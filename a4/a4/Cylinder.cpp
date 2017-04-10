#include "Cylinder.h"
#include "Shader.h"
#include "Camera.h"


Cylinder::Cylinder(int s, float r, float h, vec3 pos)
{
	slices = s;
	radius = r;
	height = h;
	position = pos;
	program = generateProgram("cylinder.vert", "cylinder.frag");
	generateBuffer();
}

void Cylinder::generateBuffer()
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	buildCylinder();

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts[0]) * verts.size(), &verts[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Cylinder::render(mat4 &view, mat4 &proj)
{
	glBindVertexArray(vertexArray);
	glUseProgram(program);

	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_FALSE, value_ptr(proj));

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//glDrawArrays(GL_TRIANGLE_STRIP, 0, slices*2+2);
	glDrawArrays(GL_LINE_STRIP, 0, slices * slices);

	glBindVertexArray(0);
}

void Cylinder::buildCylinder()
{
	//float hl = height / 2;
	//float a = 0.0f;
	//float step = 2 * M_PI / slices;

	//for (int i = 0; i < slices; i++) 
	//{
	//	verts.push_back(vec3(radius*cos(a), -hl, radius*sin(a))+position);
	//	verts.push_back(vec3(radius*cos(a), hl, radius*sin(a)) + position);
	//	a += step;
	//}
	//a = 0.0f;
	//verts.push_back(vec3(radius*cos(a), -hl, radius*sin(a)) + position);
	//verts.push_back(vec3(radius*cos(a), hl, radius*sin(a)) + position);

	float a;
	float step = 2 * M_PI / slices;
	float vstep = height / slices;

	for (int j = -height/2; j < height/2; j += vstep)
	{
		a = 0.0f;
		for (int i = 0; i < slices; i++)
		{
			verts.push_back(vec3(radius*cos(a), j, radius*sin(a)) + position);
			a += step;
		}
	}

}