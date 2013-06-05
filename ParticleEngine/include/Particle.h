#pragma once

#include "cml\cml.h"
#include "GL\glut.h"

class Particle
{
public:
	Particle(void);
	~Particle(void);

	void addForce(cml::vector3f force);
	void draw();
	cml::vector3f getPosition();
	cml::vector3f getVelocity();
	void update();
private:
	cml::vector4f	color_;
	cml::vector3f	force_;
	GLboolean		isAlive_;
	GLint			lifetime_;
	GLfloat			mass_;
	cml::vector3f	position_;
	GLfloat			size_;
	cml::vector3f	velocity_;
};
