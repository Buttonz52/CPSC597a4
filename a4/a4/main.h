#include "Boid.h"
#include "Shader.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <iostream>
#include <vector>

#define PI 3.14159265359f
#define defaultZoom 8.f

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 500

using namespace glm;
using namespace std;

//callback
double mouse_old_x, mouse_old_y;
float s = 1.0;				//scroll amount
float phi = 0.0;			//radians
float rotate_x = 0.0, rotate_y = 0.0;

//Simulation
float delta_t = 0.000005;
float curr_t = 0.0;
vector<Boid*> boids;

//functions
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse(GLFWwindow* window, int button, int action, int mods);
void motion(GLFWwindow* w, double x, double y);
void scroll(GLFWwindow* w, double x, double y);
void errorCallback(int error, const char* description);
void printOpenGLVersion();

void setupScene();
void simulate();