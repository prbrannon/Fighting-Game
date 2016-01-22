#ifndef FIGHTER_H
#define FIGHTER_H

#include "GameObject.h"
#include "ArrayList.h"
#include "FrameData.h"
#include "Input.h"
#include "FighterFSM.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "Globals.h"

const float WALK_SPEED = 3.0;
const float JUMP_SPEED_X = 6.0;

// Physics in pixels
const float JUMP_LAUNCH_VELOCITY = 20.0;
const float GRAVITY = -1.0;

class Fighter : public GameObject
{
public:
	Fighter();

	virtual void Update() override; // TODO: write this

	void LoadFrameData(std::string filepath);

	virtual void SetScaledWidth(int width) override { GameObject::SetScaledWidth(width); box_pivot_x_offset = width / 2; };

	//virtual void ProgressFrames() override; // TODO: Fill out how the frames change

	void SetFacingRight(bool faceRight){ facing_right = faceRight; }

	void SetCurrentState(FighterState next_state);
	
	void PerformAttack(FighterState state, unsigned int row);

	/*
	void SetBaseX(float x){pos_x = x;}
	void SetBaseY(float y){pos_y = y;}

	float GetBaseX(){return pos_x;}
	float GetBaseY(){return pos_y;}
	*/
	
	unsigned int NumHurtboxes(){return CurrentFrameData().NumHurtboxes();};
	unsigned int NumHitboxes(){return CurrentFrameData().NumHitboxes();};

	Box GetPushbox();
	Box GetHurtbox(int index);
	HitBox GetHitbox(int index);

	float GetBaseX(){return worldPosX + scaledWidth / 2;};
	float GetBaseY(){return worldPosY;};
	void SetBaseX(float new_base_x){worldPosX = new_base_x - scaledWidth / 2;};
	void SetBaseY(float new_base_y){worldPosX = new_base_y;};

	void SetMaxHealth(int val) { maxHealth = val; };
	int GetMaxHealth() { return maxHealth; };
	void SetCurrentHealth(int val) { currentHealth = val; };
	int GetCurrentHealth() { return currentHealth; };

	// Set the boxes to be based off of the center of the sprite
	void FixBoxAllignment();

	void Hurt(const HitBox& hitbox);

	void PlayerInput(const Input& input, const bool& key_down);

	virtual void Render(GLuint text_ID) override;

private:
	int maxHealth, currentHealth;

	FighterFSM state_machine;

	bool facing_right;

	std::vector<std::vector<FrameData>> frames;

	// Jumping
	bool jumping;
	float current_air_vel_y;
	float current_air_vel_x;

	float box_pivot_x_offset;

	FrameData CurrentFrameData();

	unsigned int time_in_frame;
};

#endif