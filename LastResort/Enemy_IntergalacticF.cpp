#include "Application.h"
#include "Enemy_IntergalacticF.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleStage05.h"
#include "MovPath.h"


Enemy_Intergalactic_F::Enemy_Intergalactic_F(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	//Position--------------------------------------
	fixedPos.x = x - App->stage05->spawnPos.x;
	fixedPos.y = y - App->stage05->spawnPos.y;
	//Movement--------------------------------------
	pinataMov.originPoint = { 0,0 };
	pinataMov.PushBack({ 0,90 }, 150);
	pinataMov.PushBack({ -10 ,85 }, 15);
	//Animations------------------------------------
	moveRAnim.PushBack({ 0, 0,0,0 });   //1
	moveRAnim.PushBack({ 0, 0,0,0 });   //2
	moveRAnim.PushBack({ 0, 0,0,0 });   //3
	moveRAnim.speed = 0.3f;

	moveLAnim.PushBack({ 0, 0,0,0 });   //1
	moveLAnim.PushBack({ 0, 0,0,0 });   //2
	moveLAnim.PushBack({ 0, 0,0,0 });   //3
	moveLAnim.speed = 0.3f;

	rotateRAnim.PushBack({ 0, 0,0,0 }); //1
	rotateRAnim.PushBack({ 0, 0,0,0 });  //2
	rotateRAnim.PushBack({ 0, 0,0,0 });  //3
	rotateRAnim.speed = 0.1f;

	rotateLAnim.PushBack({ 0, 0,0,0 });  //1
	rotateLAnim.PushBack({ 0, 0,0,0 });  //2
	rotateLAnim.PushBack({ 0, 0,0,0 });  //2
	rotateLAnim.PushBack({ 0, 0,0,0 });  //3
	rotateLAnim.speed = 0.1f;


	//Add collider--------------------------------
	collider = App->collision->AddCollider({ x, y, 32, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
}


//Check tarjet player------------------------------------------------

void Enemy_Intergalactic_F::CheckTarget() {

	float DistancePlayer1 = float_position.DistanceTo({ (float)App->player1->position.x,(float)App->player1->position.y });
	float DistancePlayer2 = float_position.DistanceTo({ (float)App->player2->position.x,(float)App->player2->position.y });

	if (DistancePlayer1 <= DistancePlayer2) {
		if (App->player1->isActive)
			currentTarget = App->player1;
		else if (App->player2->isActive)
			currentTarget = App->player2;
	}
	else if (DistancePlayer2  < DistancePlayer1)
	{
		if (App->player2->isActive)
			currentTarget = App->player2;
		else if (App->player1->isActive)
			currentTarget = App->player1;
	}

	if (lastTarget == nullptr) {
		lastTarget = currentTarget;
	}
	else if (lastTarget != currentTarget) {
		CheckDirection();
		lastTarget = currentTarget;
	}

}

//Check enemy direction-----------------------------------------------

void Enemy_Intergalactic_F::CheckDirection() {

	if (float_position.x  < currentTarget->position.x) {
		currentDir = RIGHT;
	}
	else if (float_position.x >= currentTarget->position.x) {
		currentDir = LEFT;
	}

	if (lastDir == NONE) {
		lastDir = currentDir;
	}
	else if (lastDir != currentDir && currentState != IDLE) {
		currentState = ROTATE;
		lastDir = currentDir;
	}
}

//Movement-------------------------------------------------------------

void Enemy_Intergalactic_F::Move()
{
	fPoint vectorIncrease;
	fPoint PlayerPos;

	switch (currentState)
	{

	case MOVE:
		CheckTarget();
		CheckDirection();

		pinataMov.GetCurrentPosition();
		float_position.y = App->stage05->spawnPos.y + fixedPos.y + pinataMov.GetPosition().y;

		float_position.x = App->stage05->spawnPos.x + fixedPos.x - pinataMov.GetPosition().x;


		break;
	case ROTATE:
		//Not move
		break;
	}
	position = { (int)float_position.x, (int)float_position.y };
}

void Enemy_Intergalactic_F::Draw(SDL_Texture* sprites)
{
	SDL_Rect currentAnim;
	blitEx = false;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	switch (currentState)
	{
	case MOVE:
		if (currentDir == RIGHT)
			currentAnim = moveRAnim.LoopAnimation();
		else if (currentDir == LEFT) {
			currentAnim = moveLAnim.LoopAnimation();
		}

		break;
	case ROTATE:

		if (currentDir == RIGHT) {
			currentAnim = rotateRAnim.GetFrameEx();
			if (rotateRAnim.finished == true) {
				moveRAnim.Reset();
				rotateRAnim.Reset();
				currentState = MOVE;
			}
		}
			

		else if (currentDir == LEFT) {
			currentAnim = rotateLAnim.GetFrameEx();
			if (rotateLAnim.finished == true) {
				moveLAnim.Reset();
				rotateLAnim.Reset();
				currentState = MOVE;
			}
		}
		break;
	}

	////Check direction for flip blit or not----------------------------------
	//if (currentDir == RIGHT)
	//	blitEx = true;
	//else
	//	blitEx = false;

	//Draw------------------------------------------------------------------

	App->render->Blit(sprites, position.x, position.y, &currentAnim);

}