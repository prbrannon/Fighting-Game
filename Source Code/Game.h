#ifndef GAME_H
#define GAME_H

#include "OpenGL.h"
#include "SceneManager.h"

//Rendering:
const GLclampf CLEAR_COLOR_RED = 0;
const GLclampf CLEAR_COLOR_GREEN = 0;
const GLclampf CLEAR_COLOR_BLUE = 0;

class Game
{
public:
	Game();

	/*
	Pre Condition:
	 -Game has been created. DevIL, OpenGL, and GLUT have been initialized
	Post Condition:
	 -Begins running the game logic
	Side Effects:
	 -None
	*/
	void Start();

	/*
	Pre Condition:
	 -None
	Post Condition:
	 -Does per frame logic
	Side Effects:
	 -None
	*/
	void Update();

	/*
	Pre Condition:
	 -A valid OpenGL context
	 -Active modelview matrix
	Post Condition:
	 -Renders the scene
	Side Effects:
	 -Clears the color buffer
	 -Swaps the front/back buffer
	*/
	static void Render();

	void DigitalPlayerInput(const PlayerID& player, const Input &input, const bool& key_down);

	SceneManager& GetSceneManager(){return scene_manager;};

private:
	static SceneManager scene_manager;

	bool player_one_inputs[Input::NUMBER_INPUTS];
};
#endif