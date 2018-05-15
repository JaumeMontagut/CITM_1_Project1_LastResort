#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModulePowerups.h"
#include "Enemy.h"
#include "Enemy_Oscilator.h"
#include "Enemy_Basic.h"
#include "Enemy_PowerDropper.h"
#include "MiddleBosslvl1.h"
#include "Enemy_RedBats.h"
#include "Enemy_RotatingTurret.h"
#include "Enemy_Pinata.h"
#include "ModuleStage05.h"

#define DAMAGE_FLASHING_INTERVAL 4

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	 ; //ALL IN 1 PNG
	nml_sprites = App->textures->Load("Assets/General/Enemies/Enemies1.png");
    dmg_sprites = App->textures->Load("Assets/General/Enemies/Enemies1_white.png");
	
	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	//Check if the enemy is inside the "spawn area (viewport + spawn margin)" to spawn it---------------------------------------------------------------------------
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (App->stage05->spawnPos.x + queue[i].x < 0 + SCREEN_WIDTH + spawnMarginRight &&
				App->stage05->spawnPos.x + queue[i].x > 0 - spawnMarginLeft &&
				App->stage05->spawnPos.y + queue[i].y > 0 - spawnMarginUp &&
				App->stage05->spawnPos.y + queue[i].y < 0 + SCREEN_HEIGHT + spawnMarginDown)
			{
				//If we get to the position, we start counting
				if (queue[i].counting == false)
				{
					queue[i].spawnTime = SDL_GetTicks() + queue[i].delay;
					queue[i].counting = true;
				}
				//If we reach the spawn time, we spawn the enemy!
				if(queue[i].counting == true && SDL_GetTicks() <= queue[i].spawnTime)
				{
					SpawnEnemy(queue[i]);
					queue[i].type = ENEMY_TYPES::NO_TYPE;
					LOG("Spawning enemy at %d", queue[i].x);
				}
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr)
		{
			enemies[i]->Move();
		}

	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr) {

			if (enemies[i]->isDamaged)
			{
				if (enemies[i]->flashing_interval %2) 
					enemies[i]->Draw(dmg_sprites);
				else
					enemies[i]->Draw(nml_sprites);
					
				enemies[i]->dmg_frames += 1;

				if (enemies[i]->dmg_frames > 3) {
					enemies[i]->flashing_interval += 1;
					enemies[i]->dmg_frames = 0;
				}
				if (enemies[i]->flashing_interval > DAMAGE_FLASHING_INTERVAL) {
					enemies[i]->isDamaged = false;
					enemies[i]->flashing_interval = -1;
				}

			}
			else {
				enemies[i]->Draw(nml_sprites);
			}
		}
	}
	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	//Check if the enemy is outside the "spawn area (viewport + despawn margin)" to despawn it---------------------------------------------------------------------------
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->position.x > 0 + SCREEN_WIDTH + despawnMarginRight ||
				enemies[i]->position.x < 0 - despawnMarginLeft ||
				enemies[i]->position.y < 0 - despawnMarginUp ||
				enemies[i]->position.y > 0 + SCREEN_HEIGHT + despawnMarginDown)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y, Uint32 delay, POWERUP_TYPE powerup_type)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].delay = delay;
			queue[i].pu_Type = powerup_type;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::BASIC:
			enemies[i] = new Enemy_Basic(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, info.pu_Type);
			enemies[i]->points = 100;
			enemies[i]->hp = 1;
			break;
		case ENEMY_TYPES::OSCILATOR:
			enemies[i] = new Enemy_Oscilator(info.x + App->stage05->spawnPos.x, info.pu_Type);
			enemies[i]->points = 100;
			enemies[i]->hp = 5;
			break;
		case ENEMY_TYPES::POWERDROPPER:
			enemies[i] = new Enemy_PowerDropper(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, info.pu_Type);
			enemies[i]->points = 100;
			enemies[i]->hp = 1;
			break;
		case ENEMY_TYPES::METALCROW:
			enemies[i] = new Enemy_MetalCraw(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, info.pu_Type);
			enemies[i]->points = 1000;
			enemies[i]->hp = 50;
			break;
		case  ENEMY_TYPES::REDBATS:
			enemies[i] = new Enemy_RedBats(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, info.pu_Type);
			enemies[i]->points = 100;
			enemies[i]->hp = 1;
			break;
		case ENEMY_TYPES::ROTATING_TURRET:
			enemies[i] = new Enemy_RotatingTurret(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, info.pu_Type);
			enemies[i]->points = 200;
			enemies[i]->hp = 50;
			break;
		case ENEMY_TYPES::PINATA:
			enemies[i] = new Enemy_Pinata(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, info.pu_Type);
			enemies[i]->points = 200;
			enemies[i]->hp = 50;
			break;
		case ENEMY_TYPES::PINATA_SPAWNER:
			enemies[i] = new Enemy_Pinata(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, info.pu_Type);
			enemies[i]->points = 200;
			enemies[i]->hp = 50;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			//Rest hp to enemies depending on the collider's damage
			enemies[i]->hp -= c2->damage;  
			//If enemy dies-----------------------------------------
			if (enemies[i]->hp <= 0)
			{
				//---Give out points------------------------
				if (c2->type == COLLIDER_PLAYER_1_SHOT) {
					App->ui->score_p1 += enemies[i]->points;
				}
				else if (c2->type == COLLIDER_PLAYER_2_SHOT) {
					App->ui->score_p2 += enemies[i]->points;
				}
				//---Drop powerup---------------------------
				if (enemies[i]->powerUp_drop != NOPOWERUP) {
					App->powerups->AddPowerup( enemies[i]->position.x, enemies[i]->position.y, enemies[i]->powerUp_drop);
				}
				//---Delete enemie--------------------------
				enemies[i]->OnCollision(c2);
				delete enemies[i];
				enemies[i] = nullptr;
			}
			//If enemy does not die only change its sprite to white
			else  if  (enemies[i]->isDamaged == false && enemies[i]->flashing_interval == -1) {
				enemies[i]->isDamaged = true;
				enemies[i]->flashing_interval = 0;
			}
		}
	}
}