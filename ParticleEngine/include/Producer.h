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

	//overrides SelectableObject::getHudElement(..)
	HudElement* getHudElement(cml::vector2f size);

private:

	void increaseSpreadStrength();
	void decreaseSpreadStrength();
	void increasePosX();
	void decreasePosX();
	void increasePosY();
	void decreasePosY();
	void increasePosZ();
	void decreasePosZ();
	void increaseDirecX();
	void increaseDirecY();
	void decreaseDirecX();
	void decreaseDirecY();
	void increaseStrength();
	void decreaseStrength();

	GLfloat								alpha_;
		
	GLfloat								beta_;

	GLfloat								spawnTime_;

	GLfloat								elapsedTime_;

	cml::vector3f						initialForce_;

	GLfloat 							spreadStrength_;
	
	Particle::ParticleSpecification		particleSpecification_;

	std::list<Particle*>				storedParticles_;
};
