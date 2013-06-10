#pragma once

#include "GL\glut.h"

#include "Particle.h"
#include "SelectableObject.h"

#include "oogl\Model.h"

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

	GLfloat								spawnTime_;

	GLfloat								elapsedTime_;

	cml::vector3f						initialForce_;

	GLfloat 							spreadStrength_;
	
	Particle::ParticleSpecification		particleSpecification_;

	std::list<Particle*>				storedParticles_;

	oogl::Model*						model_;

};