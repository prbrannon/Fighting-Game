#include "Input.h"

bool IsMovement(Input input)
{
	if((int)input >= 1 && (int)input <= 9)
		return true;
	return false;
}

bool IsAction(Input input)
{
	if((int)input >= 10 && (int)input < (int)Input::NUMBER_INPUTS)
		return true;
	return false;
}