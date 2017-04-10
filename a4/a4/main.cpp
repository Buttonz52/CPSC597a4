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
	box b = box(100.f);
	Cylinder obs = Cylinder(30,20,200, vec3(-50, 0, -50));
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

	for (int i = 0; i < 1000; i++)
	{
		x = rand() % 200 - 99;	// [-19,20]
		y = rand() % 200 - 99;	// [-19,20]
		z = rand() % 200 - 99;	// [-19,20]

		x1 = rand() % 200 - 99;	// [-19,20]
		y1 = rand() % 200 - 99;	// [-19,20]
		z1 = rand() % 200 - 99;	// [-19,20]

		dir = normalize(vec3(x1, y1, z1));

		Boid *b = new Boid(vec3(x, y, z), 1, dir,8);
		boids.push_back(b);
	}
}

void simulate()
{
	//loop through to other side of box
	for (int i = 0; i < boids.size(); i++)			
	{
		boids[i]->position += boids[i]->velocity * boids[i]->direction;		//move foward

		checkLoop(boids[i]);
		alignment(boids[i]);
		cohesion(boids[i]);
		separation(boids[i]);
	}
}

void checkLoop(Boid *b)
{
	if (b->position.x < -BS*5)
		b->position.x = BS*5;
	if (b->position.y < -BS*5)
		b->position.y = BS*5;
	if (b->position.z < -BS*5)
		b->position.z = BS*5;

	if (b->position.x > BS*5)
		b->position.x = -BS*5;
	if (b->position.y > BS*5)
		b->position.y = -BS*5;
	if (b->position.z > BS*5)
		b->position.z = -BS*5;
}

void alignment(Boid *b)
{
	for (int j = 0; j < boids.size(); j++)
	{
		Boid *b2 = boids[j];

		float l = length(b2->position - b->position);

		if (l == 0)
			continue;
		else if (l < b->radius)
		{
			float f = l / b->radius;				//only let a little bit of direction contribute if you are far away
			b->direction += (f*f*b2->direction);
		}
		else
			continue;

	}
	b->direction = normalize(b->direction);
}

void cohesion(Boid *b)
{
	vec3 avg = vec3(0,0,0);
	for (int j = 0; j < boids.size(); j++)
	{
		avg += boids[j]->position;
	}
	avg /= boids.size();

	vec3 adjustDir = avg - b->position;
	b->direction = normalize(adjustDir*0.001f + b->direction);
}

void separation(Boid *b)
{
	for (int j = 0; j < boids.size(); j++)
	{
		Boid *b2 = boids[j];

		float l = length(b2->position - b->position);

		if (l == 0)
			continue;
		else if (l < 3)
		{				
			b->direction += (-b2->direction);
		}
		else
			continue;

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

	camera.incrementRadius(-10*dy);
}