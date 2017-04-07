#include "Spring.h"
#include "Shader.h"



Spring::Spring(Particle *_a, Particle *_b, float r_len, float k, float damp)
{
	a = _a;
	b = _b;
	rest_len = r_len;	
	len = length(b->position - a->position);
	stiffness = k;
	dampening = damp;
	vertexArray = 0;
	vertexBuffer = 0;
	program = generateProgram("general.vert", "general.frag");
	generateBuffer();
}

void Spring::generateBuffer()
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	verts.push_back(a->position);
	verts.push_back(b->position);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts[0]) * verts.size(), &verts[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Spring::render()
{
	glBindVertexArray(vertexArray);
	glUseProgram(program);

	glDrawArrays(GL_LINES, 0, 2);

	glBindVertexArray(0);
}

void Spring::update()
{
	glBindVertexArray(vertexArray);

	verts.clear();
	verts.push_back(a->position);
	verts.push_back(b->position);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts[0]) * verts.size(), &verts[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}
