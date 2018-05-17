#include "Application.h"
#include "Enemy_Outdoor_turret.h"
#include "ModuleCollision.h"
#include "ModuleStage05.h"
#include "ModuleEnemies.h"

Enemy_Outdoor_turret::Enemy_Outdoor_turret(int x, int y, POWERUP_TYPE pu_t) : Enemy(x, y, pu_t)
{
	OutdoorTurretAnim.PushBack({152,156,24,20});
	OutdoorTurretAnim.loop = true;
	animation = &OutdoorTurretAnim;
	position_x = x-App->stage05->spawnPos.x;
	position_y = y-App->stage05->spawnPos.y;
	collider = App->collision->AddCollider({ x, y+3, 24, 17 }, COLLIDER_TYPE::COLLIDER_ENEMY_HEAVY, (Module*)App->enemies);
	StartTime = SDL_GetTicks();
}

void Enemy_Outdoor_turret::Move()
{
	position.x = App->stage05->spawnPos.x+position_x;
	position.y = App->stage05->spawnPos.y+position_y;
	/*if (SDL_GetTicks() - StartTime > 2500)
	{
		App->enemies->AddEnemy(OUTDOOR_LASER, position.x- App->stage05->spawnPos.x , position.y- App->stage05->spawnPos.y);
		StartTime = SDL_GetTicks();
	}*/
}

