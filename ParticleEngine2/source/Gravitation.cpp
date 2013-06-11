#include "..\include\Gravitation.h"


Gravitation::Gravitation(cml::vector3f position, cml::vector3f force):
	Affector(position),
	force_(force)
{
	model_ = oogl::loadModel("assets/Apple/apple.3ds", oogl::Model::LOAD_NORMALIZE_TWO);
}


Gravitation::~Gravitation(void)
{
}


void Gravitation::draw()
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


void Gravitation::affect(Particle* particle)
{
	particle->addForce(force_);
}


HudElement* Gravitation::getHudElement(cml::vector2f size)
{
	HudElement* hudElement = new HudElement(size);
	return hudElement;
}