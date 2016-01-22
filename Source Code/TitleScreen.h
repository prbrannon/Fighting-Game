#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "Menu.h"

#include "Globals.h"

class TitleScreen : public Menu
{
	float travelDist;
	GameObject object;
	int flashContinue;

public:
	TitleScreen(void)
	{
		flashContinue = 0;
		travelDist = 0;
		scene_id = SceneID::TitleScreen;
	}

	// Override function from Scene.h
	void PlayerInput(const PlayerID& player, const Input &input, const bool& key_down) override
	{
		if(key_down == true)
		{
			transition->next_scene = SceneID::MainMenu;
			transition->game_scene_set = true;
		}
	}

	void Update() override
	{
		// Background
		object.SetTextureID(0);
		object.SetPosX(0);
		object.SetPosY(0);
		object.SetScaledWidth(WINDOW_WIDTH);
		object.SetScaledHeight(WINDOW_HEIGHT);
		objects[0].Add(object);

		if(travelDist <= 435)
		{
			travelDist += 3;
			// TitleBlack falling
			object.SetTextureID(2);
			object.SetPosX(WINDOW_WIDTH * 0.15);
			object.SetPosY((WINDOW_HEIGHT * 0.65f) + 300 - travelDist);
			object.SetScaledWidth(WINDOW_WIDTH * 0.65f);
			object.SetScaledHeight(WINDOW_HEIGHT * 0.35f);
			objects[0].Add(object);
		}
		else
		{
			// flash of white
			object.SetTextureID(3);
			object.SetPosX(-WINDOW_WIDTH / 2);
			object.SetPosY(-WINDOW_HEIGHT / 2);
			object.SetScaledWidth(WINDOW_WIDTH * 2);
			object.SetScaledHeight(WINDOW_HEIGHT * 2);
			objects[0].Add(object);

			// Title main standstill
			object.SetTextureID(1);
			object.SetPosX(WINDOW_WIDTH * 0.075);
			object.SetPosY(WINDOW_HEIGHT * 0.25f);
			object.SetScaledWidth(WINDOW_WIDTH * 0.85f);
			object.SetScaledHeight(WINDOW_HEIGHT * 0.55f);
			objects[0].Add(object);

			// Continue
			object.SetTextureID(4);
			object.SetPosX(WINDOW_WIDTH * 0.19);
			object.SetPosY(WINDOW_HEIGHT * 0.005f);
			object.SetScaledWidth(WINDOW_WIDTH * 0.65f);
			object.SetScaledHeight(WINDOW_HEIGHT * 0.35f);
			objects[0].Add(object);
		}

		Menu::Update();
	}

	void Load() override
	{
		engine->play2D("TitleScreen//titleScreenTheme3.wav", false, false, false, irrklang::ESM_NO_STREAMING, false);

		LoadTextures();

		Scene::SetRenderLayers(1);
	}

protected:
	virtual void PlayerSelect() override
	{
		Menu::PlayerSelect(); // Selects the current button for P1 and goes to a scene transition
	}

private:
	void LoadTextures()
	{
		// Resize array now so that resizing doesn't lose OpenGL context for textures
		textures.reserve(5);

		Texture t = Texture();

		textures.push_back(t);
		textures[0].LoadTextureFromFile("TitleScreen/titleBackground.gif");

		textures.push_back(t);
		textures[1].LoadTextureFromFile("TitleScreen/title.png");

		textures.push_back(t);
		textures[2].LoadTextureFromFile("TitleScreen/titleBlack.png");

		textures.push_back(t);
		textures[3].LoadTextureFromFile("TitleScreen/flash.png");
		
		textures.push_back(t);
		textures[4].LoadTextureFromFile("TitleScreen/continue.png");
	}
};
#endif
