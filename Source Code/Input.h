#ifndef INPUT_H
#define INPUT_H

// Input types.
// Indexing starts at 0 and ends at NUMBER_INPUTS
// Use NUMBER_INPUTS to iterate through states
enum class Input
{
	NoChange = 0,

	// Directionals:
	DownBack,
	Down,
	DownForward,
	Back,
	Neutral,
	Forward,
	UpBack,
	Up,
	UpForward,

	// Actions:
	Punch,
	Kick,

	NUMBER_INPUTS // Not actually an input. DO NOT USE AS ONE.
};

enum class PlayerID
{
	None,

	PlayerOne,
	PlayerTwo
};

// Determine if a given input is a movement input(left, right, up, down, and diagonals)
bool IsMovement(Input input);

// Determine if a given input is an action input(punch, kick, and block)
bool IsAction(Input input);

// We need a way to gather all inputs from devices over the course of one frame update.
// Ex: Digital keys on keyboard. Pressing up and left should translate to one Up+Left input
// instead of two singular inputs.
// The InputGroup should be reset to the default state after an input is taken out and fed to
// the scene manager.
struct InputGroup
{
	InputGroup()
	{
		RestoreDefaults();
	}

	// Feed a player's input into the InputGroup.
	// When updating a frame, logic will determine which input should be read by the game.
	// Ex: combining digital directions into diagonals (up + left = upleft)
	void PlayerInput(const Input& input)
	{
		inputs[(int)input] = true;

		if(IsMovement(input))
		{
			movement_recorded = true;
		}
		else if(IsAction(input))
		{
			action_recorded = true;
		}
	}

	// Read the movement determined by the input group.
	// Proirity: Down>Up>Back>Forward
	// Invalid combinations like down and up are disregarded
	Input ReadMovement()
	{
		if(inputs[(int)Input::Down])
		{
			if(inputs[(int)Input::Back])
			{
				return Input::DownBack;
			}
			else if(inputs[(int)Input::Forward])
			{
				return Input::DownForward;
			}
			else
			{
				return Input::Down;
			}
		}
		else if(inputs[(int)Input::Up])
		{
			if(inputs[(int)Input::Back])
			{
				return Input::UpBack;
			}
			else if(inputs[(int)Input::Forward])
			{
				return Input::UpForward;
			}
			else
			{
				return Input::Up;
			}
		}
		else if(inputs[(int)Input::Back])
		{
			return Input::Back;
		}
		else if(inputs[(int)Input::Forward])
		{
			return Input::Forward;
		}

		return Input::NoChange;
	}

	// Read the action determined by the input group.
	// Proirity: Down>Up>Back>Forward
	// Invalid combinations like down and up are disregarded
	Input ReadAction()
	{
		// 
		//TODO: finish work on input combination. No diagonal inputs yet. Not implemented - Shawn
		if(inputs[(int)Input::Punch])
		{
		}
	}

	void RestoreDefaults()
	{
		for(int i = 0; i < (int)Input::NUMBER_INPUTS; i++)
		{
			inputs[i] = false;
		}

		movement_recorded = false;
		action_recorded = false;
	}

	bool inputs[Input::NUMBER_INPUTS];

	bool movement_recorded;
	bool action_recorded;
};
#endif