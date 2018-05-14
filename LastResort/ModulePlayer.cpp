#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleStageClear.h"
#include "ModuleStage01.h"
#include "ModuleUnit.h"
#include "Player1.h"
#include "Player2.h"

ModulePlayer::ModulePlayer() //Constructor 
{}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::Start()
{
	bool ret = true;
	LOG("Loading player assets");
	//variables-----------------------------------------------------------------------
	godMode = false;
	isShooting = false;
	shoot = false;
	canMove = false;
	canShoot = false;
	isDying = false;
	shipAnimations = ShipAnimations::Initial;
	start_time = SDL_GetTicks();
	//audios-------------------------------------------------------------------------
	init_sfx = App->audio->LoadSFX("Assets/initial_sfx.wav");
	//textures-----------------------------------------------------------------------
	PlayerTexture = App->textures->Load("Assets/SpaceShip_player1.png"); // arcade version																 
	//colliders----------------------------------------------------------------------
	InitPosition();//We set the position (before adding the collider) (note that the intial positions are set in Player1.h and Player2.h)
	playerCol = App->collision->AddCollider({ position.x, position.y + 2, 24, 8 }, COLLIDER_TYPE::COLLIDER_PLAYER, this);
	//animations----------------------------------------------------------------------
	deathAnim.Reset();

	return ret;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player assets");
	//textures------------------------------------------------------------------
	App->textures->Unload(PlayerTexture);
	//audios-------------------------------------------------------------------------
	App->audio->UnloadSFX(init_sfx);
	return true;
}

void ModulePlayer::Reappear() {
	powerup_upgrades = 0;
	powerup_type = POWERUP_TYPE::NOPOWERUP;
	shipAnimations = ShipAnimations::Initial;
	isShooting = false;
	shoot = false;
	canMove = false;
	canShoot = false;
	start_time = SDL_GetTicks();
	deathAnim.Reset();
	InitPosition();
}

void ModulePlayer::InitPosition() {
	position = initPosition;
}


update_status ModulePlayer::PreUpdate()
{
	//Movement-------------------------------------------------------------------------
	if (canMove == true)
		MovementInput();
	//If the movement is not on preupdate, the player will move after the unit, causing weird visual effects

	return UPDATE_CONTINUE;
}

update_status ModulePlayer::Update()
{
	//Timer----------------------------------------------------------------------------
	current_time = SDL_GetTicks() - start_time; //Delete if it has not use
	//Debug Modes----------------------------------------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
	{
		if (godMode == true)
		{
			//Go back to normal
			playerCol->type = COLLIDER_PLAYER;
			SDL_SetTextureColorMod(PlayerTexture, 255, 255, 255);
			godMode = false;
		}
		else
		{
			//Go to god mode
			playerCol->type = COLLIDER_GOD;
			SDL_SetTextureColorMod(PlayerTexture, 255, 255, 150);
			godMode = true;
		}
	}
	//Shots----------------------------------------------------------------------------
	if (canShoot == true) {
		ShotInput();
	}
	//Lock the unit--------------------------------------------------------------------
	if (Lock())
	{
		if (unit_locked == true) { unit_locked = false; }
		else { unit_locked = true; }
	}
	//Collision------------------------------------------------------------------------
	playerCol->SetPos(position.x, position.y + 2); //We update the collider position

	//Ship Animation-------------------------------------------------------------------
	ShipAnimation();


	//Winlvl
	if (winlvl)
	{
		Winlvl();
	}
	return UPDATE_CONTINUE;
}

void ModulePlayer::ShipAnimation() {

	switch (shipAnimations)
	{
	case Initial:
		current_animation = &initAnim.GetFrameEx();
		if (initAnim.current_frame == 0)
		{
			App->audio->ControlSFX(init_sfx, PLAY_AUDIO);
		}

		if (initAnim.finished == true)
		{
			shipAnimations = ShipAnimations::Movement;
			//We change the collider type when spawning if god mode is not active
			if (godMode == false) { playerCol->type = COLLIDER_PLAYER; }
			initAnim.Reset();
			canMove = true;
			canShoot = true;
			break;
		}
		//Draw ship---------------------------------------------------
		if (initAnim.current_frame > 4)
		{
			App->render->Blit(PlayerTexture, position.x + 32 - (current_animation->w), position.y + 6 - (current_animation->h / 2), current_animation);
		}
		else
		{
			App->render->Blit(PlayerTexture, position.x - 40, position.y + 6 - (current_animation->h / 2), current_animation);
		}
		break;

	case Movement:
		//Idle--------------------------------------------------------
		if (yAxis > -transitionLimit && yAxis < transitionLimit)
		{
			currentFrame = Idle;
		}
		//Transitions-------------------------------------------------
		if (yAxis >= transitionLimit && yAxis < MaxLimit)
		{
			currentFrame = TransitionDown;
		}
		if (yAxis <= -transitionLimit && yAxis > -MaxLimit)
		{
			currentFrame = TransitionUp;
		}
		//Maximums---------------------------------------------------
		if (yAxis >= MaxLimit)
		{
			currentFrame = MaxDown;
		}
		if (yAxis <= -MaxLimit)
		{
			currentFrame = MaxUp;
		}
		//Draw ship--------------------------------------------------
		current_animation = &shipAnim.frames[currentFrame]; //It set the animation frame 

		//1- Render the texture
		App->render->Blit(PlayerTexture, position.x, position.y, current_animation);
		////2- Render the lightened texture above it
		//SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_ADD);
		//SDL_SetTextureColorMod(PlayerTexture, 255, 255, 255);
		//App->render->Blit(PlayerTexture, position.x, position.y, current_animation);
		////3- Put everything back to normal
		//SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_NONE);
		//SDL_SetTextureColorMod(PlayerTexture, 0, 0, 0);
		//https://forums.libsdl.org/viewtopic.php?p=51593
		break;

	case Death:
		if (deathAnim.finished == true)
		{
			PlayerDies();
		}
		else if (isDying)
		{
			playerCol->type = COLLIDER_NONE;
			current_animation = &deathAnim.GetFrameEx();
			App->render->Blit(PlayerTexture, position.x + 32 - current_animation->w, position.y + 6 - current_animation->h / 2, current_animation);
		}
		break;

	}
}


void ModulePlayer::OnCollision(Collider* collider1, Collider* collider2)
{
	App->particles->AddParticle(App->particles->death_explosion, position.x, position.y , PlayerTexture, COLLIDER_NONE);
	isDying = true;
	canMove = false;
	canShoot = false;
	shipAnimations = ShipAnimations::Death;
	KillUnit();
}

void  ModulePlayer::ShotInput() {
	//Basic shoot-------------------------------------------------------------------
	if (Shoot() == true)
	{
		if(powerup_type == POWERUP_TYPE::NOPOWERUP)
		{
			//Basic shoot
			App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 6, PlayerTexture, shot_colType, 0);
		}
		if (powerup_type == POWERUP_TYPE::LASER)
		{
			switch(powerup_upgrades)
			{
			case 1:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 6, PlayerTexture, shot_colType, 0);
				break;
			case 2:
				//Laser shot
				App->particles->AddParticle(App->particles->Basic_Laser, position.x + 32, position.y + 6, PlayerTexture, shot_colType, 0);
				break;
			case 3:
				//Laser shot
				App->particles->AddParticle(App->particles->Basic_Laser, position.x + 32, position.y + 6, PlayerTexture, shot_colType, 0);
				//Laser rings
				break;
			}
		}
		if (powerup_type == POWERUP_TYPE::HOMING)
		{
			switch (powerup_upgrades)
			{
			case 1:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 6, PlayerTexture, shot_colType, 0);
				break;
			case 2:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 6, PlayerTexture, shot_colType, 0);
				//2 missiles on the sides
				break;
			case 3:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 6, PlayerTexture, shot_colType, 0);
				//6 missiles on the sides
				break;
			}
		}
		if (powerup_type == POWERUP_TYPE::GROUND)
		{
			switch (powerup_upgrades)
			{
			case 1:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position. y + 6, PlayerTexture, shot_colType, 0);
				break;
			case 2:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 6, PlayerTexture, shot_colType, 0);
				//Missiles up and down
				break;
			case 3:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 6, PlayerTexture, shot_colType, 0);
				//Missiles up and down that destoy the ground
				break;
			}
		}
		if (isShooting == false) { shoot = true; }
		if (Controllshoot == true) {
			Controllshoot = false;

		}
	}
	//----------Ship Fire-------------------------------------------
	if (shoot == true) {
		if (powerup_type == POWERUP_TYPE::NOPOWERUP)
		{
			if (shotFire.finished == false)
			{
				isShooting = true;
				App->render->Blit(PlayerTexture, position.x + 32, position.y + 1, &shotFire.GetFrameEx());
			}
			else
			{
				shotFire.finished = false;
				isShooting = false;
				shoot = false;
			}
		}
		if (powerup_type == POWERUP_TYPE::LASER)
		{
			if (ShotLaserBasic.finished == false)
			{
				isShooting = true;
				App->render->Blit(PlayerTexture, position.x + 32, position.y + 1, &ShotLaserBasic.GetFrameEx());
			}
			else
			{
				shotFire.finished = false;
				isShooting = false;
				shoot = false;
			}
		}
		else
		{
			if (shotFire.finished == false)
			{
				isShooting = true;
				App->render->Blit(PlayerTexture, position.x + 32, position.y + 1, &shotFire.GetFrameEx());
			}
			else
			{
				shotFire.finished = false;
				isShooting = false;
				shoot = false;
			}
		}
		
	}
}




void ModulePlayer::MovementInput() {

	if (MoveLeft() == true) {
		//---------Movement-----------------------------------------------------------
		position.x -= (int)movementSpeed;
		if (position.x < 0 + HORIZONTAL_MARGIN)
		{ position.x = 0 + HORIZONTAL_MARGIN; }
	}
	if (MoveRight() == true) {
		//---------Movement-----------------------------------------------------------
		position.x += (int)movementSpeed;
		if (position.x > SCREEN_WIDTH - playerwidth - HORIZONTAL_MARGIN)
		{ position.x = SCREEN_WIDTH - playerwidth - HORIZONTAL_MARGIN; }
	}
	if (MoveUp() == true) {
		//---------Movement-----------------------------------------------------------
		position.y -= (int)movementSpeed;
		if (position.y < 0 + VERTICAL_MARGIN)
		{ position.y = 0 + VERTICAL_MARGIN; }

		//---------Animation---------------------------------------------------------
		yAxis -= keyPressSpeed;
		//We check that the yAxis doesn't get bellow -1
		if (yAxis < -1) {
			yAxis = -1;
		}
	}

	if (MoveDown() == true) {
		//---------Movement-----------------------------------------------------------
		position.y += (int)movementSpeed;
		if (position.y > SCREEN_HEIGHT - playerheight - VERTICAL_MARGIN)
		{ position.y = SCREEN_HEIGHT - playerheight - VERTICAL_MARGIN; }
			
		//---------Animation---------------------------------------------------------
		yAxis += keyPressSpeed;
		//We check that the yAxis doesn't get above 1
		if (yAxis > 1)
		{
			yAxis = 1;
		}
	}
	//If there isn't any input on the y axis
	if (MoveDown() == false) {
		if (yAxis > 0.1) {
			yAxis -= keyReleaseSpeed;
		}
	}

	if (MoveUp() == false) {
		if (yAxis < -0.1) {
			yAxis += keyReleaseSpeed;
		}
	}
}

void ModulePlayer::Winlvl()
{
	if (godMode == false)
	{
		playerCol->type = COLLIDER_NONE;
		godMode = true;
	}

	canShoot = false;
	canMove = false;
	Winposition();
}
