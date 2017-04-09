#include "box.h"
#include "Shader.h"

box::box(float s)
{
	BS = s;
	program = generateProgram("box.vert", "box.frag");
	generateBuffer();
}

void box::generateBuffer()
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	buildBox();

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts[0]) * verts.size(), &verts[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void box::render(mat4 &view, mat4 &proj)
{
	glBindVertexArray(vertexArray);
	glUseProgram(program);

	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_FALSE, value_ptr(proj));

	glDrawArrays(GL_LINES, 0, 24);

	glBindVertexArray(0);
}

void box::buildBox()
{
	verts.push_back(vec3(-BS, -BS, -BS));
	verts.push_back(vec3(-BS, -BS, BS));

	verts.push_back(vec3(-BS, -BS, BS));
	verts.push_back(vec3(BS, -BS, BS));

	verts.push_back(vec3(BS, -BS, BS));
	verts.push_back(vec3(BS, -BS, -BS));

	verts.push_back(vec3(BS, -BS, -BS));
	verts.push_back(vec3(-BS, -BS, -BS));

	verts.push_back(vec3(-BS, -BS, -BS));
	verts.push_back(vec3(-BS, BS, -BS));

	verts.push_back(vec3(-BS, -BS, BS));
	verts.push_back(vec3(-BS, BS, BS));

	verts.push_back(vec3(BS, -BS, BS));
	verts.push_back(vec3(BS, BS, BS));

	verts.push_back(vec3(BS, -BS, -BS));
	verts.push_back(vec3(BS, BS, -BS));

	verts.push_back(vec3(-BS, BS, -BS));
	verts.push_back(vec3(-BS, BS, BS));

	verts.push_back(vec3(-BS, BS, BS));
	verts.push_back(vec3(BS, BS, BS));

	verts.push_back(vec3(BS, BS, BS));
	verts.push_back(vec3(BS, BS, -BS));

	verts.push_back(vec3(BS, BS, -BS));
	verts.push_back(vec3(-BS, BS, -BS));


}