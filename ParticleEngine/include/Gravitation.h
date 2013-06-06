#pragma once

#include "Affector.h"

class Gravitation:
	public Affector
{
public:

	Gravitation(cml::vector3f position, cml::vector3f force);
	~Gravitation(void);

	virtual void affect(Particle* particle);

private:

	cml::vector3f force_;
};

