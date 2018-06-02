#ifndef __ENEMY_METALBEE_H__
#define __ENEMY_METALBEE_H__

#include "Enemy.h"
#include "MovPath.h"

class ModulePlayer;

class Enemy_MetalBee : public Enemy
{
public:
	Enemy_MetalBee(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	/*void Draw(SDL_Texture* sprites);
	void CheckTarget();
	void CheckDirection();*/

private:
	//Animations---------------------------
	Animation moveAnim;
	Animation rotateAnim;
	//Variables---------------------------
	fPoint float_position;
	fPoint speed;
	fPoint aceleration;
	ModulePlayer* currentTarget = nullptr;
	ModulePlayer* lastTarget = nullptr;
	MovePath pinataMov;
	bool blitEx = false;
	int currentFrames = 0;


	enum DirectionX {
		RIGHT,
		LEFT
	} currentDirX = LEFT, lastDirX = LEFT;

	enum MoveState {
		FOLLOW,
		ROTATE
	} currentState = FOLLOW;

};

#endif // __ENEMY_METALBEE_H__
