#include "Boid.h"
#include "Shader.h"

Boid::Boid(vec3 p, float v, vec3 d)
{
	position = p;
	velocity = v;
	direction = d;
	program = generateProgram("general.vert", "general.frag");
	generateBuffer();
}

void Boid::generateBuffer()
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	buildTriangle();

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts[0]) * verts.size(), &verts[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Boid::render()
{
	glBindVertexArray(vertexArray);
	glUseProgram(program);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
}

void Boid::update()
{
	glBindVertexArray(vertexArray);

	verts.clear();
	buildTriangle();

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts[0]) * verts.size(), &verts[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Boid::buildTriangle()
{
	verts.push_back(vec3(0,0,0));
	verts.push_back(vec3(0, 0.5, 0));
	verts.push_back(vec3(0.5, 0.5, 0));
}