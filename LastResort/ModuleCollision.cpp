#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleCollision::ModuleCollision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_NONE][COLLIDER_NONE] = false;
	matrix[COLLIDER_NONE][COLLIDER_WALL] = false;
	matrix[COLLIDER_NONE][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_NONE][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_NONE][COLLIDER_PLAYER_1_SHOT] = true;
	matrix[COLLIDER_NONE][COLLIDER_PLAYER_2_SHOT] = true;
	matrix[COLLIDER_NONE][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_NONE][COLLIDER_UNIT] = false;
	matrix[COLLIDER_NONE][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_NONE][COLLIDER_GOD] = false;
	matrix[COLLIDER_NONE][COLLIDER_HIT_DETECTION_WALL] = false;

	matrix[COLLIDER_WALL][COLLIDER_NONE] = false;
	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_1_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_2_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_UNIT] = false;
	matrix[COLLIDER_WALL][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_WALL][COLLIDER_GOD] = false;
	matrix[COLLIDER_WALL][COLLIDER_HIT_DETECTION_WALL] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_NONE] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_1_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_UNIT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_GOD] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_HIT_DETECTION_WALL] = false;

	matrix[COLLIDER_ENEMY][COLLIDER_NONE] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_1_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_2_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_UNIT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_GOD] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_HIT_DETECTION_WALL] = false;

	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_NONE] = false;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_PLAYER_1_SHOT] = false;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_UNIT] = false;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_GOD] = false;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_HIT_DETECTION_WALL] = false;

	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_NONE] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_PLAYER_1_SHOT] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_UNIT] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_GOD] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_HIT_DETECTION_WALL] = false;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_NONE] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_1_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_UNIT] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_GOD] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_HIT_DETECTION_WALL] = false;

	matrix[COLLIDER_UNIT][COLLIDER_NONE] = false;
	matrix[COLLIDER_UNIT][COLLIDER_WALL] = false;
	matrix[COLLIDER_UNIT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_UNIT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_UNIT][COLLIDER_PLAYER_1_SHOT] = false;
	matrix[COLLIDER_UNIT][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_UNIT][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_UNIT][COLLIDER_UNIT] = false;
	matrix[COLLIDER_UNIT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_UNIT][COLLIDER_GOD] = false;
	matrix[COLLIDER_UNIT][COLLIDER_HIT_DETECTION_WALL] = false;

	matrix[COLLIDER_POWERUP][COLLIDER_NONE] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_WALL] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWERUP][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_PLAYER_1_SHOT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_UNIT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_GOD] = true;
	matrix[COLLIDER_POWERUP][COLLIDER_HIT_DETECTION_WALL] = false;

	matrix[COLLIDER_GOD][COLLIDER_NONE] = false;
	matrix[COLLIDER_GOD][COLLIDER_WALL] = false;
	matrix[COLLIDER_GOD][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_GOD][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_GOD][COLLIDER_PLAYER_1_SHOT] = false;
	matrix[COLLIDER_GOD][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_GOD][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_GOD][COLLIDER_UNIT] = false;
	matrix[COLLIDER_GOD][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_GOD][COLLIDER_GOD] = false;	
	matrix[COLLIDER_GOD][COLLIDER_HIT_DETECTION_WALL] = false;

	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_NONE] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_WALL] = true;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_PLAYER_1_SHOT] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_UNIT] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_GOD] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_HIT_DETECTION_WALL] = false;
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	//LOG("Matrix powerup and god %d", matrix[COLLIDER_POWERUP][COLLIDER_GOD]);

	// Remove all colliders scheduled for deletion---------------------------------------------
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	// Calculate collisions
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				matrix[COLLIDER_POWERUP][COLLIDER_GOD] = true;//FIX (this is probably rewritten somewhere else, but i can't find where)

				if (matrix[c1->type][c2->type] && c1->callback)
				{
					c1->callback->OnCollision(c1, c2);
				}

				if (matrix[c2->type][c1->type] && c2->callback)
				{
					c2->callback->OnCollision(c2, c1);
				}		
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{

	DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if (App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_PLAYER_1_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_PLAYER_2_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 51, 255, alpha);
			break;
		case COLLIDER_ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_UNIT: // pink
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
			break;
		case COLLIDER_POWERUP: // orange
			App->render->DrawQuad(colliders[i]->rect, 255, 125, 0, alpha);
			break;
		case COLLIDER_GOD: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		}
	}
}

bool ModuleCollision::Start()
{
	LOG("Bool on start: %d", matrix[COLLIDER_POWERUP][COLLIDER_GOD]);
	return true;
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	//Return true if there is an overlap between argument "r" and property "rect"
	return (this->rect.x + this->rect.w > r.x   &&
		this->rect.x                < r.x + r.w &&
		this->rect.y + this->rect.h > r.y       &&
		this->rect.y < r.y + r.h);
}