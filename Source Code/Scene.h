#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "ArrayList.h"
#include "GameObject.h"
#include "Input.h"
#include "Texture.h"
#include "SceneID.h"

#include "Globals.h"

struct SceneTransition
{
	SceneTransition()
	{
		Reset();
	}

	void Reset()
	{
		game_scene_set = false;
		menu_scene_set = false;
		next_scene = SceneID::None;
	}

	bool game_scene_set, menu_scene_set;

	SceneID next_scene;
};

class Scene
{
public:
	SceneID scene_id;

	Scene(void);
	~Scene(void);
	Scene(const Scene &copy_me);
	void operator = (const Scene &copy_me);

	// Feed a player's input into the scene
	// Post: Processes the input to modify objects in the scene
	virtual void PlayerInput(const PlayerID& player, const Input &input, const bool& key_down){} /* Pure virtual function */

	// Step the scene forward (after input is read)
	// Post: Performs changes from cycle to cycle
	virtual void Update(){} /* Pure virtual function */

	// Render objects in the scene
	// This method is virtual, although it is defined here
	virtual void Render();

	// Load the needed assets into the scene. Called when beginning a scene.
	virtual void Load(){} /* Pure virtual function */

	// Dispose of loaded assets. Called when moving away from a scene.
	virtual void Unload();

	void SetRunning(bool a){ running = a; };
	bool IsRunning(){ return running; };

	void SetRendering(bool a){ rendering = a; };
	bool IsRendering(){ return rendering; };

	void SetNumPlayers(unsigned int players){ num_players = players; };

protected:
	ArrayList<ArrayList<GameObject>> objects; // A list of layers used to determine rendering order

	std::vector<Texture> textures;

	bool running;
	bool rendering;

	unsigned int num_players;

	/*
	Pre Condition:
	 -None
	Post Condition:
	 -Sets the number of layers in the scene. Used to hold objects.
	Side Effects:
	 -Clears any existing layers
	*/
	void SetRenderLayers(int num_layers);

	// Load any needed textures from files.
	virtual void LoadTextures(){}; /* Pure virtual function */

	// Load any needed sounds from files.
	virtual void LoadSounds(){}; /* Pure virtual function */
};
#endif