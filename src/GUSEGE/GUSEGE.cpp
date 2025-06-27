#include <GUSEGE.h>

// Initialize static members
GLFWwindow *GUSEGE::window = nullptr;
unsigned int GUSEGE::SCR_WIDTH = 1280;
unsigned int GUSEGE::SCR_HEIGHT = 720;
float GUSEGE::fps = 0.0f;
float GUSEGE::renderTime = 0.0f;
float GUSEGE::deltaTime = 0.0f;
std::chrono::high_resolution_clock::time_point GUSEGE::lastFrameTime = std::chrono::high_resolution_clock::now();
int GUSEGE::frameCount = 0;
std::chrono::high_resolution_clock::time_point GUSEGE::lastFPSTime = std::chrono::high_resolution_clock::now();
bool GUSEGE::sceneInit = false;