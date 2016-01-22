#ifndef GLOBALS_H
#define GLOBALS_H

// Define any global variables here.
// Can also be used for static storage.

#include "OpenGL.h"
#include "Input.h"
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <irrKlang.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

const int QUEUE_SIZE = 5;

enum Command
{
	None,
	
	Fondu,
	NextGen,
	WomboCombo,
	Random
};

struct Controls
{
	Controls(const char& l, const char& r, const char& u, const char& d, const char& p, const char& k)
	{
		left = l;
		right = r;
		up = u;
		down = d;

		punch = p;
		kick = k;

		esc = 27;
	}

	char left;
	char right;
	char up;
	char down;

	char punch;
	char kick;

	char esc;
};

struct InputQueue
{
	InputQueue()
	{
		current_index = 0;

		for(int i = 0; i < QUEUE_SIZE; i++)
			queue[i] = Input::Neutral;
	}

	void AddInput(Input in)
	{
		current_index = (current_index + 1) % QUEUE_SIZE;

		queue[current_index] = in;
	}

	Input queue[QUEUE_SIZE];

	unsigned int current_index;
};

// Player Input:
extern bool leftMousePressed;
extern bool* keyStates;

extern InputQueue player_one_queue;
extern InputQueue player_two_queue;

//Window:
extern GLint WINDOW_WIDTH;
extern GLint WINDOW_HEIGHT;
extern int WINDOW_FPS;

#pragma comment(lib, "irrKlang.lib") 
extern irrklang::ISoundEngine* engine;

extern Command player_one_char;
extern Command player_two_char;

// Options
extern bool render_boxes;

extern Controls player_one_controls;


#endif