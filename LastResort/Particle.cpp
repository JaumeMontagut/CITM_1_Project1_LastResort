#include "Particle.h"
#include "Application.h"
#include "ModuleRender.h"
#include "SDL\include\SDL_timer.h"
#include "ModuleStage05.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(Particle& sentParticle, iPoint position, iPoint speed, Uint32 delay, COLLIDER_TYPE colType, SDL_Texture* tex)
{
	//- Values that vary depending on the parameters we pass in
	this->position = position;
	this->fixedPos = position - App->stage05->spawnPos;
	this->speed = speed;
	this->born = SDL_GetTicks() + delay;
	if (colType != COLLIDER_IGNORE_HIT)
	{
		this->collider = App->collision->AddCollider({ this->position.x, this->position.y ,this->anim.GetCurrentFrame().w, this->anim.GetFrame().h }, colType, (Module*)App->particles);
	}
	this->texture = tex;

	//- Values that always stay the same as sentParticle (those values are defined on ModuleParticles.cpp or they are the default ones)
	this->anim = sentParticle.anim;
	this->collision_fx = sentParticle.collision_fx;
	this->life = sentParticle.life;
	if (sentParticle.collision_fx != nullptr) { this->collision_fx = sentParticle.collision_fx; }
	
	//- Play audio
	if (sentParticle.sfx != nullptr) { App->audio->ControlSFX(sentParticle.sfx, PLAY_AUDIO); }
}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::CheckParticleDeath()
{
	//1- Check if its his "life" time has passed
	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
		{
			return true;
		}
	}

	//2- Check if its animation has finished
	else
	{
		if (anim.Finished())
		{
			return true;
		}
	}

	//3- Check if it out of the screen margins
	if (position.x >  SCREEN_WIDTH + DESPAWN_MARGIN_RIGHT ||
		position.x < 0 - DESPAWN_MARGIN_LEFT ||
		position.y > SCREEN_HEIGHT + DESPAWN_MARGIN_DOWN ||
		position.y < 0 - DESPAWN_MARGIN_UP)
	{
		return true;
	}

	//4- Return false it is shouldn't die (passes all the cases)
	return false;
}

void Particle::Move()
{
	position.x += speed.x;
	position.y += speed.y;
}

void Particle::Draw()
{
	SDL_Rect currentFrame = anim.GetCurrentFrame();

	//Update the collider
	if (collider != nullptr)
	{
		collider->SetPos(position.x - currentFrame.w / 2, position.y - currentFrame.h / 2);
		collider->SetMeasurements(currentFrame.w, currentFrame.h);
	}

	//Draw the particle
	App->render->Blit(this->texture, position.x - currentFrame.w / 2, position.y - currentFrame.h / 2, &currentFrame);
}