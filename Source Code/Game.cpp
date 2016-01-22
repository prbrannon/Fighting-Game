#include "Game.h"

// Must define the static scene manager to link the variable
SceneManager Game::scene_manager = SceneManager();
Texture t;

Game::Game()
{
}

void Game::Start()
{
	// Set the starting scene
	scene_manager.ChangeGameScene(SceneID::TitleScreen);
}

void Game::Update()
{
	scene_manager.Update();
}

void Game::Render()
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );

    //Render scenes
	scene_manager.Render();

    //Update screen
    glutSwapBuffers();
}

void Game::DigitalPlayerInput(const PlayerID& player, const Input &input, const bool& key_down)
{
	scene_manager.PlayerInput(player, input, key_down);
}