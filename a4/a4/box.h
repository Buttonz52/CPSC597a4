#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

using namespace glm;
using namespace std;

class box
{
public:
	box(float s);
	float BS;			//Box Size
	vector<vec3> verts;

	GLuint vertexBuffer;
	GLuint vertexArray;
	GLuint program;

	void generateBuffer();
	void buildBox();
	void render(mat4 &view, mat4 &proj);
};

