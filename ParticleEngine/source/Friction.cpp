#include "..\include\Friction.h"


Friction::Friction(cml::vector3f position, GLfloat strength):
	Affector(position),
	strength_(strength)
{
}


Friction::~Friction(void)
{
}


void Friction::draw()
{
	glPushMatrix();
		glTranslatef(position_[0], position_[1], position_[2]);
		glColor4f(1.0, 0.0, 0.0, 0.0);
		//glutSolidSphere(size_, 10, 10);

	glPopMatrix();
}


void Friction::affect(Particle* particle)
{
	cml::vector3f force = particle->getVelocity() * (-strength_);

	particle->addForce(force);
}


HudElement* Friction::getHudElement(cml::vector2f size)
{
	HudElement* hudElement = new HudElement(size);
	//Button* buttonIncreaseStrength = new Button(..)
	return hudElement;
}


void Friction::increaseStrength()
{
	strength_ += 0.01;
}


void Friction::decreaseStrength()
{
	strength_ -= 0.01;
}