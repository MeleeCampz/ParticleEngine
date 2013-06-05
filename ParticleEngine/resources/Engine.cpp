#include "..\include\Engine.h"


Engine::Engine(void)
{
}


Engine::~Engine(void)
{
}

void Engine::addAffector(Affector toAddAffector)
{
	affectors_.push_back(toAddAffector);
}

void Engine::addProducer(Producer toAddProducer)
{
	producers_.push_back(toAddProducer);
}

void Engine::draw()
{
}

void Engine::update()
{
}