#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

#define BORDER_WIDTH 1
#define MAX_ZOOM 5
#define MOVE_AMOUNT 5

ModuleRender::ModuleRender() : Module()
{

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
		SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	ResetMovedPosition();

	return ret;
}

void ModuleRender::ResetMovedPosition()
{
	movedPosition.x = 0;
	movedPosition.y = 0;
}

// Called every draw update
update_status ModuleRender::PreUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	if (App->input->keyboard[SDL_SCANCODE_KP_8] == KEY_REPEAT) { movedPosition.y += MOVE_AMOUNT; }
	if (App->input->keyboard[SDL_SCANCODE_KP_4] == KEY_REPEAT) { movedPosition.x += MOVE_AMOUNT; }
	if (App->input->keyboard[SDL_SCANCODE_KP_5] == KEY_REPEAT) { movedPosition.y -= MOVE_AMOUNT; }
	if (App->input->keyboard[SDL_SCANCODE_KP_6] == KEY_REPEAT) { movedPosition.x -= MOVE_AMOUNT; }
	if (App->input->keyboard[SDL_SCANCODE_KP_0] == KEY_REPEAT) { ResetMovedPosition(); }

	if (App->input->keyboard[SDL_SCANCODE_KP_7] == KEY_DOWN)
	{
		if (zoomedOutSize < MAX_ZOOM)
		{
			zoomedOutSize++;
			SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH * zoomedOutSize, SCREEN_HEIGHT * zoomedOutSize);
		}
	}
	if(App->input->keyboard[SDL_SCANCODE_KP_9] == KEY_DOWN)
	{
		if (zoomedOutSize > 1)
		{
			zoomedOutSize--;
			SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH * zoomedOutSize, SCREEN_HEIGHT * zoomedOutSize);
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update()	
{	
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	//Render the camera borders, so we know where the camera is
	//- INFO: Border width is multiplied by zoomedOutSize to mantain its size across all the zoomed out modes
	//Up border
	App->render->DrawQuad({ -BORDER_WIDTH * zoomedOutSize, -BORDER_WIDTH * zoomedOutSize, SCREEN_WIDTH + BORDER_WIDTH * zoomedOutSize * 2, BORDER_WIDTH * zoomedOutSize }, 255, 255, 255, 255);
	//Down border
	App->render->DrawQuad({ -BORDER_WIDTH * zoomedOutSize, SCREEN_HEIGHT, SCREEN_WIDTH + BORDER_WIDTH * zoomedOutSize * 2, BORDER_WIDTH * zoomedOutSize }, 255, 255, 255, 255);
	//Left border
	App->render->DrawQuad({ -BORDER_WIDTH * zoomedOutSize, 0, BORDER_WIDTH * zoomedOutSize, SCREEN_HEIGHT}, 255, 255, 255, 255);
	//Right border
	App->render->DrawQuad({ SCREEN_WIDTH, 0, BORDER_WIDTH * zoomedOutSize, SCREEN_HEIGHT}, 255, 255, 255, 255);

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

	//Zooming and moving the viewport
	rect.x += SCREEN_WIDTH * (zoomedOutSize - 1) / 2 + movedPosition.x;
	rect.y += SCREEN_HEIGHT * (zoomedOutSize - 1) / 2 + movedPosition.y;

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

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);

	rec.x *= SCREEN_SIZE;
	rec.y *= SCREEN_SIZE;
	rec.w *= SCREEN_SIZE;
	rec.h *= SCREEN_SIZE;

	//Zooming and moving the viewport
	rec.x += SCREEN_WIDTH * (zoomedOutSize - 1) / 2 + movedPosition.x;
	rec.y += SCREEN_HEIGHT * (zoomedOutSize - 1) / 2 + movedPosition.y;

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

	//Zooming and moving the viewport
	rect.x += SCREEN_WIDTH * (zoomedOutSize - 1) / 2 + movedPosition.x;
	rect.y += SCREEN_HEIGHT * (zoomedOutSize - 1) / 2 + movedPosition.y;

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



