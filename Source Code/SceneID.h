#ifndef SCENEID_H
#define SCENEID_H

enum class SceneID
{
	None = 0,

	TestMenu,

	TitleScreen,

	MainMenu,
	MainMenuVS,
	MainMenuTraining,
	MainMenuSettings,

	CharacterSelect,

	Fight,

	EndGame,

	TestScene,

	Pause, // Open the menu from a game scene
	Unpause, // Close the menu to unpause
	CancelMenu, // Pop a menu object from the menu stack
	Quit,

	NUMBER_SCENES // Not actually a scene. DO NOT USE AS ONE.
};

#endif