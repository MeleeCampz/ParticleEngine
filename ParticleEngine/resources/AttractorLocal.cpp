#include "..\include\AttractorLocal.h"


AttractorLocal::AttractorLocal(cml::vector3f position, GLfloat strength):
	Affector(position),
	strength_(strength)
{
}


AttractorLocal::~AttractorLocal(void)
{
}


void AttractorLocal::draw()
{
	glPushMatrix();
		glTranslatef(position_[0], position_[1], position_[2]);
		glColor4f(0.0, 0.0, 1.0, 0.0);
		glutSolidSphere(size_, 10, 10);

	glPopMatrix();
}


void AttractorLocal::affect(Particle* particle)
{
	cml::vector3f difference = position_ - particle->getPosition();
	GLfloat distance = difference.length();

	cml::vector3f force = cml::normalize(difference);
	// maximum force length is strength
	if( distance > strength_ ){
		force *= strength_ / distance;
	}
	else{
		force *= strength_;
	}

	particle->addForce(force);
}