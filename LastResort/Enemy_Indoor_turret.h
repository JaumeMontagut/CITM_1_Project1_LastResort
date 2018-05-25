#ifndef __ENEMY_INDOOR_TURRET_H__
#define __ENEMY_INDOOR_TURRET_H__

#include "Enemy.h"
#include "Rotation.h"

class Enemy_indoorTurret : public Enemy
{
public:
	Enemy_indoorTurret(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop, iPoint speed);
	void Move();
	//void OnCollision(Collider*);

private:
	//Helper functions
	fPoint fixedPos;
	Animation indoorTurretAnim;
	iPoint targetPlayerPos;
	int frameCounter;

};

#endif // __ENEMY_INDOOR_TURRET_H__

