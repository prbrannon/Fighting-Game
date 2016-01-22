#include "SceneManager.h"

SceneManager::SceneManager()
{
	game_scene = new Fight();

	menu_active = false;

	ChangeGameScene(SceneID::None);
	ModifyMenuStack(SceneID::None);
}

SceneManager::~SceneManager(void)
{
	delete game_scene;

	for(int i = 0; i < menu_stack.size(); i++)
	{
		delete menu_stack[i];
	}
}

void SceneManager::PlayerInput(const PlayerID& player, const Input &input, const bool& key_down)
{
	if(menu_active == true)
		GetCurrentMenu().PlayerInput(player, input, key_down);
	else
		game_scene->PlayerInput(player, input, key_down);
}

void SceneManager::Update()
{
	if(menu_stack.size() > 0)
	{
		// Update the menu stack
		for(int i = 0; i < menu_stack.size(); i++)
		{
			if(menu_stack[i]->IsRunning() == true)
			{
				menu_stack[i]->Update();
			}
		}

		// MENU SCENE->GAME SCENE
		if(GetCurrentMenu().GetTransition()->game_scene_set)
		{
			ChangeGameScene(GetCurrentMenu().GetTransition()->next_scene);

			return;
		}
		// MENU SCENE->MENU SCENE
		if(GetCurrentMenu().GetTransition()->menu_scene_set)
		{
			ModifyMenuStack(GetCurrentMenu().GetTransition()->next_scene);

			return;
		}
	}
	
	// Update the current scene
	if(game_scene->IsRunning() == true)
	{
		game_scene->Update();
	}
}

void SceneManager::Render()
{
	// Render game scene
	if(game_scene->IsRendering())
		game_scene->Render();

	// Render menu stack backwards on top of game scene
	for(int i = 0; i < menu_stack.size(); i++)
	{
		if(menu_stack[i]->IsRendering())
			menu_stack[i]->Render();
	}
}

void SceneManager::ChangeGameScene(SceneID scene)
{
	engine->stopAllSounds();

	if(game_scene != NULL)
	{
		game_scene->SetRunning(false);
		game_scene->SetRendering(false);
		game_scene->Unload();
	}

	// The destination determines what scene you want to go to
	switch(scene)
	{
		case SceneID::TitleScreen:
			EmptyMenuStack();
			ModifyMenuStack(SceneID::TitleScreen);

			break;
		case SceneID::MainMenu:
			EmptyMenuStack();
			ModifyMenuStack(SceneID::MainMenu);
			
			break;
		case SceneID::CharacterSelect:
			EmptyMenuStack();
			ModifyMenuStack(SceneID::CharacterSelect);

			break;
		case SceneID::Fight:
			delete game_scene;
			EmptyMenuStack();
			game_scene = new Fight();

			// load base textures such as the HUD
			game_scene->Load();

			// Load the fighter for each player (all moves/graphics/sounds)
			game_scene->SetFighter(player_one_char, PlayerID::PlayerOne);
			game_scene->SetFighter(player_two_char, PlayerID::PlayerTwo);

			game_scene->SetRunning(true);
			game_scene->SetRendering(true);

			menu_active = false;

			break;
		case SceneID::Quit:
			EmptyMenuStack();
			glutDestroyWindow(0);
			exit (0);

			break;
		default:
			delete game_scene;
			game_scene = new Fight();

			break;
	}
}

void SceneManager::ModifyMenuStack(SceneID scene)
{
	// The destination determines what scene you want to go to
	switch(scene)
	{
		case SceneID::EndGame:
			menu_stack.push_back(new EndGame());
			GetCurrentMenu().Load();
			GetCurrentMenu().SetRunning(true);
			GetCurrentMenu().SetRendering(true);

			menu_active = true;

			break;
		case SceneID::TitleScreen:
			menu_stack.push_back(new TitleScreen());
			GetCurrentMenu().Load();
			GetCurrentMenu().SetRunning(true);
			GetCurrentMenu().SetRendering(true);

			menu_active = true;

			break;
		case SceneID::MainMenu:
			menu_stack.push_back(new MainMenu());
			GetCurrentMenu().Load();
			GetCurrentMenu().SetRunning(true);
			GetCurrentMenu().SetRendering(true);

			menu_active = true;
			
			break;
		case SceneID::MainMenuVS:
			menu_stack.push_back(new MainMenuVS());
			GetCurrentMenu().Load();
			GetCurrentMenu().SetRunning(true);
			GetCurrentMenu().SetRendering(true);

			menu_active = true;
			
			break;
		case SceneID::MainMenuTraining:
			menu_stack.push_back(new MainMenuTraining());
			GetCurrentMenu().Load();
			GetCurrentMenu().SetRunning(true);
			GetCurrentMenu().SetRendering(true);

			menu_active = true;
			
			break;
		case SceneID::MainMenuSettings:
			menu_stack.push_back(new MainMenuSettings());
			GetCurrentMenu().Load();
			GetCurrentMenu().SetRunning(true);
			GetCurrentMenu().SetRendering(true);

			menu_active = true;
			
			break;
		case SceneID::CharacterSelect:
			menu_stack.push_back(new CharacterSelect());
			GetCurrentMenu().Load();
			GetCurrentMenu().SetRunning(true);
			GetCurrentMenu().SetRendering(true);

			menu_active = true;

			break;
		case SceneID::Pause:
			if (game_scene != NULL && game_scene->IsRunning())
			{
				game_scene->SetRunning(false);
				menu_stack.push_back(new Pause());
				GetCurrentMenu().Load();
				GetCurrentMenu().SetRunning(true);
				GetCurrentMenu().SetRendering(true);

				menu_active = true;
			}

			break;
		case SceneID::Unpause:
			GetCurrentMenu().SetRunning(false);
			GetCurrentMenu().SetRendering(false);
			EmptyMenuStack();
			game_scene->SetRunning(true);

			menu_active = false;

			break;
		case SceneID::CancelMenu:
			GetCurrentMenu().SetRunning(false);
			GetCurrentMenu().SetRendering(false);
			GetCurrentMenu().Unload();
			delete &GetCurrentMenu();
			menu_stack.pop_back();

			GetCurrentMenu().GetTransition()->Reset();

			break;
		default:
			break;
	}
}

Menu& SceneManager::GetCurrentMenu()
{
	return *menu_stack[menu_stack.size() - 1];
}

void SceneManager::EmptyMenuStack()
{
	// Delete the menu objects. Unload textures first.
	for(int i = 0; i < menu_stack.size(); i++)
	{
		GetCurrentMenu().SetRunning(false);
		GetCurrentMenu().SetRendering(false);
		menu_stack[i]->Unload();
		delete menu_stack[i];
	}

	// Clear the pointers
	menu_stack.clear();
}