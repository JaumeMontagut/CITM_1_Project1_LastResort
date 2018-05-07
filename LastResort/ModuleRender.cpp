#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleRender::ModuleRender() : Module()
{
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(REN_VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC ;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	
	if(renderer == NULL)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (WIN_FULLSCREEN_DESKTOP == 1)
	{
		SDL_RenderSetLogicalSize(renderer,
			SCREEN_WIDTH,
			SCREEN_HEIGHT);
	}


	return ret;
}

// Called every draw update
update_status ModuleRender::PreUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update()	
{
	//Move the camera
	int speed = 20;

	if (App->input->keyboard[SDL_SCANCODE_KP_8] == KEY_STATE::KEY_REPEAT)
		camera.y -= speed;
	
	if (App->input->keyboard[SDL_SCANCODE_KP_2] == KEY_STATE::KEY_REPEAT)
		camera.y += speed;

	if (App->input->keyboard[SDL_SCANCODE_KP_4] == KEY_STATE::KEY_REPEAT)
		camera.x -= speed;

	if (App->input->keyboard[SDL_SCANCODE_KP_6] == KEY_STATE::KEY_REPEAT)
		camera.x += speed;
		
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if(renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section)
{
	bool ret = true;
	SDL_Rect rect;

	rect.x = x * SCREEN_SIZE;
	rect.y = y * SCREEN_SIZE;

	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if (use_camera)
	{
		rec.x = (int)(r_camera.x + rect.x * SCREEN_SIZE);
		rec.y = (int)(r_camera.y + rect.y * SCREEN_SIZE);
		
	}
	else
	{
		rec.x *=   SCREEN_SIZE;
		rec.y *=  SCREEN_SIZE;
	}

	rec.w *= SCREEN_SIZE;
	rec.h *= SCREEN_SIZE;
	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

//Blit that flips the texture horizontally
bool ModuleRender::FlippedBlit(SDL_Texture* texture, int x, int y, SDL_Rect* section)
{
	bool ret = true;
	SDL_Rect rect;

	rect.x = x * SCREEN_SIZE;
	rect.y = y * SCREEN_SIZE;

	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	
	if (SDL_RenderCopyEx(renderer, texture, section, &rect, NULL, NULL, SDL_FLIP_HORIZONTAL) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}



float  ModuleRender::getCameraPosition(int position,float speed)
{
	return(-position*SCREEN_SIZE/speed);
}


