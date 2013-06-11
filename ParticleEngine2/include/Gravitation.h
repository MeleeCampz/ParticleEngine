#pragma once

#include "Affector.h"
#include <cml\cml.h>
#include <Glee/GLee.h>
#include <GL/gl.h>	
#include "oogl\Model.h"

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

	oogl::Model*	model_;
};

