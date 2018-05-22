#include "Application.h"
#include "Enemy_Big_Asteriod.h"
#include "ModuleCollision.h"
Enemy_Big_Asteroid::Enemy_Big_Asteroid(int x, int y, POWERUP_TYPE pu_t) :Enemy(x,y, pu_t)
{
	BigAsteroid.PushBack({ 152,176,64,62 });
	animation = &BigAsteroid;
	collider = App->collision->AddCollider({ x, y, 64, 62 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
}
void Enemy_Big_Asteroid::Move()
{
	position.x -= 3;
}
void Enemy_Big_Asteroid::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->AsteroidDestroy, position.x, position.y, App->particles->ParticleTexture, COLLIDER_NONE, 0);
}