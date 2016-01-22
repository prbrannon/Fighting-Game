#ifndef FIGHT_H
#define FIGHT_H

#include "Scene.h"
#include "Fighter.h"

// TODO: remove placeholders - SHAWN

struct Stage
{
	int left;
	int right;
	int ground;
};

struct HUD
{
	HUD()
	{

	}
};

class Fight : public Scene
{
public:
	Fight(void)
	{
		playerOne = NULL;
		playerTwo = NULL;

		stage = Stage();

		SetStage();
	}

	~Fight(void)
	{
		if(playerOne != NULL)
			delete playerOne;
		if(playerTwo != NULL)
			delete playerTwo;
	}

	Fight(const Fight &copy_me)
	{
		playerOne = copy_me.playerOne;
		playerTwo = copy_me.playerTwo;

		stage = copy_me.stage;
	}

	void operator = (const Fight &copy_me)
	{
		playerOne = copy_me.playerOne;
		playerTwo = copy_me.playerTwo;

		stage = copy_me.stage;
	}

	// Override the update function
	void Update() override
	{
		// Update the base class to update all objects and their states
		Scene::Update();



		playerOne->Update();
		playerTwo->Update();

		// Check for push box collision
		CheckPushBoxCollision();

		// Check for stage collision
		CheckFighterStageCollision(playerOne);
		CheckFighterStageCollision(playerTwo);

		// Check for hurtbox->hitbox collision between fighters
		CheckFighterDamage();
	}

	// Override the render function
	void Render() override
	{
		// Call base class to render objects...
		Scene::Render();

		// Render player one
		RenderFighter(playerOne);

		// Render player two
		RenderFighter(playerTwo);
	}

	// Change the fighter's state based on player inputs
	// Pre: Both fighters must not be null
	void PlayerInput(const PlayerID& player, const Input& input, const bool& key_down) override
	{
		Fighter* fighter;

		if(player == PlayerID::PlayerOne)
			fighter = playerOne;
		else if(player == PlayerID::PlayerTwo)
			fighter = playerTwo;


		fighter->PlayerInput(input, key_down);
	}

	void Load() override
	{
		LoadTextures();

		Scene::SetRenderLayers(1);

		LoadSounds();

		// TODO: set up the hud and stuff + stage data reading
		
		// Give the box objects textures
		pushbox.SetTextureID(0);
		hurtbox.SetTextureID(1);
		hitbox.SetTextureID(2);

		GameObject object;
		// TODO: loading the background from a different size window breaks the background
		// Background
		object.SetTextureID(3);
		object.SetPosX(0);
		object.SetPosY(0);
		object.SetScaledWidth(WINDOW_WIDTH);
		object.SetScaledHeight(WINDOW_HEIGHT);
		objects[0].Add(object);
	}

	// Set the given player to be a given fighter
	// Pre:  Must have called Fight.Load() to load other required textures and objects
	// Post: Loads a fighter to be used by the player. Destroys any past fighter.
	//       Loads the framedata, textures, and sounds used by the fighter.
	void SetFighter(const Command& fighter, const PlayerID& playerID)
	{
		// TODO: load textures and sounds as well
		Fighter* player;

		player = new Fighter();

		Texture t;

		int random;

		switch(fighter)
		{
			case Command::Random:
				random = rand() % 3;
				switch (random)
				{
				case 0:
					SetFighter(Command::Fondu, playerID);
					break;
				case 1:
					SetFighter(Command::NextGen, playerID);
					break;
				case 2:
					SetFighter(Command::WomboCombo, playerID);
					break;
				}
				return;
			case Command::Fondu:
				player->LoadFrameData("Fight//Fighters//fondu_framedata.txt");
				textures.push_back(t);
				textures.back().LoadTextureFromFile("Fight/Fighters/fondu_spritesheet.png");
				player->SetTextureID(textures.size() - 1);
				
				break;
			case Command::NextGen:
				player->LoadFrameData("Fight//Fighters//nextgen_framedata.txt");
				textures.push_back(t);
				textures.back().LoadTextureFromFile("Fight/Fighters/nextgen_spritesheet.png");
				player->SetTextureID(textures.size() - 1);
				
				break;
			case Command::WomboCombo:
				player->LoadFrameData("Fight//Fighters//wombocombo_framedata.txt");
				textures.push_back(t);
				textures.back().LoadTextureFromFile("Fight/Fighters/wombocombo_spritesheet.png");
				player->SetTextureID(textures.size() - 1);

				break;
			default:
				break;
		}

		if(playerID == PlayerID::PlayerOne)
		{
			if(playerOne != NULL)
				delete playerOne;
			playerOne = player;
		}
		else if(playerID == PlayerID::PlayerTwo)
		{
			if(playerTwo != NULL)
				delete playerTwo;
			playerTwo = player;
		}
		else
			return;
	}

	// TODO: make multiple stages. make parameter a stageid
	void SetStage()
	{
		stage.ground = 0;
		stage.left = 0;
		stage.right = 640;
	}

protected:
	Stage stage;

	Fighter* playerOne;
	Fighter* playerTwo;

private:

	GameObject pushbox;
	GameObject hurtbox;
	GameObject hitbox;

	// Determine if the two pushboxes collide
	// Pre: None
	// Post: Moves the two fighters apart if their pushboxes collide. They are not guaranteed to be in the state boundary.
	void CheckPushBoxCollision()
	{
		// Both players must be active to do push box tests
		if(playerOne != NULL && playerTwo != NULL)
		{
			// Do the pushboxes intersect?
			if(BoxesIntersect(playerOne->GetPushbox(), playerTwo->GetPushbox()))
			{
				// Find the amount of overlap:
				float overlap;

                // Fighter 1 on left:
				if (playerOne->GetPushbox().x < playerTwo->GetPushbox().x)
                {
					overlap = (playerOne->GetPushbox().GetRight() - playerTwo->GetPushbox().GetLeft()) / 2;

					playerOne->SetBaseX(playerOne->GetBaseX() - overlap);
					playerTwo->SetBaseX(playerTwo->GetBaseX() + overlap);
                }
                // Fighter 1 on right:
                else
                {
					overlap = (playerTwo->GetPushbox().GetRight() - playerOne->GetPushbox().GetLeft()) / 2;

                    playerOne->SetBaseX(playerOne->GetBaseX() + overlap);
					playerTwo->SetBaseX(playerTwo->GetBaseX() - overlap);
                }
			}
		}
	}

	// Correct the fighters' position if they are outside of a the stage
	// Pre: None
	// Post: Moves each fighter into the stage boundary
	void CheckFighterStageCollision(Fighter* fighter)
	{
		if(fighter != NULL)
		{
			// Too far left
			if(fighter->GetBaseX() < stage.left)
			{
				fighter->SetBaseX(stage.left);
			}

			// Too far right
			else if(fighter->GetBaseX() > stage.right)
			{
				fighter->SetBaseX(stage.right);
			}
		}
	}

	// Check for interactions between fighter attacks and apply damage appropriately
	// Pre: None
	// Post: Applies damage if an attack hits a fighter
	void CheckFighterDamage()
	{
		int p_one_hitbox = FighterHits(playerOne, playerTwo);
		int p_two_hitbox = FighterHits(playerTwo, playerOne);

		// Check if player one hits player two
		if(p_one_hitbox != -1)
		{
			// TODO: check for blocking. keep crossups/highlow attacks in mind. - Shawn

			// Attack connects. Check for a trade.
			if(p_two_hitbox != -1)
			{
				// Both players hit with their attacks
				playerOne->Hurt(playerTwo->GetHitbox(p_two_hitbox)); // Hurt player one
				playerTwo->Hurt(playerOne->GetHitbox(p_one_hitbox)); // Hurt player two
			}
			else
			{
				// Apply damage normally
				playerTwo->Hurt(playerOne->GetHitbox(p_one_hitbox)); // Hurt player two

				// TODO: begin combo state for p1 - Shawn
			}
		}
		// Check if player two hits player one
		else if(p_two_hitbox != -1)
		{
			// TODO: check for blocking here too. - Shawn

			playerOne->Hurt(playerTwo->GetHitbox(p_two_hitbox)); // Hurt player one

			// TODO: begin combo state for p2 - Shawn
		}
	}

	// Check to see if a fighter(first) hits another fighter(second) with an attack
	// Pre: None
	// Post: Returns the index of a hitbox that connects, and -1 otherwise
	int FighterHits(Fighter* first, Fighter* second)
	{
		if(first != NULL && second != NULL)
		{
			// Check Player One hitting Player Two
			for(int i = 0; i < first->NumHitboxes(); i++)
			{
				for(int j = 0; j < second->NumHurtboxes(); j++)
				{
					// Check for collision
					if(BoxesIntersect(first->GetHitbox(i), second->GetHurtbox(j)))
					{
						return i;
					}
				}
			}
		}

		return -1;
	}

	void RenderFighter(Fighter* fighter)
	{
		fighter->Render(textures[fighter->GetTextureID()].GetTextureID());

		// Render the boxes over the sprite if needed
		if(render_boxes)
		{
			// Pushbox
			RenderBox(fighter->GetPushbox(), pushbox);

			for(int i = 0; i < fighter->NumHurtboxes(); i++)
			{
				RenderBox(fighter->GetHurtbox(i), hurtbox);
			}

			for(int i = 0; i < fighter->NumHitboxes(); i++)
			{
				RenderBox(fighter->GetHitbox(i), hitbox);
			}
		}
	}

	void RenderBox(Box& box, GameObject& object)
	{
		object.SetPosX(box.x);
		object.SetPosY(box.y);
		object.SetScaledWidth(box.width);
		object.SetScaledHeight(box.height);

		object.Render(textures[object.GetTextureID()].GetTextureID());
	}

	void LoadTextures()
	{
		// Resize array now so that resizing doesn't lose OpenGL context for textures
		// 3 more for each fighter texture
		textures.reserve(6);

		Texture t = Texture();

		textures.push_back(t);
		textures.back().LoadTextureFromFile("Fight/fight_pushbox.png");

		textures.push_back(t);
		textures.back().LoadTextureFromFile("Fight/fight_hurtbox.png");

		textures.push_back(t);
		textures.back().LoadTextureFromFile("Fight/fight_hitbox.png");

		textures.push_back(t);
		textures.back().LoadTextureFromFile("Fight/background.jpg");
	}

	void LoadSounds()
	{
		engine->play2D("Fight/fightTheme.wav", true, false, false, irrklang::ESM_NO_STREAMING, false);
	}
};

#endif