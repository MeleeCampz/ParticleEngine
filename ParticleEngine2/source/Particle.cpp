#include "..\include\Particle.h"


Particle::Particle(cml::vector3f position, GLfloat mass, GLint lifetime, cml::vector4f color, GLfloat size):
	position_(position),
	velocity_(0.0, 0.0, 0.0),
	force_(0.0, 0.0, 0.0),
	mass_(mass),
	isAlive_(true),
	lifetime_(lifetime),
	color_(color),
	size_(size)
{
}


Particle::Particle(cml::vector3f position, ParticleSpecification particleSpecification):
	position_(position),
	velocity_(0.0, 0.0, 0.0),
	force_(0.0, 0.0, 0.0),
	mass_(particleSpecification.mass),
	isAlive_(true),
	lifetime_(particleSpecification.lifetime),
	color_(particleSpecification.color),
	size_(particleSpecification.size)
{
}


Particle::~Particle(void)
{
}


void Particle::draw()
{
	glPushMatrix();
		glTranslatef(position_[0], position_[1], position_[2]);
		glColor4f(color_[0], color_[1], color_[2],0);
		glutSolidSphere(size_, 10, 10);

	glPopMatrix();
}


void Particle::update()
{
	velocity_ += force_ / mass_;
	force_.zero();
	position_ += velocity_;

	lifetime_ --;
	if(lifetime_ <= 0){
		isAlive_ = false;
	}
}


void Particle::addForce(cml::vector3f force)
{
	force_ += force;
}


cml::vector3f Particle::getPosition()
{
	return position_;
}


cml::vector3f Particle::getVelocity()
{
	return velocity_;
}


GLboolean Particle::getIsAlive()
{
	return isAlive_;
}