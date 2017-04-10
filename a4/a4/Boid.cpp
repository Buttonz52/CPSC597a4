#include "Boid.h"
#include "Shader.h"

Boid::Boid(vec3 p, float v, vec3 d, float r)
{
	position = p;
	velocity = v;
	direction = d;
	radius = r;
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

void Boid::render(mat4 &view, mat4 &proj)
{
	glBindVertexArray(vertexArray);
	glUseProgram(program);

	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_FALSE, value_ptr(proj));
	
	glPointSize(3.f);

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
	verts.push_back(position);
	verts.push_back(position + vec3(1,0,-1));
	verts.push_back(position + vec3(1,0,1));
}