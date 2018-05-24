#ifndef __ENEMY_FRONT_TURRET_H__
#define __ENEMY_FRONT_TURRET_H__

#include "Enemy.h"
#include "Rotation.h"

class Enemy_FrontTurret : public Enemy
{
public:
	Enemy_FrontTurret(int x, int y, POWERUP_TYPE pu_t);
	void Move();

private:
	//Helper functions
	void ShootBall(iPoint position, iPoint speed);

	Animation frontTurretAnim;
	int fixedY;
	int fixedX;
	int frameCounter = 0;
	float shotSpeed = 1;
	int shotStage = 0;
	float angleSeparation = 2 * PI / 32;
};

#endif // __ENEMY_FRONT_SHIP_TURRET_H__