#ifndef PAUSE_H
#define PAUSE_H

#include "Menu.h"

class Pause : public Menu
{
public:
	Pause(void)
	{
		scene_id = SceneID::Pause;
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
		Scene::SetRenderLayers(1);

		LoadSounds();

		// Buttons for menu
		buttons.Resize(4);

		
		// From pause to unpause (aka resume fighting)
		AddButton(1, 50, 350, 200, 100, SceneID::Unpause, true);

		// From pause to main menu
		AddButton(2, 50, 250, 200, 100, SceneID::MainMenu, false);

		// From pause to character select
		AddButton(3, 50, 150, 200, 100, SceneID::CharacterSelect, false);

		// Quit
		AddButton(4, 50, 50, 200, 100, SceneID::Quit, false);

		buttons[0].down = &buttons[1];
		buttons[0].up = &buttons[3];

		buttons[1].down = &buttons[2];
		buttons[1].up = &buttons[0];

		buttons[2].down = &buttons[3];
		buttons[2].up = &buttons[1];

		buttons[3].down = &buttons[0];
		buttons[3].up = &buttons[2];
		

		// Selection for the currently selected button
		selectionOneBox->SetTextureID(5);
		playerOneSelection = &buttons[0]; // Sets the cursor to a button
		Menu::MoveSelectionBox(selectionOneBox, buttons[0]); // Sets the box to be over a button and scaled to button dimensions

		GameObject object;

		// Pause Title
		object.SetTextureID(0);
		object.SetPosX(WINDOW_WIDTH * 0.50f);
		object.SetPosY(WINDOW_HEIGHT * 0.25f);
		object.SetScaledWidth(WINDOW_WIDTH * 0.50f);
		object.SetScaledHeight(WINDOW_HEIGHT * 0.50f);
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
		playerOneSelection = &buttons[0];
		Menu::MoveSelectionBox(selectionOneBox, buttons[0]);
	}

private:
	void LoadTextures()
	{
		// Resize array now so that resizing doesn't lose OpenGL context for textures
		textures.reserve(6);

		Texture t = Texture();

		textures.push_back(t);
		textures[0].LoadTextureFromFile("Pause/paused.png");

		textures.push_back(t);
		textures[1].LoadTextureFromFile("Pause/resume.png");

		textures.push_back(t);
		textures[2].LoadTextureFromFile("Pause/mainMenu.png");

		textures.push_back(t);
		textures[3].LoadTextureFromFile("Pause/characterSelect.png");

		textures.push_back(t);
		textures[4].LoadTextureFromFile("Pause/quit.png");

		textures.push_back(t);
		textures[5].LoadTextureFromFile("Pause/selector.png");
	}

	void LoadSounds()
	{
		// NO SOUNDS YET
		// engine->play2D("Menu/mainMenuTheme.wav", true, false, false, irrklang::ESM_NO_STREAMING, false);
	}
};
#endif