#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "SDL_image\include\SDL_image.h"
#include <stdlib.h>
#include <time.h>
#include "ModuleContinue.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "Module2lvlScene.h"
#include "ModuleAudio.h"
#include "ModuleGameTitle.h"

ModuleContinue::ModuleContinue()
{

	// BackgroundsRect

	//Continue
	BGroundCont.x = 0;
	BGroundCont.y = 64;
	BGroundCont.w = 240;
	BGroundCont.h = 32;

	//Back Black (it's white)
	BBlack.x = 0;
	BBlack.y = 0;
	BBlack.w = SCREEN_WIDTH;
	BBlack.h = SCREEN_HEIGHT;

}

ModuleContinue::~ModuleContinue()
{}

// Load assets
bool ModuleContinue::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	backgroundCont = App->textures->Load("Assets/continue.png");

	SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(App->render->renderer, &BBlack);

	App->player->Disable();

	return ret;
}

bool ModuleContinue::CleanUp()
{
	//Remove all memory leaks

	LOG("Unloading ready scene");
	App->player->Disable(); //Disable the player module
	App->textures->Unload(backgroundCont);
	return true;
}


// Update: draw background

update_status ModuleContinue::Update()
{
	// Draw everything


	App->render->Blit(backgroundCont, 110 /*SCREEN_WIDTH/2*/, 100 /*SCREEN_HEIGHT/2*/, &BGroundCont, 0.0f); //MAGIC NUMBERS



	// make so pressing SPACE other stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(this, App->GameTitle, 0.5f);
	}



	return UPDATE_CONTINUE;
}