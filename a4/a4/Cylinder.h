#pragma once
#include <glm\gtc\type_ptr.hpp>
#include <glm\glm.hpp>
#include <glad\glad.h>
#include <vector>

using namespace glm;
using namespace std;

class Cylinder
{
public:
	Cylinder(int s, float r, float h, vec3 pos);

	int slices;
	float radius;
	float height;
	vec3 position;
	vector<vec3> verts;

	GLuint vertexBuffer;
	GLuint vertexArray;
	GLuint program;

	void generateBuffer();
	void render(mat4 &view, mat4 &proj);
	void buildCylinder();
};

