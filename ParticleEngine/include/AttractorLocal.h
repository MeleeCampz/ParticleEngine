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
private:

	GLfloat strength_;
};

