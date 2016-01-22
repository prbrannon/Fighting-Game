#ifndef ENDGAME_H
#define ENDGAME_H

#include "Menu.h"

class EndGame : public Menu
{
public:
	EndGame(void)
	{
		scene_id = SceneID::EndGame;
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

		// Rematch - same fighters, reset fight scene
		AddButton(0, 100, 225, 200, 100, SceneID::Fight, true);

		// Select new characters - goto char select scene
		AddButton(1, 350, 225, 200, 100, SceneID::CharacterSelect, true);

		// Goto main menu
		AddButton(2, 100, 125, 200, 100, SceneID::MainMenu, true);

		// Quit
		AddButton(3, 350, 125, 200, 100, SceneID::Quit, false);

		buttons[0].down = &buttons[2];
		buttons[0].up = &buttons[2];
		buttons[0].left = &buttons[1];
		buttons[0].right = &buttons[1];

		buttons[1].down = &buttons[3];
		buttons[1].up = &buttons[3];
		buttons[1].left = &buttons[0];
		buttons[1].right = &buttons[0];

		buttons[2].down = &buttons[0];
		buttons[2].up = &buttons[0];
		buttons[2].left = &buttons[3];
		buttons[2].right = &buttons[3];

		buttons[3].down = &buttons[1];
		buttons[3].up = &buttons[1];
		buttons[3].left = &buttons[2];
		buttons[3].right = &buttons[2];

		// Selection for the currently selected button
		selectionOneBox->SetTextureID(4);
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
		// Move the selection box to the quit option
		playerOneSelection = &buttons[3];
		Menu::MoveSelectionBox(selectionOneBox, buttons[3]);
	}

private:
	void LoadTextures()
	{
		// Resize array now so that resizing doesn't lose OpenGL context for textures
		textures.reserve(5);

		Texture t = Texture();

		textures.push_back(t);
		textures[0].LoadTextureFromFile("EndGame/rematch.png");

		textures.push_back(t);
		textures[1].LoadTextureFromFile("EndGame/mainMenu.png");

		textures.push_back(t);
		textures[2].LoadTextureFromFile("EndGame/characterSelect.png");

		textures.push_back(t);
		textures[3].LoadTextureFromFile("EndGame/quit.png");

		textures.push_back(t);
		textures[4].LoadTextureFromFile("EndGame/selector.png");
	}

	void LoadSounds()
	{
		// NO SOUND YET
		// engine->play2D("Menu/mainMenuTheme.wav", true, false, false, irrklang::ESM_NO_STREAMING, false);
	}
};
#endif