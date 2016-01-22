#include "FighterFSM.h"

FighterFSM::FighterFSM()
{
	combo_root = new StateNode();
	combo_root->frame_data_combo_row = -1;
	combo_root->state = FighterState::None;
}

void FighterFSM::CreateUniversal()
{
	stance_states.reserve(15);
	// Create the root node
	// 0
	AddNode(FighterState::Standing);
	stance_states[0].frame_data_combo_row = 0;

	// Movement
	// 1
	AddNode(FighterState::WalkForward);
	AddTransition(stance_states[0], Input::Forward, true, stance_states[1]);
	AddTransition(stance_states[1], Input::Forward, false, stance_states[0]);
	stance_states[1].frame_data_combo_row = 1;
	
	// 2
	AddNode(FighterState::WalkBack);
	AddTransition(stance_states[0], Input::Back, true, stance_states[2]);
	AddTransition(stance_states[2], Input::Back, false, stance_states[0]);
	stance_states[2].frame_data_combo_row = 2;

	// 3
	AddNode(FighterState::Crouch);
	AddTransition(stance_states[0], Input::Down, true, stance_states[3]);
	AddTransition(stance_states[3], Input::Down, false, stance_states[0]);
	AddTransition(stance_states[1], Input::Down, true, stance_states[3]);
	AddTransition(stance_states[2], Input::Down, true, stance_states[3]);
	stance_states[3].frame_data_combo_row = 3;

	// 4
	AddNode(FighterState::BlockStun);
	AddTransition(stance_states[4], Input::NoChange, false, stance_states[0]);
	stance_states[4].frame_data_combo_row = 4;

	// 5
	AddNode(FighterState::CrouchBlockStun);
	AddTransition(stance_states[5], Input::NoChange, false, stance_states[3]);
	stance_states[5].frame_data_combo_row = 5;
	
	// 6
	AddNode(FighterState::JumpingUp);
	AddTransition(stance_states[0], Input::Up, true, stance_states[6]);
	stance_states[6].frame_data_combo_row = 6;

	// 7
	AddNode(FighterState::JumpingForward);
	AddTransition(stance_states[1], Input::Up, true, stance_states[7]);
	stance_states[7].frame_data_combo_row = 6;

	// 8
	AddNode(FighterState::JumpingBack);
	AddTransition(stance_states[2], Input::Up, true, stance_states[8]);
	stance_states[8].frame_data_combo_row = 6;

	// 9
	AddNode(FighterState::HitStun);
	AddTransition(stance_states[9], Input::NoChange, true, stance_states[0]);
	stance_states[9].frame_data_combo_row = 7;

	// 10
	AddNode(FighterState::AirJuggle);
	AddTransition(stance_states[10], Input::NoChange, true, stance_states[0]);
	stance_states[10].frame_data_combo_row = 8;
}

void FighterFSM::AddNode(FighterState state)
{
	StateNode node;

	node.state = state;

	// Add the new node to the list
	stance_states.push_back(node);
}

void FighterFSM::AddTransition(StateNode& source, const Input& required_input, const bool& key_down, StateNode& destination)
{
	Transition t;

	t.required_input = required_input;
	t.key_down = key_down;

	// Set the transition to point to destination
	t.destination = &destination;

	// Set the source node to point to the destination
	source.transitions.push_back(t);
}

bool FighterFSM::MakeTransition(const Input& input, const bool& key_down)
{
	// Check each transition
	for(int i = 0; i < current_state->transitions.size(); i++)
	{
		// Check if the required input matches and is the right keystate
		if(current_state->transitions[i].required_input == input && current_state->transitions[i].key_down == key_down)
		{
			// Make the transition
			current_state = current_state->transitions[i].destination;

			return true;
		}
	}

	return false;
}

void FighterFSM::SetCurrentState(const FighterState& state)
{
	// Search for a node with the given state 
	for(int i = 0; i < stance_states.size(); i++)
	{
		if(stance_states[i].state == state)
		{
			// Set the current state to point at the node
			current_state = &stance_states[i];
		}
	}
}

void FighterFSM::AddComboNode(FighterState state)
{
	StateNode node;

	node.state = state;

	// Add the new node to the list
	combo_nodes.push_back(node);
}

void FighterFSM::AddCombo(const std::vector<Input>& inputs, FighterState type, int row)
{
	bool exists;

	for(int i = 0; i < inputs.size(); i++)
	{
		exists = false;
		combo_traverse = combo_root;

		// Search for node with input that already exists.
		for(int j = 0; j < combo_traverse->transitions.size() && exists == false; j++)
		{
			// Check if existing node has an input
			if(combo_traverse->transitions[j].required_input == inputs[i])
			{
				// Move to the next node
				combo_traverse = combo_traverse->transitions[j].destination;
				exists = true;
			}
		}

		// Create a new node on the graph
		if(exists == false)
		{
			// is a kick or punch
			if(IsAction(inputs[i]))
			{
				AddComboNode(type);
				combo_nodes[combo_nodes.size() - 1].frame_data_combo_row = row;
			}
			// Add an empty input node
			else
				AddComboNode(FighterState::None);

			AddTransition(*combo_traverse, inputs[i], true, combo_nodes[combo_nodes.size() - 1]);
		}
	}
}

bool FighterFSM::AttemptCombo(InputQueue& q)
{
	// Loop through starting nodes
	for(int start = 0; start < QUEUE_SIZE; start++)
	{
		// Loop through each string in array
		for(int i = start; i < QUEUE_SIZE; i++)
		{
			// Start at root node
			combo_traverse = combo_root;

			// Search for transition with input
			for(int j = 0; j < combo_traverse->transitions.size(); j++)
			{
				if(combo_traverse->transitions[j].required_input == q.queue[i])
				{
					// Go to next node
					combo_traverse = combo_traverse->transitions[j].destination;

					// Hit a combo node
					if(combo_traverse->state != FighterState::None)
					{
						current_state = combo_traverse; // SET CURRENT STATE TO THE COMBO NODE

						// Clear the array
						for(int k = 0; k < QUEUE_SIZE; k++)
						{
							q.queue[k] = Input::NoChange;
						}

						return true;
					}
				}
			}
		}
	}

	return false;
}