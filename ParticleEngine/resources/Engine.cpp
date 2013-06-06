#include "..\include\Engine.h"


Engine::Engine(void):
	affectors_(),
	particles_(),
	producers_()
{
	/*test
	Particle* testParticle = new Particle( cml::vector3f(0.0, 0.0, 0.0), 1.0, 1000, cml::vector4f(1.0, 0.0, 0.0, 0.50), 0.1 );
	testParticle->addForce(cml::vector3f(0.01, 0.0, 0.0));
	particles_.push_back( testParticle );
	*/
	/*test
	Producer* testProducer = new Producer(0.3, cml::vector3f(0.1, 0.0, 0.0), 0.01);
	producers_.push_back(testProducer);
	*/

}


Engine::~Engine(void)
{
	{
		std::list<Particle*>::iterator i = particles_.begin();
		while(i != particles_.end()){
			delete (*i);
			i++;
		}
	}
	{
		std::list<Producer*>::iterator i = producers_.begin();
		while(i != producers_.end()){
			delete (*i);
			i++;
		}
	}
	{
		std::list<Affector*>::iterator i = affectors_.begin();
		while(i != affectors_.end()){
			delete (*i);
			i++;
		}
	}
}	


void Engine::update()
{
	{
		std::list<Particle*>::iterator i = particles_.begin();
		while(i != particles_.end()){
			if( (*i)->getIsAlive() == GL_TRUE){
				(*i)->update();
				i++;
			}
			else{
				delete (*i);
				i = particles_.erase(i);
			}
		}
	}
	{
		std::list<Producer*>::iterator i = producers_.begin();
		while(i != producers_.end()){
			(*i)->update();
			std::list<Particle*> particles = (*i)->extractParticles();
			particles_.insert(particles_.end(), particles.begin(), particles.end());
			i++;
		}
	}
}


void Engine::draw()
{
	std::list<Particle*>::iterator i = particles_.begin();
	while(i != particles_.end()){

		(*i)->draw();

		i++;
	}
}


void Engine::addAffector(Affector* toAddAffector)
{
	affectors_.push_back(toAddAffector);
}

void Engine::addProducer(Producer* toAddProducer)
{
	producers_.push_back(toAddProducer);
}