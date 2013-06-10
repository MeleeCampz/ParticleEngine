#pragma once

#include "Affector.h"

class AttractorLocal:
	public Affector
{
public:
	AttractorLocal(cml::vector3f position, GLfloat strength);
	~AttractorLocal(void);

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
	void increasePosX();
	void decreasePosX();
	void increasePosY();
	void decreasePosY();
	void increasePosZ();
	void decreasePosZ();
};

