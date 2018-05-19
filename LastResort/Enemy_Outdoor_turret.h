#ifndef __ENEMY_OUTDOOR_TURRET_H__
#define __ENEMY_OUTDOOR_TURRET_H__

#include "Enemy.h"
#include "ModuleParticles.h"
class Enemy_Outdoor_turret : public Enemy
{
private:
	Animation OutdoorTurretAnim;
	int initialY;
	int position_y;
	int position_x;
	Uint32 StartTime;
	Uint32 CurrentTime;
	
	SDL_Texture *LacerTex;
public:
	Enemy_Outdoor_turret(int x, int y, POWERUP_TYPE pu_t);
	~Enemy_Outdoor_turret();
	void Move();
};

#endif // __ENEMY_OUTDOOR_TURRET_H__

