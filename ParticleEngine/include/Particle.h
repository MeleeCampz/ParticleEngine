#pragma once

#include "cml\cml.h"
#include "GL\glut.h"

class Particle
{
public:
	Particle(cml::vector3f position, GLfloat mass, GLint lifetime, cml::vector4f color, GLfloat size);
	~Particle(void);

	void draw();
	void update();
	void addForce(cml::vector3f force);
	cml::vector3f getPosition();
	cml::vector3f getVelocity();
private:
	cml::vector3f	position_;
	cml::vector3f	velocity_;
	cml::vector3f	force_;
	GLfloat			mass_;
	
	GLboolean		isAlive_;
	GLint			lifetime_;
	
	cml::vector4f	color_;
	GLfloat			size_;
	
};
