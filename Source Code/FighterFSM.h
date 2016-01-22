#ifndef FIGHTERFSM_H
#define FIGHTERFSM_H

#include <vector>
#include "Input.h"
#include "Globals.h"

enum class FighterState
{
	None = 0,

	// Movement States
	CrouchBack,
	Crouch,
	WalkBack,
	Standing,
	WalkForward,
	JumpingBack,
	JumpingUp,
	JumpingForward,

	// Attack States
	JumpAttack,
	StandAttack,
	CrouchAttack,

	// Block Stuns
	BlockStun,
	CrouchBlockStun,

	// Combo States
	HitStun,
	AirJuggle,
	Bound,
	Knockdown,

	NUMBER_OF_STATES // Not an actual state
};

struct StateNode;
struct Transition;

struct StateNode
{
	StateNode()
	{
		state = FighterState::None;
	}

	FighterState state;

	std::vector<Transition> transitions; // Store the directed edges for this node

	// TODO?
	unsigned int frame_data_combo_row;
};

struct Transition
{
	Transition()
	{
		destination = NULL;
	}

	StateNode* destination; // The next node in the graph

	// Required parameters to make transition valid:
	Input required_input;

	bool key_down;
};

class FighterFSM
{
public:
	FighterFSM();

	void CreateUniversal();

	void AddNode(FighterState state);
	void AddTransition(StateNode& source, const Input& required_input, const bool& key_down, StateNode& destination);

	void AddComboNode(FighterState state);
	void AddComboTransition(StateNode& source, const Input& required_input, const bool& key_down, StateNode& destination);

	void AddCombo(const std::vector<Input>& inputs, FighterState type, int row);

	// Determine the next state due to an input
	bool MakeTransition(const Input& input, const bool& key_down);

	// Use to override the current state(such as when jumping and getting hit etc.)
	void SetCurrentState(const FighterState& state);

	FighterState GetCurrentState(){return current_state->state;}

	StateNode& GetCurrentStateNode(){return *current_state;}

	// Call when the latest input is a punch or kick
	bool AttemptCombo(InputQueue& queue);

private:

	std::vector<StateNode> stance_states; // Store every node that isn't an attack
	std::vector<StateNode> combo_nodes; // Store every node that isn't an attack

	StateNode* current_state;

	StateNode* combo_root;
	StateNode* combo_traverse;
};

#endif
