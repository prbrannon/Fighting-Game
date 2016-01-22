#ifndef MAINMENU_H
#define MAINMENU_H

#include "Menu.h"

#include "Globals.h"

class MainMenu : public Menu
{
public:
	MainMenu(void)
	{
		scene_id = SceneID::MainMenu;
	}

	// Override function from Scene.h
	void PlayerInput(const PlayerID& player, const Input &input, const bool& key_down) override
	{
		Menu::PlayerInput(player, input, key_down);
	}

	void Update() override
	{
		return;
	}

	void Load() override
	{
		engine->play2D("Menu//mainMenuTheme.wav", true, false, false, irrklang::ESM_NO_STREAMING, false);

		LoadTextures();

		Scene::SetRenderLayers(1);

		// Buttons for menu
		buttons.Resize(4);
		
		// Versus Mode
		AddButton(0, 125, 245, 200, 75, SceneID::MainMenuVS, true);

		// Training Mode
		AddButton(1, 125, 170, 200, 75, SceneID::MainMenuTraining, true);

		// Settings
		AddButton(2, 125, 95, 200, 75, SceneID::MainMenuSettings, true);

		// Quit
		AddButton(3, 225, 20, 200, 75, SceneID::Quit, false);


		buttons[0].down = &buttons[1];
		buttons[0].up = &buttons[3];

		buttons[1].down = &buttons[2];
		buttons[1].up = &buttons[0];

		buttons[2].down = &buttons[3];
		buttons[2].up = &buttons[1];

		buttons[3].down = &buttons[0];
		buttons[3].up = &buttons[2];

		// Selection for the currently selected button
		selectionOneBox->SetTextureID(4);
		playerOneSelection = &buttons[0]; // Sets the cursor to a button
		Menu::MoveSelectionBox(selectionOneBox, buttons[0]); // Sets the box to be over a button and scaled to button dimensions

		GameObject object;
		// TODO: loading the background from a different size window breaks the background
		// Background
		object.SetTextureID(5);
		object.SetPosX(0);
		object.SetPosY(0);
		object.SetScaledWidth(WINDOW_WIDTH);
		object.SetScaledHeight(WINDOW_HEIGHT);
		objects[0].Add(object);
		
		// Title
		object.SetTextureID(6);
		object.SetPosX(WINDOW_WIDTH * 0.15);
		object.SetPosY(WINDOW_HEIGHT * 0.65f);
		object.SetScaledWidth(WINDOW_WIDTH * 0.65f);
		object.SetScaledHeight(WINDOW_HEIGHT * 0.35f);
		objects[0].Add(object);
	}

protected:
	virtual void PlayerSelect() override
	{
		Menu::PlayerSelect(); // Selects the current button for P1 and goes to a scene transition
	}

	
	virtual void CancelMenu() override
	{
		// Move the selection box to the quit option
		playerOneSelection = &buttons[3];
		Menu::MoveSelectionBox(selectionOneBox, buttons[3]);
	}
	
private:
	void LoadTextures()
	{
		// Resize array now so that resizing doesn't lose OpenGL context for textures
		textures.reserve(7);

		Texture t = Texture();

		textures.push_back(t);
		textures[0].LoadTextureFromFile("Menu/versus.png");

		textures.push_back(t);
		textures[1].LoadTextureFromFile("Menu/training.png");

		textures.push_back(t);
		textures[2].LoadTextureFromFile("Menu/settings.png");

		textures.push_back(t);
		textures[3].LoadTextureFromFile("Menu/quit.png");

		textures.push_back(t);
		textures[4].LoadTextureFromFile("Menu/selector.png");

		textures.push_back(t);
		textures[5].LoadTextureFromFile("Menu/background.png");

		textures.push_back(t);
		textures[6].LoadTextureFromFile("Menu/title.png");
	}
};

class MainMenuVS : public Menu
{
public:
	MainMenuVS(void)
	{
		scene_id = SceneID::MainMenuVS;
	}

	// Override function from Scene.h
	void PlayerInput(const PlayerID& player, const Input &input, const bool& key_down) override
	{
		Menu::PlayerInput(player, input, key_down);
	}

	void Update() override
	{
		return;
	}

	void Load() override
	{
		LoadTextures();

		Scene::SetRenderLayers(1); // TODO: Add additional layer for a gray half-alpha texture to fade the background? -Shawn

		// Buttons for menu
		buttons.Resize(2);
		
		// Player vs Player
		AddButton(0, 325, 245, 200, 75, SceneID::CharacterSelect, false);

		// Player vs Computer
		AddButton(1, 325, 170, 200, 75, SceneID::None, true);

		buttons[0].down = &buttons[1];
		buttons[0].up = &buttons[1];

		buttons[1].down = &buttons[0];
		buttons[1].up = &buttons[0];

		// Selection for the currently selected button
		selectionOneBox->SetTextureID(2);
		playerOneSelection = &buttons[0]; // Sets the cursor to a button
		Menu::MoveSelectionBox(selectionOneBox, buttons[0]); // Sets the box to be over a button and scaled to button dimensions
	}

protected:
	virtual void PlayerSelect() override
	{
		Menu::PlayerSelect(); // Selects the current button for P1 and goes to a scene transition
	}

	virtual void CancelMenu() override
	{
		Menu::CancelMenu();
	}
	
private:
	void LoadTextures()
	{
		// Resize array now so that resizing doesn't lose OpenGL context for textures
		textures.reserve(3);

		Texture t = Texture();

		textures.push_back(t);
		textures[0].LoadTextureFromFile("Menu/player vs player.png");

		textures.push_back(t);
		textures[1].LoadTextureFromFile("Menu/player vs computer.png");
		
		textures.push_back(t);
		textures[2].LoadTextureFromFile("Menu/selector.png");
	}
};

class MainMenuTraining : public Menu
{
public:
	MainMenuTraining(void)
	{
		scene_id = SceneID::MainMenuTraining;
	}

	// Override function from Scene.h
	void PlayerInput(const PlayerID& player, const Input &input, const bool& key_down) override
	{
		Menu::PlayerInput(player, input, key_down);
	}

	void Update() override
	{
		return;
	}

	void Load() override
	{
		LoadTextures();

		Scene::SetRenderLayers(1); // TODO: Add additional layer for a gray half-alpha texture to fade the background? -Shawn

		// Buttons for menu
		buttons.Resize(2);
		
		// Player vs Player
		AddButton(0, 325, 170, 200, 75, SceneID::None, true);

		// Player vs Computer
		AddButton(1, 325, 95, 200, 75, SceneID::None, true);

		buttons[0].down = &buttons[1];
		buttons[0].up = &buttons[1];

		buttons[1].down = &buttons[0];
		buttons[1].up = &buttons[0];

		// Selection for the currently selected button
		selectionOneBox->SetTextureID(2);
		playerOneSelection = &buttons[0]; // Sets the cursor to a button
		Menu::MoveSelectionBox(selectionOneBox, buttons[0]); // Sets the box to be over a button and scaled to button dimensions
	}

protected:
	virtual void PlayerSelect() override
	{
		Menu::PlayerSelect(); // Selects the current button for P1 and goes to a scene transition
	}

	virtual void CancelMenu() override
	{
		Menu::CancelMenu();
	}

private:
	void LoadTextures()
	{
		// Resize array now so that resizing doesn't lose OpenGL context for textures
		textures.reserve(3);

		Texture t = Texture();

		textures.push_back(t);
		textures[0].LoadTextureFromFile("Menu/player vs player.png");

		textures.push_back(t);
		textures[1].LoadTextureFromFile("Menu/player vs computer.png");
		
		textures.push_back(t);
		textures[2].LoadTextureFromFile("Menu/selector.png");
	}
};

class MainMenuSettings : public Menu
{
public:
	MainMenuSettings(void)
	{
	}

	// Override function from Scene.h
	void PlayerInput(const PlayerID& player, const Input &input, const bool& key_down) override
	{
		Menu::PlayerInput(player, input, key_down);
	}

	void Update() override
	{
		return;
	}

	void Load() override
	{
		LoadTextures();

		Scene::SetRenderLayers(1); // TODO: Add additional layer for a gray half-alpha texture to fade the background? -Shawn

		// Buttons for menu
		buttons.Resize(1);
		
		// Button Configuration
		AddButton(0, 325, 95, 200, 75, SceneID::None, true);

		// Selection for the currently selected button
		selectionOneBox->SetTextureID(1);
		playerOneSelection = &buttons[0]; // Sets the cursor to a button
		Menu::MoveSelectionBox(selectionOneBox, buttons[0]); // Sets the box to be over a button and scaled to button dimensions
	}

protected:
	virtual void PlayerSelect() override
	{
		Menu::PlayerSelect(); // Selects the current button for P1 and goes to a scene transition
	}

	virtual void CancelMenu() override
	{
		Menu::CancelMenu();
	}

private:
	void LoadTextures()
	{
		// Resize array now so that resizing doesn't lose OpenGL context for textures
		textures.reserve(2);

		Texture t = Texture();

		textures.push_back(t);
		textures[0].LoadTextureFromFile("Menu/buttonconfig.png");
		
		textures.push_back(t);
		textures[1].LoadTextureFromFile("Menu/selector.png");
	}
};

#endif