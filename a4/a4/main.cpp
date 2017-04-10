#include "main.h"

int main()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 16);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CPSC587 Assignment 3", NULL, NULL);

	if (!window) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouse);
	glfwSetCursorPosCallback(window, motion);
	glfwSetScrollCallback(window, scroll);
	glfwMakeContextCurrent(window);

	if (!gladLoadGL())
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}
	printOpenGLVersion();

	setupScene();
	box b = box(50.f);
	Cylinder obs = Cylinder(20,10,100, vec3(-30, 0, -30));
	proj = camera.calculateProjectionMatrix();
	view = camera.calculateViewMatrix();



	while (!glfwWindowShouldClose(window))
	{
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 1.0);

		//update vertex positions
		for (int i = 0; i < boids.size(); i++)
		{
			boids[i]->update();
		}

		//update Camera
		proj = camera.calculateProjectionMatrix();
		view = camera.calculateViewMatrix();

		//draw objects
		for (int i = 0; i < boids.size(); i++)
		{
			boids[i]->render(view,proj);
		}

		b.render(view, proj);				//render box
		obs.render(view, proj);

		//simulate
		simulate();

		//time step
		curr_t += delta_t;

		//v-sync
		glfwSwapInterval(1);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// Shutdow the program
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void setupScene()
{
	srand(time(NULL));
	int x, y, z, x1, y1, z1;
	vec3 dir;

	for (int i = 0; i < 100; i++)
	{
		x = rand() % 40 - 19;	// [-19,20]
		y = rand() % 40 - 19;	// [-19,20]
		z = rand() % 40 - 19;	// [-19,20]

		x1 = rand() % 40 - 19;	// [-19,20]
		y1 = rand() % 40 - 19;	// [-19,20]
		z1 = rand() % 40 - 19;	// [-19,20]

		dir = normalize(vec3(x1, y1, z1));

		Boid *b = new Boid(vec3(x, y, z), 0.1, dir);
		boids.push_back(b);
	}
}

void simulate()
{
	for (int i = 0; i < boids.size(); i++)
	{
		boids[i]->position += boids[i]->velocity * boids[i]->direction;
		if (boids[i]->position.x < -BS*2.5)
			boids[i]->position.x = BS*2.5;
		if (boids[i]->position.y < -BS*2.5)
			boids[i]->position.y = BS*2.5;
		if (boids[i]->position.z < -BS*2.5)
			boids[i]->position.z = BS*2.5;

		if (boids[i]->position.x > BS*2.5)
			boids[i]->position.x = -BS*2.5;
		if (boids[i]->position.y > BS*2.5)
			boids[i]->position.y = -BS*2.5;
		if (boids[i]->position.z > BS*2.5)
			boids[i]->position.z = -BS*2.5;
	}
}

void printOpenGLVersion()
{
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	printf("OpenGL on %s %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
	printf("OpenGL version supported %s\n", glGetString(GL_VERSION));
	printf("GLSL version supported %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("GL version major, minor: %i.%i\n", major, minor);
}

void errorCallback(int error, const char* description)
{
	std::cout << "GLFW ERROR " << error << ": " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void mouse(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		mouse_old_x = x;
		mouse_old_y = y;
	}
}

void motion(GLFWwindow* w, double x, double y)
{

	double dx, dy;
	dx = (x - mouse_old_x);
	dy = (y - mouse_old_y);

	if (glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_1))
	{
		rotate_x += dy * 0.005f;
		phi += dx * 0.005f;
	}

	mouse_old_x = x;
	mouse_old_y = y;

	camera.setAlt(rotate_x);
	camera.setAzu(phi);

}

void scroll(GLFWwindow* w, double x, double y)
{
	double dy;
	dy = (x - y);

	camera.incrementRadius(-2*dy);
}