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
}


Engine::~Engine(void)
{
	std::list<Particle*>::iterator i = particles_.begin();
	while(i != particles_.end()){
		delete (*i);
		i++;
	}
}


void Engine::update()
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