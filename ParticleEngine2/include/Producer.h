#pragma once

#include <cml\cml.h>
#include <Glee/GLee.h>
#include <GL/glut.h>	

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

	//Producer
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
	//Particle
	void increaseMass();
	void decreaseMass();
	void increaseSize();
	void decreaseSize();
	void increaseLifeTime();
	void decreaseLifeTime();
	void changeColor();

	GLfloat								alpha_;
		
	GLfloat								beta_;

	GLfloat								spawnTime_;

	GLfloat								elapsedTime_;

	cml::vector3f						initialForce_;

	GLfloat 							spreadStrength_;
	
	Particle::ParticleSpecification		particleSpecification_;

	std::list<Particle*>				storedParticles_;

	oogl::Model*						model_;

};