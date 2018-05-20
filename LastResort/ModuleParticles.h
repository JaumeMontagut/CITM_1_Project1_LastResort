#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"
#include "Particle.h"
#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;
struct Mix_Chunk;



class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(Particle& particle, int x, int y, SDL_Texture *tex ,COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0, PARTICLE_TYPE particle_type = PARTICLE_REGULAR);
	

private:
	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];

public:
	//PLAYER------------------------------------------------

	Particle basicShot;
	Particle basic_explosion; //Basic Shot Explosion
	Mix_Chunk* basic_shot_sfx = nullptr;
	Particle unit_explosion;//Unit shot explosion
	Particle unitShot;
	Particle death_explosion;//Death explosion 
	Mix_Chunk* death_sfx = nullptr;
	Particle Basic_Laser;

	//GENERAL-----------------------------------------------
	Particle g_explosion01;
	Particle g_explosion02;
	Mix_Chunk* g_explosion01_1sfx = nullptr;
	Mix_Chunk* g_explosion02_1sfx = nullptr;
	Mix_Chunk* Basic_LaserFx = nullptr;
	//Enemies------------------------------------------------
	Particle MiddleBossShot;
	Particle MiddleBosExplotion;
	iPoint VectorMiddleBossShots;

	Particle LacerEnemyShot;
	SDL_Texture* LaserTex;

	//Mix_Chunk* g_explosion02_2sfx = nullptr;
	//Mix_Chunk* g_explosion02_3sfx = nullptr;	
	//Mix_Chunk* g_explosion01_2sfx = nullptr;
	//Mix_Chunk* g_explosion01_3sfx = nullptr;
};

#endif // __MODULEPARTICLES_H__

