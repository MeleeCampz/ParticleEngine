#include "..\include\Producer.h"


Producer::Producer(GLfloat spawnTime, cml::vector3f initialForce, GLfloat spreadStrength):
	spawnTime_(spawnTime),
	elapsedTime_(0),
	initialForce_(initialForce),
	spreadStrength_(spreadStrength)
{
}


Producer::~Producer(void)
{
	std::list<Particle*>::iterator i = storedParticles_.begin();
	while(i != storedParticles_.end()){
		delete (*i);
		i++;
	}
}


void Producer::update()
{
	elapsedTime_ += 1;
	while(elapsedTime_ >= spawnTime_){
		elapsedTime_ -= spawnTime_;
		Particle* particle = new Particle( cml::vector3f(0.0, 0.0, 0.0), 1.0, 1000, cml::vector4f(1.0, 0.0, 0.0, 0.50), 0.1 );

		cml::vector3f randomForce;
		cml::random_unit(randomForce);
		randomForce *= spreadStrength_;

		particle->addForce(initialForce_ + randomForce);
		storedParticles_.push_back(particle);
	}
}


std::list<Particle*> Producer::extractParticles()
{
	std::list<Particle*> particles = storedParticles_;
	storedParticles_.clear();
	return particles;
}