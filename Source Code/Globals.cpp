#include "Globals.h"

// Set default values for globals:

bool leftMousePressed = false;
bool* keyStates = new bool[256];

InputQueue player_one_queue = InputQueue();
InputQueue player_two_queue = InputQueue();

GLint WINDOW_WIDTH = 640;
GLint WINDOW_HEIGHT = 480;
int WINDOW_FPS = 60;

irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();

Command player_one_char = Command::None;
Command player_two_char = Command::None;

bool render_boxes = false; //TODO: switch to false after debugging is done

Controls player_one_controls = Controls('a', 'd', 'w', 's', 'j', 'k');