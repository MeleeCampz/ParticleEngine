
#include "Particle.h"

#include <list>

class Producer
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

	virtual void update();

	std::list<Particle*> extractParticles();

private:

	cml::vector3f						position_;

	GLfloat								spawnTime_;

	GLfloat								elapsedTime_;

	cml::vector3f						initialForce_;

	GLfloat 							spreadStrength_;
	
	Particle::ParticleSpecification		particleSpecification_;

	std::list<Particle*>				storedParticles_;
};
