#pragma once

#include "Affector.h"
#include "GL\glut.h"


class Friction:
	public Affector
{
public:
	Friction(cml::vector3f position, GLfloat strength);
	~Friction(void);

	//overrides Affector::draw()
	void draw();

	//overrides Affector::affect(..)
	virtual void affect(Particle* particle);

	//overrides SelectableObject::getHudElement(..)
	HudElement* getHudElement(cml::vector2f size);

private:

	GLfloat strength_;

	void increaseStrength();
	void decreaseStrength();
};

