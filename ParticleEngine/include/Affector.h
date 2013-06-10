#pragma once

#include "Particle.h"
#include "SelectableObject.h"

#include "GL\glut.h"


class Affector:
	public SelectableObject
{
public:
	Affector(cml::vector3f position);
	virtual ~Affector(void);

	virtual void draw() = 0;

	virtual void affect(Particle* particle) = 0;

};
