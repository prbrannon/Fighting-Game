#ifndef MENU_H
#define MENU_H

#include "Scene.h"

struct Button : GameObject
{
	Button* left;
	Button* right;
	Button* up;
	Button* down;

	SceneID destination;
	bool dest_is_menu;

	Command command;

	Button()
	{
		left = NULL;
		right = NULL;
		up = NULL;
		down = NULL;

		destination = SceneID::None;
		dest_is_menu = false;

		command = Command::None;
	}
};

class Menu : public Scene
{
public:
	Menu(void)
	{
		buttons = ArrayList<Button>();

		playerOneSelection = NULL;
		playerTwoSelection = NULL;

		selectionOneBox = new GameObject();
		selectionTwoBox = new GameObject();

		transition = new SceneTransition();
	}

	~Menu()
	{
		delete selectionOneBox;
		delete selectionTwoBox;

		delete transition;
	}

	// Override the render function to draw buttons over the scene
	void Render() override
	{
		// Call base class to render objects...
		Scene::Render();

		// Render each Button...
		for(int i = 0; i < buttons.GetLength(); i++)
		{
			//RenderObject(buttons[i]);
			buttons[i].Render(textures[buttons[i].GetTextureID()].GetTextureID());
		}
		/*
		RenderObject(*selectionOneBox);
		RenderObject(*selectionTwoBox);
		*/

		selectionOneBox->Render(textures[selectionOneBox->GetTextureID()].GetTextureID());
		selectionTwoBox->Render(textures[selectionTwoBox->GetTextureID()].GetTextureID());


		return;
	}

	// Moves the player's selection between the different buttons created by child classes
	void PlayerInput(const PlayerID& player, const Input &input, const bool& key_down) override
	{
		if(playerOneSelection == NULL)
			return;

		// Check if the button is key pressed down
		if(key_down == false)
			return;

		if(input == Input::Back)
		{
			if(playerOneSelection->left != NULL)
			{
				playerOneSelection = playerOneSelection->left;
				MoveSelectionBox(selectionOneBox, *playerOneSelection);
				engine->play2D("Menu/menuMove.wav", false, false, false, irrklang::ESM_NO_STREAMING, false);
			}
		}
		else if(input == Input::Forward)
		{
			if(playerOneSelection->right != NULL)
			{
				playerOneSelection = playerOneSelection->right;
				MoveSelectionBox(selectionOneBox, *playerOneSelection);
				engine->play2D("Menu/menuMove.wav", false, false, false, irrklang::ESM_NO_STREAMING, false);
			}
		}
		else if(input == Input::Up)
		{
			if(playerOneSelection->up != NULL)
			{
				playerOneSelection = playerOneSelection->up;
				MoveSelectionBox(selectionOneBox, *playerOneSelection);
				engine->play2D("Menu/menuMove.wav", false, false, false, irrklang::ESM_NO_STREAMING, false);
			}
		}
		else if(input == Input::Down)
		{
			if(playerOneSelection->down != NULL)
			{
				playerOneSelection = playerOneSelection->down;
				MoveSelectionBox(selectionOneBox, *playerOneSelection);
				engine->play2D("Menu/menuMove.wav", false, false, false, irrklang::ESM_NO_STREAMING, false);
			}
		}
		else if(input == Input::Punch)
		{
			PlayerSelect();
			engine->play2D("Menu/menuSelect.wav", false, false, false, irrklang::ESM_NO_STREAMING, false);
		}
		else if(input == Input::Kick)
		{
			CancelMenu();
			engine->play2D("Menu/menuCancel.wav", false, false, false, irrklang::ESM_NO_STREAMING, false);
		}
	}

	SceneTransition* GetTransition(){ return transition; };

protected:
	ArrayList<Button> buttons;

	Button* playerOneSelection;
	Button* playerTwoSelection;

	GameObject* selectionOneBox;
	GameObject* selectionTwoBox;

	SceneTransition* transition;

	// Move and scale a selection box to be over the given button
	void MoveSelectionBox(GameObject* box, Button b)
	{
		box->SetPosX(b.GetPosX());
		box->SetPosY(b.GetPosY());
		box->SetScaledWidth(b.GetScaledWidth());
		box->SetScaledHeight(b.GetScaledHeight());
	}

	// Player activates the currently selected button
	virtual void PlayerSelect()
	{
		if(playerOneSelection->destination != SceneID::None)
		{
			// Set the destination scene (menu or game scene)
			transition->next_scene = playerOneSelection->destination;

			// Set the flag for either menu or game scene
			if(playerOneSelection->dest_is_menu)
			{
				transition->menu_scene_set = true;
			}
			else
			{
				transition->game_scene_set = true;
			}
		}
	}

	// Add a button to the button array with the desired settings.
	// Pre: None
	// Post: Button is added to the array. The directional movement is NOT set.
	void AddButton(int textureID, float x, float y, int width, int height, SceneID dest, bool dest_is_menu)
	{
		Button b = Button();
		b.SetTextureID(textureID);
		b.SetPosX(x);
		b.SetPosY(y);
		b.SetScaledWidth(width);
		b.SetScaledHeight(height);
		b.destination = dest;
		b.dest_is_menu = dest_is_menu;

		buttons.Add(b);
	}

	virtual void CancelMenu()
	{
		transition->next_scene = SceneID::CancelMenu;
		transition->menu_scene_set = true;
	}
};

#endif