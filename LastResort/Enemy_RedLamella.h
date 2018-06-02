#ifndef __ENEMY_RED_LAMELLA_H__
#define __ENEMY_RED_LAMELLA_H__

#include "Enemy.h"
#include "MovPath.h"

class ModulePlayer;

class Enemy_RedLamella: public Enemy
{
public:
	Enemy_RedLamella(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void Draw(SDL_Texture* sprites);
	void CheckTarget();
	void CheckDirection();

private:
	//Animations---------------------------
	Animation moveAnim;
	Animation rotateAnim;
	Animation initAnim;
	//Variables---------------------------
	fPoint float_position;
	fPoint velocity;
	fPoint aceleration;
	ModulePlayer* currentTarget = nullptr;
	ModulePlayer* lastTarget = nullptr;
	MovePath pinataMov;
	bool blitEx = false;


	enum DirectionX {
		RIGHT,
		LEFT
	} currentDirX = LEFT, lastDirX = LEFT;

	enum DirectionY {
		UP,
		DOWN
	} currentDirY = UP;

	enum MoveState {
		FOLLOW,
		ROTATE
	} currentState = FOLLOW;


	
};

#endif // __ENEMY_RED_LAMELLA_H__
