// Singleton SceneManager class that handles the updating, rendering, and swapping for scenes

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "ArrayList.h"
#include "Scene.h"

#include "SceneID.h"
#include "TestMenu.h"
#include "TestScene.h"
#include "TitleScreen.h"
#include "MainMenu.h"
#include "CharacterSelect.h"
#include "Fight.h"
#include "Pause.h"
#include "EndGame.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager(void);

	void PlayerInput(const PlayerID& player, const Input &input, const bool& key_down);

	void Update();

	void Render();

	void ChangeGameScene(SceneID scene);
	void ModifyMenuStack(SceneID scene);

	Menu& GetCurrentMenu();

private:
	Fight* game_scene;

	std::vector<Menu*> menu_stack;

	bool menu_active;

	void EmptyMenuStack();
};

#endif