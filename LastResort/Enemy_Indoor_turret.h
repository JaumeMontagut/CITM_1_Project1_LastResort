#ifndef __ENEMY_INDOOR_TURRET_H__
#define __ENEMY_INDOOR_TURRET_H__

#include "Enemy.h"
#include "Rotation.h"

class Enemy_indoorTurret : public Enemy
{
public:
	Enemy_indoorTurret(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	/*void Move();
	void Draw(SDL_Texture*);
	void OnCollision(Collider*);*/

private:
	//Helper functions
	Animation indoorTurretAnim;
	iPoint targetPlayerPos;
	int frameCounter;

};

#endif // __ENEMY_INDOOR_TURRET_H__

