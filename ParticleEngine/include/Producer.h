#pragma once


#include "Particle.h"
#include "SelectableObject.h"

#include <list>

class Producer:
	public SelectableObject
{
public:

	struct ProducerSpecification
	{
		GLfloat			spawnTime;
		cml::vector3f	initialForce;
		GLfloat 		spreadStrength;
	};

	Producer(cml::vector3f position, GLfloat spawnTime, cml::vector3f initialForce, GLfloat spreadStrength, Particle::ParticleSpecification particleSpecification);
	Producer(cml::vector3f position, ProducerSpecification producerSpecification, Particle::ParticleSpecification particleSpecification);
	~Producer(void);

	void update();
	void draw();

	std::list<Particle*> extractParticles();

private:

	GLfloat								spawnTime_;

	GLfloat								elapsedTime_;

	cml::vector3f						initialForce_;

	GLfloat 							spreadStrength_;
	
	Particle::ParticleSpecification		particleSpecification_;

	std::list<Particle*>				storedParticles_;
};
