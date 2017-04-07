#include "Particle.h"
#include "Shader.h"

Particle::Particle(vec3 pos, float m, bool anchored)
{
	force = vec3(0);
	velocity = vec3(0);
	position = pos;
	mass = m;
	vertexArray = 0;
	vertexBuffer = 0;
	program = generateProgram("general.vert", "general.frag");
	generateBuffer();
	isAnchored = anchored;
}

void Particle::generateBuffer()
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	verts.push_back(position);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts[0]) * verts.size(), &verts[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Particle::render()
{
	glBindVertexArray(vertexArray);
	glUseProgram(program);

	glPointSize(5.f);

	glDrawArrays(GL_POINTS, 0, 1);

	glBindVertexArray(0);
}

void Particle::update()
{
	glBindVertexArray(vertexArray);

	verts.clear();
	verts.push_back(position);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts[0]) * verts.size(), &verts[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}