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

	void addAffector(Affector toAddAffector);
	void addProducer(Producer toAddProducer);
	void draw();
	void update();
private:
	std::list <Affector> affectors_;
	std::list <Particle> particles_;
	std::list <Producer> producers_;
};
