#pragma once

#include "Affector.h"
#include "Particle.h"
#include "Producer.h"

#include <list>

class Engine
{
public:
	Engine(void);
	~Engine(void);

	void update();
	void draw();

	void addAffector(Affector* toAddAffector);
	void addProducer(Producer* toAddProducer);

private:
	std::list <Affector*> affectors_;
	std::list <Particle*> particles_;
	std::list <Producer*> producers_;
};
