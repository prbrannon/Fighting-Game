#ifndef FRAMEDATA_H
#define FRAMEDATA_H

#include <vector>
#include "string"

struct Box
{
	// Origin bottom left!!
	float x, y, width, height;

	float GetLeft() const { return x; }
	float GetRight() const { return x + width; }
	float GetTop() const { return y + height; }
	float GetBottom() const { return y; }

	void SetLeft(float left){ x = left; }
	void SetRight(float right){ x = right - width; }
	void SetTop(float top){ y = top - height; }
	void SetBottom(float bottom){ y = bottom; }

	void SetCenterX(float center_x){x = center_x - width / 2;}
	float GetCenterX(){return x + width / 2;}
};

enum AttackLevel
{
	High,
	Mid,
	Low
};

struct HitBox : Box
{
	float damage;
	AttackLevel level;
	unsigned int blockstun;
	unsigned int hitstun;
	float knockback_x;
	float knockback_y;
};

// Determine if two boxes overlap
// Pre: First and second have defined dimensions
// Post: Returns true if the two boxes overlap, and false otherwise.
bool BoxesIntersect(const Box& first, const Box& second);

class FrameData
{
public:
	FrameData();
	~FrameData();

	void Clear();

	void SetPushBox(Box box){ pushbox = box; }

	void AddHurtbox(const Box& box);
	void AddHitbox(const HitBox& box);

	Box& GetPushbox(){return pushbox;}

	unsigned int NumHurtboxes(){return hurtboxes.size();}
	unsigned int NumHitboxes(){return hitboxes.size();}
	
	Box& GetHurtbox(int index){return hurtboxes[index];}
	HitBox& GetHitbox(int index){return hitboxes[index];}

	unsigned int GetFrameDuration(){ return frame_duration; }
	void SetFrameDuration(const unsigned int& duration){ frame_duration = duration; }


private:
	std::vector<Box> hurtboxes;
	std::vector<HitBox> hitboxes;
	Box pushbox;

	unsigned int frame_duration;
};

#endif
