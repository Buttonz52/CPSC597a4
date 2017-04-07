#pragma once
#include <glm\gtc\type_ptr.hpp>
#include <glm\glm.hpp>
#include <glad\glad.h>
#include <vector>

using namespace glm;
using namespace std;

class Boid
{
public:
	Boid(vec3 p, float v, vec3 d);

	vec3 position;
	float velocity;
	vec3 direction;
	vector<vec3> verts;

	GLuint vertexBuffer;
	GLuint vertexArray;
	GLuint program;

	void generateBuffer();
	void render(mat4 &view, mat4 &proj);
	void update();
	void buildTriangle();
};

