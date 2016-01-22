#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "OpenGL.h"
#include "Texture.h"

struct AnimationNode
{
	unsigned int row, col;

	AnimationNode* next;
};

class GameObject
{
public:

	GameObject();

	virtual void Update(){};
	virtual void ProgressFrames();

	// Set the number of animation types.
	// Pre: None.
	// Post: Clears the array.
	void SetNumAnimRows(const unsigned int& rows);

	// Set the length of a row for animation
	// Pre: the row must exist in the array. Call SetNumAnimRows to set the number of rows.
	// Post: change the row length. If the row doesn't exist, does nothing.
	void SetAnimRowLength(const unsigned int& row_index, const unsigned int& length);
	
	// Set the current animation row and reset the animation row to 0.
	// Pre: The row index should be valid.
	// Post: Sets the animation row and recents the animation row to 0. If the index is invalid, does nothing.
	void SetCurrentAnimRow(const unsigned int& row_index);

	// Set the current animation frame.
	// Pre: The animation row must be valid. The frame index should be valid within the row.
	// Post: Sets the animation frame. If the index is invalid, does nothing.
	void SetCurrentAnimFrame(const unsigned int& frame_index);

	float GetPosX()	const { return worldPosX; };
	float GetPosY()	const { return worldPosY; };
	void SetPosX(float X) { worldPosX = X; };
	void SetPosY(float Y) { worldPosY = Y; };

	int GetTextureWidth() const		  { return texWidth; };
	int GetTextureHeight() const	  { return texHeight; };
	void SetTextureWidth(int width)   { texWidth = width; };
	void SetTextureHeight(int height) { texHeight = height; };

	int GetScaledWidth() const		 { return scaledWidth; };
	int GetScaledHeight() const		 { return scaledHeight; };
	virtual void SetScaledWidth(int width)   { scaledWidth = width; };
	virtual void SetScaledHeight(int height) { scaledHeight = height; };

	unsigned int GetTextureID() const  { return texID; };
	void SetTextureID(unsigned int id) { texID = id; };

	virtual void Render(GLuint text_id);

protected:

	float worldPosX;
	float worldPosY;

	int scaledWidth;
	int scaledHeight;

	unsigned int current_anim_row;
	unsigned int current_frame_num;

	int texWidth;
	int texHeight;

	unsigned int texID;

	// Animation
	std::vector<unsigned int> row_lengths;

	// Spritesheet frame size
	unsigned int longest_row;

	float percent_width;
	float percent_height;

private:

};

#endif