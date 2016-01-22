#include "FrameData.h"

bool BoxesIntersect(const Box& first, const Box& second)
{
	if (first.GetBottom() > second.GetTop())
		return false;
	else if (first.GetTop() < second.GetBottom())
		return false;
	else if (first.GetLeft() > second.GetRight())
		return false;
	else if (first.GetRight() < second.GetLeft())
		return false;

	return true;
}

FrameData::FrameData()
{
}


FrameData::~FrameData()
{
}

void FrameData::Clear()
{
	hurtboxes.clear();
	hitboxes.clear();
}

void FrameData::AddHurtbox(const Box& box)
{
	hurtboxes.push_back(box);
}

void FrameData::AddHitbox(const HitBox& box)
{
	hitboxes.push_back(box);
}