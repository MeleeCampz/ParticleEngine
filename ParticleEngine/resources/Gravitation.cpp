#include "..\include\Gravitation.h"


Gravitation::Gravitation(cml::vector3f position, cml::vector3f force):
	Affector(position),
	force_(force)
{
}


Gravitation::~Gravitation(void)
{
}


void Gravitation::affect(Particle* particle)
{
	particle->addForce(force_);
}