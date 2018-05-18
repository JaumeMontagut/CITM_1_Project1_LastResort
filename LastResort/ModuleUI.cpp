#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleInput.h"
#include "ModuleFonts.h"
#include "ModuleFadetoBlack.h"
#include "ModuleContinue.h"
#include "ModuleStageFunctionality.h"
#include "ModuleReady.h"
#include "ModuleUnit.h"
#include <stdio.h>
#include <string.h>


ModuleUI::ModuleUI() {
	lives_score_p1 = { 0,0,32,16};
	live_score_p2 = { 160,16,40,16};
	pow = { 0,16,96,8};
	powBar = { 96, 16, 64, 3 };
	push_p2= { 159,0,96,16 };
	top = { 96,0,63,16};

}
ModuleUI:: ~ModuleUI() {}

bool ModuleUI::Start() {
	LOG("Loading Module UI assets");
	bool ret = true;
	//Fonts-------------------------------------------------------------------------
	App->fonts->Load("Assets/Fonts/blue_chars.png", "0123456789[]ABCDEFGHIJKLMNOPQRSTUVWXYZ_-.,&#", 1); //font id = 0
	//textures----------------------------------------------------------------------
	uiTex = App->textures->Load("Assets/UI.png");
	//audios------------------------------------------------------------------------
	coinsSfx = App->audio->LoadSFX("Assets/General/Fx/001. Coin inserted.wav");
	return ret;
}

bool ModuleUI::CleanUp() {
 	LOG("Unloading Module UI assets");
	//Fonts-------------------------------------------------------------------------
	App->fonts->UnLoad(0);
	//textures----------------------------------------------------------------------
	App->textures->Unload(uiTex);
	//audios------------------------------------------------------------------------
	App->audio->UnloadSFX(coinsSfx);
	//------------------------------------------------------------------------------
	return true;
}

update_status  ModuleUI::PreUpdate() { 

	return update_status::UPDATE_CONTINUE;
}


update_status ModuleUI::Update() {

	//Credits functionality------------------------------------------------------------------------------//

	//-------Add credits-----------------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_DOWN || App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_DOWN || App->input->Controller1[SDL_CONTROLLER_BUTTON_Y] == KEY_DOWN || App->input->Controller2[SDL_CONTROLLER_BUTTON_Y] == KEY_DOWN)
	{
		App->audio->ControlSFX(coinsSfx, PLAY_AUDIO);
		if (credits < 99)
			credits += 1;
	}

	//-------Spawn players--------------------------------------------

	//----------------------1 pressed---------------------
	if (App->input->keyboard[SDL_SCANCODE_1] == KEY_DOWN &&
		App->input->keyboard[SDL_SCANCODE_F5] == KEY_IDLE &&
		App->input->keyboard[SDL_SCANCODE_F6] == KEY_IDLE &&
		App->input->keyboard[SDL_SCANCODE_F7] == KEY_IDLE &&
		App->input->keyboard[SDL_SCANCODE_F8] == KEY_IDLE || App->input->Controller1[SDL_CONTROLLER_BUTTON_X])
	{
		if (App->player1->isActived == false && credits > 0)
		{
			switch (currentScene)
			{
			case TITLE_SCENE:
				LOG("F1");
				credits -= 1;
				HideUi();
				App->player1->isActived = true;
				App->player1->lives = 2;
				break;
			case STAGE_SCENE:
				credits -= 1;
				App->player1->isActived = true;
				App->player1->lives = 2;
				if (App->player1->enabled == true) {
					App->player1->Reappear();
				}
				else {
					App->player1->Enable();
				}
				
				break;
			case CONTINUE_SCENE:
				credits -= 1;
				App->player1->isActived = true;
				App->player1->lives = 2;
				break;
			default:
				LOG("F1 default");
				break;
			}
		}
	}
	//----------------------2 pressed---------------------
	if (App->input->keyboard[SDL_SCANCODE_2] == KEY_DOWN && 
		(App->input->keyboard[SDL_SCANCODE_F5] == KEY_IDLE &&
		App->input->keyboard[SDL_SCANCODE_F6] == KEY_IDLE &&
		App->input->keyboard[SDL_SCANCODE_F7] == KEY_IDLE &&
		App->input->keyboard[SDL_SCANCODE_F8] == KEY_IDLE ) || App->input->Controller2[SDL_CONTROLLER_BUTTON_X])
	{
		switch (currentScene)
		{
		case TITLE_SCENE:
			
			if (credits >= 2)
			{
				HideUi();
				App->player1->isActived = true;
				App->player2->isActived = true;
				App->player1->lives = 2;
				App->player2->lives = 2;
				credits -= 2;
			}
			break;
		case STAGE_SCENE:
			if (credits > 0 && App->player2->isActived == false)
			{
				App->player2->isActived = true;
				App->player2->lives = 2;

				if (App->player2->enabled == true) {
					App->player2->Reappear();
				}
				else {
					App->player2->Enable();
				}
				
				credits -= 1;
			}
			break;
		case CONTINUE_SCENE:
			if (credits > 0)
			{
				App->player2->isActived = true;
				credits -= 1;
			}
			break;
		default:
			LOG("F2 default");
			break;
		}
	}

	

	str_score_p1 = new char[MAX_NUMBERS_SCORE];
	str_score_p2 = new char[MAX_NUMBERS_SCORE];
	str_lives_p1 = new char[4];
	str_lives_p2 = new char[4];
	str_credits = new char[20];

	snprintf(str_lives_p1, 4 * sizeof(str_lives_p1), "%d", App->player1->lives);
	snprintf(str_lives_p2, 4 * sizeof(str_lives_p2), "%d", App->player2->lives);
	snprintf(str_score_p1, 4 * sizeof(str_score_p1), "%d", App->player1->score);
	snprintf(str_score_p2, 4 * sizeof(str_score_p2), "%d", App->player2->score);
	if (credits<10)
		snprintf(str_credits, 4 * sizeof(str_credits), "CREDITS 0%d", credits);
	else
		snprintf(str_credits, 4 * sizeof(str_credits), "CREDITS %d", credits);

	//Draw UI----------------------------------------------------------------------------------------//

	if (showUI == true) {
		//------Common--------------------------------------------------
		App->fonts->BlitText(208, 216, 0, str_credits);
		if (App->player1->isActived == true || App->player2->isActived == true)
		App->render->Blit(uiTex, 112, 16, &top);
		//------Player 1------------------------------------------------

		if (App->player1->isActived == true) {

			//-----------Static UI-----------------------
			App->render->Blit(uiTex, 16, 16, &lives_score_p1);
			App->render->Blit(uiTex, 24, 208, &pow);
			if (App->unit1->IsEnabled())
			{
				powBar.w = (int)(64 * App->unit1->power);
				App->render->Blit(uiTex, 48, 210, &powBar);
			}
			//-----------Variable UI--------------------
			App->fonts->BlitText(48, 24, 0, str_lives_p1);
			if (App->player1->score == 0) {
				App->fonts->BlitText(72, 16, 0, "00");
			}
			else {
				App->fonts->BlitText(88 - 8 * strlen(str_score_p1), 16, 0, str_score_p1);
			}
		}
		//------Player 2----------------------------------------------

		if (App->player2->isActived == true) {

			//-----------Static UI----------------------
			App->render->Blit(uiTex, 256, 16, &live_score_p2);
			App->render->Blit(uiTex, 184, 208, &pow);
			if (App->unit2->IsEnabled())
			{
				powBar.w = (int)(64 * App->unit2->power);
				App->render->Blit(uiTex, 208, 210, &powBar);
			}
			//-----------Variable UI--------------------
			App->fonts->BlitText(264, 24, 0, str_lives_p2); //lives player 2

			if (App->player2->score == 0) {
				App->fonts->BlitText(256, 16, 0, "00");
			}
			else {
				App->fonts->BlitText(272 - 8 * strlen(str_score_p2), 16, 0, str_score_p2);
			}
		}
	}


	delete[](str_score_p1);
	delete[](str_score_p2);
	delete[](str_lives_p1);
	delete[](str_lives_p2);
	delete[](str_credits);
	str_score_p1 = nullptr;
	str_score_p2 = nullptr;
	str_lives_p1 = nullptr;
	str_lives_p2 = nullptr;
	str_credits = nullptr;

	return UPDATE_CONTINUE;
}

void ModuleUI::ShowUi() {
	if (showUI == false) {
		showUI = true;
	}
	
}
void ModuleUI::HideUi() {
	if (showUI == true) {
		showUI = false;
	}
}