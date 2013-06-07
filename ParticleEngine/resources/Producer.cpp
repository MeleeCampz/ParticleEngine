#include "..\include\Producer.h"


Producer::Producer(cml::vector3f position, GLfloat spawnTime, cml::vector3f initialForce, GLfloat spreadStrength, Particle::ParticleSpecification particleSpecification):
	SelectableObject(position),
	spawnTime_(spawnTime),
	elapsedTime_(0),
	initialForce_(initialForce),
	particleSpecification_(particleSpecification)
{
	if(initialForce_.length_squared() > 0){
		spreadStrength_ = initialForce_.length() * spreadStrength;
	}
	else{
		spreadStrength_ = spreadStrength;
	}
}


Producer::Producer(cml::vector3f position, ProducerSpecification producerSpecification, Particle::ParticleSpecification particleSpecification):
	SelectableObject(position),
	spawnTime_(producerSpecification.spawnTime),
	elapsedTime_(0),
	initialForce_(producerSpecification.initialForce),
	particleSpecification_(particleSpecification)
{
	if(initialForce_.length_squared() > 0){
		spreadStrength_ = initialForce_.length() * producerSpecification.spreadStrength;
	}
	else{
		spreadStrength_ = producerSpecification.spreadStrength;
	}
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
		Particle* particle = new Particle( position_, particleSpecification_);

		cml::vector3f randomForce;
		cml::random_unit(randomForce);
		randomForce *= spreadStrength_;

		particle->addForce(initialForce_ + randomForce);
		storedParticles_.push_back(particle);
	}
}


void Producer::draw()
{
	glPushMatrix();
		glTranslatef(position_[0], position_[1], position_[2]);
		glColor4f(0.0, 1.0, 0.0, 0.0);
		glutSolidSphere(size_, 10, 10);

	glPopMatrix();
}


std::list<Particle*> Producer::extractParticles()
{
	std::list<Particle*> particles = storedParticles_;
	storedParticles_.clear();
	return particles;
}


HudElement* Producer::getHudElement(cml::vector2f size)
{
	 HudElement* hudElement = new HudElement(size);
	 return hudElement;
}