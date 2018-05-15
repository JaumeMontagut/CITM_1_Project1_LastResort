#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "ModulePowerups.h"
#include "Enemy_Basic.h"
#include "Enemy_Oscilator.h"
#include "Enemy_PowerDropper.h"
#include "ModuleUI.h"

#define MAX_ENEMIES 100

enum ENEMY_TYPES
{
	NO_TYPE = -1,
	BASIC,
	OSCILATOR,
	POWERDROPPER,
	METALCROW,
	REDBATS,
	ROTATING_TURRET,
	PINATA,
	PINATA_SPAWNER,
	MAX_ENEMY
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
	Uint32 delay;//In miliseconds
	POWERUP_TYPE pu_Type = POWERUP_TYPE:: NOPOWERUP;
	//Additional variables (help us spawn enemies with time)
	bool counting = false;
	Uint32 spawnTime;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPES type, int x, int y, Uint32 delay = 0, POWERUP_TYPE powerup_type = NOPOWERUP);

private:

	void SpawnEnemy(const EnemyInfo& info);

private:
	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];

public:
	SDL_Texture* sprites = nullptr;
	SDL_Texture* nml_sprites = nullptr;
	SDL_Texture* dmg_sprites = nullptr;

	//Spawning
	const int spawnMarginLeft = 40;
	const int spawnMarginRight = 30;
	const int spawnMarginUp = 40;
	const int spawnMarginDown = 30;
	const int despawnMarginLeft = 200;
	const int despawnMarginRight = 200;
	const int despawnMarginUp = 200;
	const int despawnMarginDown = 200;
	// Despawn margin always needs to be a little bigger than spawn margin or otherwise enemies would be spawned and immmediately despawned
};

#endif // __ModuleEnemies_H__
