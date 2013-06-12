#pragma once

#include "Affector.h"
#include <cml\cml.h>
#include <Glee/GLee.h>
#include <GL/gl.h>	
#include "oogl\Model.h"

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

	void increasePosX();
	void decreasePosX();
	void increasePosY();
	void decreasePosY();
	void increasePosZ();
	void decreasePosZ();
	void increaseStrength();
	void decreaseStrength();

	oogl::Model*	model_;
};

