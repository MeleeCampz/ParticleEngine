#pragma once

#include "cml\cml.h"
#include "GL\glut.h"

class Particle
{
public:
	Particle(void);
	~Particle(void);
private:
	cml::vector4f	color_;
	cml::vector3f	force_;
	GLboolean		isAlive_;
	GLint			lifetime_;

};
