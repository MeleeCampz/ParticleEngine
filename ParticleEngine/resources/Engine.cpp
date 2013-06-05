#include "..\include\Engine.h"


Engine::Engine(void)
{
}


Engine::~Engine(void)
{
}


void Engine::update()
{
	std::list<Particle*>::iterator i = particles_.begin();
	while(i != particles_.end()){

		(*i)->draw();

		i++;
	}
}


void Engine::draw()
{
	std::list<Particle*>::iterator i = particles_.begin();
	while(i != particles_.end()){

		(*i)->update();

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