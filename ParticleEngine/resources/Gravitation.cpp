#include "..\include\Gravitation.h"


Gravitation::Gravitation(cml::vector3f position, cml::vector3f force):
	Affector(position),
	force_(force)
{
}


Gravitation::~Gravitation(void)
{
}


void Gravitation::draw()
{
	glPushMatrix();
		glTranslatef(position_[0], position_[1], position_[2]);
		glColor4f(0.5, 0.5, 1.0, 0.0);
		glutSolidSphere(size_, 10, 10);

	glPopMatrix();
}


void Gravitation::affect(Particle* particle)
{
	particle->addForce(force_);
}


HudElement* Gravitation::getHudElement(cml::vector2f size)
{
	HudElement* hudElement = new HudElement(size);
	return hudElement;
}