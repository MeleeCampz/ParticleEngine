#include "..\include\Friction.h"


Friction::Friction(cml::vector3f position, GLfloat strength):
	Affector(position),
	strength_(strength)
{
	model_ = oogl::loadModel("assets/endor/endor.3ds", oogl::Model::LOAD_NORMALIZE_TWO);
}


Friction::~Friction(void)
{
}


void Friction::draw()
{
	glPushMatrix();
		glTranslatef(position_[0], position_[1], position_[2]);
		//glRotated(alpha_,0,1,0);	
		//glRotated(-beta_,1,0,0);	
		glScalef(size_*0.5,size_*0.5,size_*0.5);
		glColor4f(1.0, 1.0, 1.0, 0.0);
		//glutSolidSphere(size_, 10, 10);
		model_->render();
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