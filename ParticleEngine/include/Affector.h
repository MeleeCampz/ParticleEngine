#pragma once


#include "Particle.h"
#include "SelectableObject.h"


class Affector:
	public SelectableObject
{
public:
	Affector(cml::vector3f position);
	virtual ~Affector(void);

	virtual void affect(Particle* particle) = 0;

private:
	cml::vector3f position_;
};
