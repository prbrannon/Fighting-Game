#include "Fighter.h"

Fighter::Fighter()
{
	facing_right = true;

	jumping = false;
}

void Fighter::LoadFrameData(std::string filepath)
{
	state_machine.CreateUniversal();

	int numHitBoxes = 0;
	int numHurtBoxes = 0;
	int pushBoxes = 0;

	int num_rows;
	int num_frames;

	int boxes;

	int duration;

	bool is_attack;

	int num_inputs;

	// Dummy read for labels
	std::string label;

	FrameData data;
	
	std::ifstream fighter(filepath);

	// Start reading the file
	if (fighter.is_open())
	{
		// Read the number of rows
		fighter >> label;

		fighter >> num_rows;

		frames.reserve(num_rows);

		SetNumAnimRows(num_rows);

		for (int row = 0; row < num_rows; row++)
		{
			// Read the number of frames in the row
			fighter >> label;

			fighter >> num_frames;

			// Read if row is an attack
			fighter >> label;

			fighter >> is_attack;

			if(is_attack)
			{
				FighterState state = FighterState::None;

				fighter >> label;
				fighter >> label;

				if(label == "Ground")
					state = FighterState::StandAttack;
				else if(label == "Crouch")
					state = FighterState::CrouchAttack;
				else if(label == "Air")
					state = FighterState::JumpAttack;


				fighter >> label;

				fighter >> num_inputs;

				std::vector<Input> sequence;

				fighter >> label;

				// Read sequence
				for(int q = 0; q < num_inputs; q++)
				{
					fighter >> label;

					if(label == "Left")
						sequence.push_back(Input::Back);
					else if(label == "Right")
						sequence.push_back(Input::Forward);
					else if(label == "Up")
						sequence.push_back(Input::Up);
					else if(label == "Down")
						sequence.push_back(Input::Down);
					else if(label == "Punch")
						sequence.push_back(Input::Punch);
					else if(label == "Kick")
						sequence.push_back(Input::Kick);
				}

				state_machine.AddCombo(sequence, state,row);
			}

			frames.push_back(std::vector<FrameData>());

			frames[row].reserve(num_frames);

			SetAnimRowLength(row, num_frames);

			for (int frame = 0; frame < num_frames; frame++)
			{
				data = FrameData();

				// Read in duration
				fighter >> label;

				fighter >> duration;

				data.SetFrameDuration(duration);

				HitBox temp;

				// Read in the pushbox
				fighter >> label;

				fighter >> temp.x;
				fighter >> temp.y;
				fighter >> temp.width;
				fighter >> temp.height;

				data.SetPushBox(temp);

				// Read in the number of boxes
				fighter >> label;

				fighter >> boxes;

				// Read in each hurtbox
				for (int hurtbox = 0; hurtbox < boxes; hurtbox++)
				{
					// Read in the hurtbox
					fighter >> label;

					fighter >> temp.x;
					fighter >> temp.y;
					fighter >> temp.width;
					fighter >> temp.height;

					data.AddHurtbox(temp);
				}

				// Read in the number of boxes
				fighter >> label;

				fighter >> boxes;

				// Read in each hitbox
				for (int hitbox = 0; hitbox < boxes; hitbox++)
				{
					// Read in the hitbox
					fighter >> label;

					fighter >> temp.x;
					fighter >> temp.y;
					fighter >> temp.width;
					fighter >> temp.height;

					// Read in attack level
					fighter >> label;

					if (label == "High")
						temp.level = AttackLevel::High;
					else if (label == "Mid")
						temp.level = AttackLevel::Mid;
					else if (label == "Low")
						temp.level = AttackLevel::Low;

					// Read in damage for hitbox
					fighter >> label;
					fighter >> temp.damage;

					// Read in blockstun
					fighter >> label;
					fighter >> temp.blockstun;

					// Read in hitstun
					fighter >> label;
					fighter >> temp.hitstun;

					// Read in knockback
					fighter >> label;
					fighter >> temp.knockback_x;
					fighter >> temp.knockback_y;

					data.AddHitbox(temp);
				}

				frames[row].push_back(data);
			}
		}
	}
	
	fighter.close();

	// Set the texture dimensions for the fighter
	SetScaledWidth(WINDOW_WIDTH * 0.35f);
	SetScaledHeight(WINDOW_HEIGHT * 0.75f);

	// Make the boxes centered
	FixBoxAllignment();

	SetCurrentState(FighterState::Standing);
}

void Fighter::SetCurrentState(FighterState next_state)
{
	state_machine.SetCurrentState(next_state);

	SetCurrentAnimRow(state_machine.GetCurrentStateNode().frame_data_combo_row);

	time_in_frame = 0;
}

void Fighter::PerformAttack(FighterState attack_state, unsigned int row)
{


	SetCurrentState(attack_state);

	time_in_frame = 0;
}

FrameData Fighter::CurrentFrameData()
{
	return frames[current_anim_row][current_frame_num];
}

Box Fighter::GetPushbox()
{
	Box box;
	box = CurrentFrameData().GetPushbox();


	box.x += worldPosX;
	box.y += worldPosY;

	return box;
}

Box Fighter::GetHurtbox(int index)
{
	Box box;
	box = CurrentFrameData().GetHurtbox(index);


	box.x += worldPosX;
	box.y += worldPosY;



	return box;
}

HitBox Fighter::GetHitbox(int index)
{
	HitBox box;
	box = CurrentFrameData().GetHitbox(index);


	box.x += worldPosX;
	box.y += worldPosY;

	return box;
}

void Fighter::FixBoxAllignment()
{
	for(int i = 0; i < frames.size(); i++)
	{
		for(int j = 0; j < frames[i].size(); j++)
		{
			frames[i][j].GetPushbox().x += (box_pivot_x_offset - frames[i][j].GetPushbox().width / 2);

			for(int k = 0; k < frames[i][j].NumHitboxes(); k++)
			{
				frames[i][j].GetHitbox(k).x += (box_pivot_x_offset - frames[i][j].GetHitbox(k).width / 2);
			}

			for(int k = 0; k < frames[i][j].NumHurtboxes(); k++)
			{
				frames[i][j].GetHurtbox(k).x += (box_pivot_x_offset - frames[i][j].GetHurtbox(k).width / 2);
			}
		}
	}
}

void Fighter::Hurt(const HitBox& hitbox)
{
	// TODO: decide what to feed in as a parameter for this function
	//currentHealth -= hurtbox.damage;
}

void Fighter::PlayerInput(const Input& input, const bool& key_down)
{
	// Change to another state if the input is a valid transition
	if (state_machine.MakeTransition(input, key_down))
	{
		SetCurrentAnimRow(state_machine.GetCurrentStateNode().frame_data_combo_row);
		time_in_frame = 0;
	}

	if(key_down && IsAction(input))
	{
		state_machine.AttemptCombo(player_one_queue);
	}
}

void Fighter::Update()
{
	switch(state_machine.GetCurrentState())
	{
		case FighterState::Standing:
			
			break;
		case FighterState::WalkBack:
			worldPosX -= WALK_SPEED;

			break;
		case FighterState::WalkForward:
			worldPosX += WALK_SPEED;
			
			break;
		case FighterState::JumpingUp:
			// Start jumping
			if(jumping == false)
			{
				current_air_vel_y = JUMP_LAUNCH_VELOCITY;
				current_air_vel_x = 0;
				jumping = true;
			}

			// Move up/down
			worldPosY += current_air_vel_y;

			// Move left/right
			worldPosX += current_air_vel_x;

			// Increase effect of gravity
			current_air_vel_y += GRAVITY;


			// Check if the fighter fell through the ground
			if(worldPosY < 0)
			{
				worldPosY = 0;
				jumping = false;

				// Set the next state based on controls
				if(keyStates[player_one_controls.left])
					SetCurrentState(FighterState::WalkBack);
				else if(keyStates[player_one_controls.right])
					SetCurrentState(FighterState::WalkForward);
				else if(keyStates[player_one_controls.down])
					SetCurrentState(FighterState::Crouch);
				else if(keyStates[player_one_controls.up])
					SetCurrentState(FighterState::JumpingUp);
				else
					SetCurrentState(FighterState::Standing);
			}

			break;
		case FighterState::JumpingBack:
			// Start jumping
			if(jumping == false)
			{
				current_air_vel_y = JUMP_LAUNCH_VELOCITY;
				current_air_vel_x = -JUMP_SPEED_X;
				jumping = true;
			}

			// Move up/down
			worldPosY += current_air_vel_y;

			// Move left/right
			worldPosX += current_air_vel_x;

			// Increase effect of gravity
			current_air_vel_y += GRAVITY;


			// Check if the fighter fell through the ground
			if(worldPosY < 0)
			{
				worldPosY = 0;
				jumping = false;

				// Set the next state based on controls
				if(keyStates[player_one_controls.left])
					SetCurrentState(FighterState::WalkBack);
				else if(keyStates[player_one_controls.right])
					SetCurrentState(FighterState::WalkForward);
				else if(keyStates[player_one_controls.down])
					SetCurrentState(FighterState::Crouch);
				else if(keyStates[player_one_controls.up])
					SetCurrentState(FighterState::JumpingUp);
				else
					SetCurrentState(FighterState::Standing);
			}

			break;
		case FighterState::JumpingForward:
			// Start jumping
			if(jumping == false)
			{
				current_air_vel_y = JUMP_LAUNCH_VELOCITY;
				current_air_vel_x = JUMP_SPEED_X;
				jumping = true;
			}

			// Move up/down
			worldPosY += current_air_vel_y;

			// Move left/right
			worldPosX += current_air_vel_x;

			// Increase effect of gravity
			current_air_vel_y += GRAVITY;


			// Check if the fighter fell through the ground
			if(worldPosY < 0)
			{
				worldPosY = 0;
				jumping = false;

				// Set the next state based on controls
				if(keyStates[player_one_controls.left])
					SetCurrentState(FighterState::WalkBack);
				else if(keyStates[player_one_controls.right])
					SetCurrentState(FighterState::WalkForward);
				else if(keyStates[player_one_controls.down])
					SetCurrentState(FighterState::Crouch);
				else if(keyStates[player_one_controls.up])
					SetCurrentState(FighterState::JumpingUp);
				else
					SetCurrentState(FighterState::Standing);
			}

			break;
		case FighterState::Crouch:
			
			break;
	}


	time_in_frame++;

	if (time_in_frame > CurrentFrameData().GetFrameDuration())
	{
		ProgressFrames();
		time_in_frame = 0;
	}
}

void Fighter::Render(GLuint text_id)
{
	if( text_id != 0 )
    {
        //Remove any previous transformations
        glLoadIdentity();

        //Move to rendering point
		glTranslatef( worldPosX, worldPosY, 0.f );

        //Set texture ID
        glBindTexture( GL_TEXTURE_2D, text_id );

        //Render textured quad
        glBegin( GL_QUADS );

		if(facing_right)
		{
			// TODO: Render with camera translation/rotation - Shawn, Park
			// Flip vertically for png:
				glTexCoord2f( percent_width * current_frame_num, percent_height * current_anim_row );             glVertex2f( 0.f        , scaledHeight );
				glTexCoord2f( percent_width * (current_frame_num + 1), percent_height * current_anim_row );       glVertex2f( scaledWidth, scaledHeight );
				glTexCoord2f( percent_width * (current_frame_num + 1), percent_height * (current_anim_row + 1) ); glVertex2f( scaledWidth, 0.f );
				glTexCoord2f( percent_width * current_frame_num, percent_height * (current_anim_row + 1) );       glVertex2f( 0.f        , 0.f );
			glEnd();
		}
		else
		{
			// TODO: Render with camera translation/rotation - Shawn, Park
			// Flip vertically for png:
				glTexCoord2f( percent_width * current_frame_num, percent_height * current_anim_row );             glVertex2f( scaledWidth, scaledHeight );
				glTexCoord2f( percent_width * (current_frame_num + 1), percent_height * current_anim_row );       glVertex2f( 0.f        , scaledHeight );
				glTexCoord2f( percent_width * (current_frame_num + 1), percent_height * (current_anim_row + 1) ); glVertex2f( 0.f        , 0.f );
				glTexCoord2f( percent_width * current_frame_num, percent_height * (current_anim_row + 1) );       glVertex2f( scaledWidth, 0.f );
			glEnd();
		}
    }
}