#include "Particle.h"
#pragma once
class Spring
{
public:
	Spring(Particle *a, Particle *b, float r_len, float k, float damp);

	Particle *a;						//Particle a
	Particle *b;						//Particle b
	float len;							//Spring length
	float rest_len;						//Spring rest length
	float stiffness;					//Spring Stiffness
	float dampening;					//Spring Dampening	
	vector<vec3> verts;

	GLuint vertexArray;
	GLuint vertexBuffer;
	GLuint program;

	void generateBuffer();
	void render();
	void update();

private:

};

