#include "Game.h"
#include "DevIL.h"
#include "Globals.h"
#include <stdio.h>

Game bananaFighter;

// Used by glut to handle when a key is pressed
static void KeyPress(unsigned char Key, int x, int y)
{
	if(player_one_controls.left ==  Key)
	{
		if(keyStates[Key] == false)
		{
			bananaFighter.DigitalPlayerInput(PlayerID::PlayerOne, Input::Back, true);
			keyStates[Key] = true;
		}
	}
	else if(player_one_controls.right ==  Key)
	{
		if(keyStates[Key] == false)
		{
			bananaFighter.DigitalPlayerInput(PlayerID::PlayerOne, Input::Forward, true);
			keyStates[Key] = true;
		}
	}
	else if(player_one_controls.up ==  Key)
	{
		if(keyStates[Key] == false)
		{
			bananaFighter.DigitalPlayerInput(PlayerID::PlayerOne, Input::Up, true);
			keyStates[Key] = true;
		}
	}
	else if(player_one_controls.down ==  Key)
	{
		if(keyStates[Key] == false)
		{
			bananaFighter.DigitalPlayerInput(PlayerID::PlayerOne, Input::Down, true);
			keyStates[Key] = true;
		}
	}
	else if(player_one_controls.punch ==  Key)
	{
		if(keyStates[Key] == false)
		{
			bananaFighter.DigitalPlayerInput(PlayerID::PlayerOne, Input::Punch, true);
			keyStates[Key] = true;
		}
	}
	else if(player_one_controls.kick ==  Key)
	{
		if(keyStates[Key] == false)
		{
			bananaFighter.DigitalPlayerInput(PlayerID::PlayerOne, Input::Kick, true);
			keyStates[Key] = true;
		}
	}
	else if (player_one_controls.esc == Key)
	{
		if (keyStates[Key] == false)
		{
			bananaFighter.GetSceneManager().ModifyMenuStack(SceneID::Pause);
			keyStates[Key] = true;
		}
	}
	else if(Key == ' ')
	{
		render_boxes = !render_boxes;
	}
}

// Used by glut to handle when a key is released
static void KeyRelease(unsigned char Key, int x, int y)
{
	// TODO: add a poll when a key releases to create more fluid controls. maybe call a key press event of whatever keys are still held?
	if(player_one_controls.left ==  Key)
	{
		bananaFighter.DigitalPlayerInput(PlayerID::PlayerOne, Input::Back, false);
		keyStates[Key] = false;

	}
	else if(player_one_controls.right ==  Key)
	{
		bananaFighter.DigitalPlayerInput(PlayerID::PlayerOne, Input::Forward, false);
		keyStates[Key] = false;
	}
	else if(player_one_controls.up ==  Key)
	{
		bananaFighter.DigitalPlayerInput(PlayerID::PlayerOne, Input::Up, false);
		keyStates[Key] = false;
	}
	else if(player_one_controls.down ==  Key)
	{
		bananaFighter.DigitalPlayerInput(PlayerID::PlayerOne, Input::Down, false);
		keyStates[Key] = false;
	}
	else if(player_one_controls.punch ==  Key)
	{
		bananaFighter.DigitalPlayerInput(PlayerID::PlayerOne, Input::Punch, false);
		keyStates[Key] = false;
	}
	else if(player_one_controls.kick ==  Key)
	{
		bananaFighter.DigitalPlayerInput(PlayerID::PlayerOne, Input::Kick, false);
		keyStates[Key] = false;
	}
	else if (player_one_controls.esc == Key)
	{
		keyStates[Key] = false;
	}
}

// Used by glut to handle down/up events of mouse buttons
void MouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON)
	{
		if(button == GLUT_DOWN)
		{

		}
		else if(button == GLUT_UP)
		{

		}
	}
	else if (button == GLUT_LEFT_BUTTON)
	{
		if(button == GLUT_DOWN)
		{
			leftMousePressed = true;
		}
		else if(button == GLUT_UP)
		{
			leftMousePressed = false;
		}
	}
}

// Used by glut to handle movement while left mouse is down
static void MouseDrag(int x, int y)
{

}

// Used by glut to handle mouse position
static void MouseMove(int x, int y)
{

}

// Used by glut to handle mouse movement events when leaving/entering the window
static void MouseEnter(int state)
{

}

/*
Pre Condition:
 -Initialized freeGLUT
Post Condition:
 -Calls the main loop functions and sets itself to be called back in 1000 / SCREEN_FPS milliseconds
Side Effects:
 -Sets glutTimerFunc
*/
void MainLoop( int val )
{
    //Frame logic
	bananaFighter.Update();
	bananaFighter.Render();

    //Run frame one more time
    glutTimerFunc( 1000 / WINDOW_FPS, MainLoop, val );
}

/*
Pre Condition:
 -A valid OpenGL context
Post Condition:
 -Initializes viewport, matrices and clear color
 -Initializes DevIL
 -Reports to console if there was an OpenGL error
 -Reports to console if there was a DevIL error
 -Returns false if there was an error in initialization
Side Effects:
 -Sets viewport to the fill rendering area
 -Projection matrix is set to an orthographic matrix
 -Modelview matrix is set to identity matrix
 -Matrix mode is set to modelview
 -Clear color is set to black
 -Texturing is enabled
 -Sets DevIL clear color to transparent white
*/
bool initLibraries()
{
	//Set the viewport
    glViewport( 0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT );

    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, 1.0, -1.0 );

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color
    glClearColor( CLEAR_COLOR_RED, CLEAR_COLOR_GREEN, CLEAR_COLOR_BLUE, 1.f );

    //Enable texturing
    glEnable( GL_TEXTURE_2D );

	//Enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Check for error
    GLenum glError = glGetError();
    if( glError != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( glError ) );
        return false;
    }

    //Initialize DevIL
    ilInit();
    ilClearColour( 255, 255, 255, 000 );

    //Check for error
    ILenum ilError = ilGetError();
    if( ilError != IL_NO_ERROR )
    {
        printf( "Error initializing DevIL! %s\n", iluErrorString( ilError ) );
        return false;
    }

    return true;
}

void glut_init()
{
    //Set rendering function(redraw called by windows)
    glutDisplayFunc( Game::Render );

	// Set keyboard functions
	glutKeyboardFunc(KeyPress);
	glutKeyboardUpFunc(KeyRelease);

	for(int i = 0; i < 256; i++)
	{
		keyStates[i] = false;
	}

	// Set mouse functions
	glutMouseFunc(MouseClick); // Button press events up/down
	glutMotionFunc(MouseDrag); // Mouse movement with left button down
	glutPassiveMotionFunc(MouseMove); // Mouse movement regardless of buttons
	glutEntryFunc(MouseEnter); // Mouse event when leaving/entering window

    //Set main loop
    glutTimerFunc( 1000 / WINDOW_FPS, MainLoop, 0 );
}

int main( int argc, char* args[] )
{
	srand(time(0));

    //Initialize FreeGLUT
    glutInit( &argc, args );

    //Create OpenGL 2.1 context
    glutInitContextVersion( 2, 1 );

    //Create Double Buffered Window
    glutInitDisplayMode( GLUT_DOUBLE ); // Double buffering
    glutInitWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
    glutCreateWindow( "BananaFighter" );
	
    //Do post window/context creation initialization
    if( !initLibraries() )
    {
        printf( "Unable to initialize graphics library!\n" );
        return 1;
    }
	
	glut_init();

	bananaFighter = Game();
	
	bananaFighter.Start();

	//Start GLUT main loop
    glutMainLoop();

    return 0;
}

