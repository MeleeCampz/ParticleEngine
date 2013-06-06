#pragma once


#include "Particle.h"


class Affector
{
public:
	Affector(cml::vector3f position);
	virtual ~Affector(void);

	virtual void affect(Particle* particle) = 0;

private:
	cml::vector3f position_;
};
