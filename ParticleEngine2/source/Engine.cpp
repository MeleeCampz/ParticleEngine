#include "..\include\Engine.h"


Engine::Engine(void):
	affectors_(),
	particles_(),
	producers_()
{

	/*test*
	Affector* testAffector = new Gravitation(cml::vector3f(-5.0, 0.0, 0.0), cml::vector3f(0.0, -0.01, 0.0));
	addAffector(testAffector);
	/**/

	/*test*
	Affector* testAffector2 = new AttractorLocal(cml::vector3f(-5.0, 3.0, 0.0), 0.01);
	addAffector(testAffector2);
	/**/

	/*test
	Affector* testAffector3 = new AttractorLocal(cml::vector3f(5.0, 0.0, 0.0), -0.01);
	addAffector(testAffector3);
	*/

	/*test*/
	Affector* testAffector3 = new Friction(cml::vector3f(5.0, 5.0, 0.0), 0.01);
	addAffector(testAffector3);
	/**/

	/*test*/
	Particle::ParticleSpecification particleSpecification;
	particleSpecification.mass = 1.0;
	particleSpecification.lifetime = 1000;
	particleSpecification.color = cml::vector4f(1.0, 1.0, 0.0, 0.00);
	particleSpecification.size = 0.05;

	Producer::ProducerSpecification producerSpecification;
	producerSpecification.spawnTime = 0.3;
	producerSpecification.initialForce = cml::vector3f(0.1, 0.0, 0.0);
	producerSpecification.spreadStrength = 0;

	Producer* testProducer = new Producer( cml::vector3f(0.0, 0.0, 0.0), producerSpecification, particleSpecification);
	addProducer(testProducer);
	/**/
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
		//for each particle
		std::list<Particle*>::iterator i = particles_.begin();
		while(i != particles_.end()){
			//if it is alive
			if( (*i)->getIsAlive() == GL_TRUE){
				//let each affector add his force to the particle
				std::list<Affector*>::iterator j = affectors_.begin();
				while(j != affectors_.end()){
					(*j)->affect(*i);
					j ++;
				}
				//and update it
				(*i)->update();
				i++;
			}
			//if its dead
			else{
				//delete it
				delete (*i);
				i = particles_.erase(i);
			}
		}
	}
	{
		//for each producer
		std::list<Producer*>::iterator i = producers_.begin();
		while(i != producers_.end()){
			//update it
			(*i)->update();
			//and add his produced particles to the set
			std::list<Particle*> particles = (*i)->extractParticles();
			particles_.insert(particles_.end(), particles.begin(), particles.end());
			i++;
		}
	}
}


void Engine::draw()
{
	{
		std::list<Particle*>::iterator i = particles_.begin();
		while(i != particles_.end()){
			(*i)->draw();
			i++;
		}
	}
	{
		std::list<Producer*>::iterator i = producers_.begin();
		while(i != producers_.end()){
			(*i)->draw();
			i++;
		}
	}
	{
		std::list<Affector*>::iterator i = affectors_.begin();
		while(i != affectors_.end()){
			(*i)->draw();
			i++;
		}
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

void Engine::deleteSelectableObject(SelectableObject* toDelete)
{
	for(std::list<Affector*>::iterator itr= affectors_.begin(); itr!=affectors_.end();){
		if((*itr)==toDelete){
			delete toDelete;
			itr=affectors_.erase(itr);
		}
		else itr++;
	}
	for(std::list<Producer*>::iterator itr= producers_.begin(); itr!=producers_.end();){
		if((*itr)==toDelete){
			delete toDelete;
			itr=producers_.erase(itr);
		}
		else itr++;
	}
}

std::list <SelectableObject*> Engine::getSelectableObjects()
{
	std::list <SelectableObject*> selectableObjects;
	selectableObjects.insert(selectableObjects.end(), affectors_.begin(), affectors_.end());
	selectableObjects.insert(selectableObjects.end(), producers_.begin(), producers_.end());

	return selectableObjects;
}