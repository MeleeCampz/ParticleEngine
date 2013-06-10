#pragma once

#include "Affector.h"
#include "GL\glut.h"

class Gravitation:
	public Affector
{
public:

	Gravitation(cml::vector3f position, cml::vector3f force);
	~Gravitation(void);

	//overrides Affector::draw()
	void draw();

	//overrides Affector::affect(..)
	virtual void affect(Particle* particle);

	//overrides SelectableObject::getHudElement(..)
	HudElement* getHudElement(cml::vector2f size);

private:

	cml::vector3f force_;
};

