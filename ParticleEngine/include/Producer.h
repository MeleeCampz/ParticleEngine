
#include "Particle.h"

#include <list>

class Producer
{
public:
	Producer(GLfloat spawnTime, cml::vector3f initialForce, GLfloat spreadStrength);
	~Producer(void);

	virtual void update();

	std::list<Particle*> extractParticles();

private:

	std::list<Particle*> storedParticles_;

	GLfloat spawnTime_;

	GLfloat elapsedTime_;

	cml::vector3f initialForce_;

	GLfloat spreadStrength_;
};
