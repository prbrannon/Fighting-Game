#ifndef CHARACTERSELECT_H
#define CHARACTERSELECT_H

#include "Menu.h"

class CharacterSelect : public Menu
{
public:
	CharacterSelect(void)
	{
		scene_id = SceneID::CharacterSelect;

		playerOneSelected = false;
		playerTwoSelected = false;
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
		buttons.Resize(5);
		
		// Fondu - Top
		AddButton(0, 245, 315, 150, 150, SceneID::None, false);
		buttons[0].command = Command::Fondu;

		// Next Gen - Left
		AddButton(1, 95, 165, 150, 150, SceneID::None, false);
		buttons[1].command = Command::NextGen;

		// Wombo Combo - Right
		AddButton(2, 395, 165, 150, 150, SceneID::None, false);
		buttons[2].command = Command::WomboCombo;

		// Random - Bottom
		AddButton(3, 245, 15, 150, 150, SceneID::None, false);
		buttons[3].command = Command::Random;

		// Back
		AddButton(4, 245, 165, 150, 150, SceneID::MainMenu, false);

		buttons[0].up = &buttons[3];
		buttons[0].down = &buttons[4];
		buttons[0].left = &buttons[1];
		buttons[0].right = &buttons[2];

		buttons[1].up = &buttons[0];
		buttons[1].down = &buttons[3];
		buttons[1].left = &buttons[2];
		buttons[1].right = &buttons[4];

		buttons[2].up = &buttons[0];
		buttons[2].down = &buttons[3];
		buttons[2].left = &buttons[4];
		buttons[2].right = &buttons[1];

		buttons[3].up = &buttons[4];
		buttons[3].down = &buttons[0];
		buttons[3].left = &buttons[1];
		buttons[3].right = &buttons[2];

		buttons[4].up = &buttons[0];
		buttons[4].down = &buttons[3];
		buttons[4].left = &buttons[1];
		buttons[4].right = &buttons[2];

		// Selection for the currently selected button
		// Player One
		selectionOneBox->SetTextureID(5);
		playerOneSelection = &buttons[4]; // Sets the cursor to a button
		Menu::MoveSelectionBox(selectionOneBox, buttons[4]); // Sets the box to be over a button and scaled to button dimensions

		// Player Two
		// TODO: activate this when 2p is working
		/*
		selectionTwoBox->SetTextureID(6);
		playerTwoSelection = &buttons[4]; // Sets the cursor to a button
		Menu::MoveSelectionBox(selectionTwoBox, buttons[4]); // Sets the box to be over a button and scaled to button dimensions
		*/

		GameObject object;
		// Background
		object.SetTextureID(7);
		object.SetPosX(0);
		object.SetPosY(0);
		object.SetScaledWidth(WINDOW_WIDTH);
		object.SetScaledHeight(WINDOW_HEIGHT);
		objects[0].Add(object);
	}

protected:
	virtual void PlayerSelect() override
	{
		// Write the player choice to static global
		if(playerOneSelection->command != Command::None)
		{
			player_one_char = playerOneSelection->command;
			playerOneSelected = true;

			// TODO: Add a player two select/deselect option
			player_two_char = playerOneSelection->command;
			playerTwoSelected = true;

		}

		if(playerOneSelected && playerTwoSelected)
		{
			transition->next_scene = SceneID::Fight;
			transition->game_scene_set = true;
		}
		else
		{
			Menu::PlayerSelect(); // Selects the current button for P1 and goes to a scene transition
		}
	}

	virtual void CancelMenu() override
	{
		playerOneSelection = &buttons[4];
		Menu::MoveSelectionBox(selectionOneBox, buttons[4]);
	}

private:

	bool playerOneSelected;
	bool playerTwoSelected;

	void LoadTextures()
	{
		// Resize array now so that resizing doesn't lose OpenGL context for textures
		textures.reserve(8);

		Texture t = Texture();

		textures.push_back(t);
		textures[0].LoadTextureFromFile("CharacterSelect/cs_fondu.png");

		textures.push_back(t);
		textures[1].LoadTextureFromFile("CharacterSelect/cs_nextGen.png");

		textures.push_back(t);
		textures[2].LoadTextureFromFile("CharacterSelect/cs_womboCombo.png");

		textures.push_back(t);
		textures[3].LoadTextureFromFile("CharacterSelect/cs_random.png");

		textures.push_back(t);
		textures[4].LoadTextureFromFile("CharacterSelect/cs_mainMenu.png");

		textures.push_back(t);
		textures[5].LoadTextureFromFile("CharacterSelect/playerOneSelector.png");

		textures.push_back(t);
		textures[6].LoadTextureFromFile("CharacterSelect/playerTwoSelector.png");

		textures.push_back(t);
		textures[7].LoadTextureFromFile("CharacterSelect/characterSelect.png");
	}

	void LoadSounds()
	{
		engine->play2D("CharacterSelect//characterSelectTheme.wav", true, false, false, irrklang::ESM_NO_STREAMING, false);
	}
};

#endif