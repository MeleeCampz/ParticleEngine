#include "..\include\Producer.h"


Producer::Producer(cml::vector3f position, GLfloat spawnTime, cml::vector3f initialForce, GLfloat spreadStrength, Particle::ParticleSpecification particleSpecification):
	SelectableObject(position),
	spawnTime_(spawnTime),
	elapsedTime_(0),
	initialForce_(initialForce),
	particleSpecification_(particleSpecification)
{
	if(initialForce_.length_squared() > 0){
		spreadStrength_ = initialForce_.length() * spreadStrength;
	}
	else{
		spreadStrength_ = spreadStrength;
	}
	//caluculate die direction the Producer is shooting at with to angles;
	beta_=std::asin(initialForce_[1]/initialForce_.length())*(2*M_PI/360);
	alpha_=std::acos(initialForce_[0]/initialForce_.length())*(2*M_PI/360);

	model_ = oogl::loadModel("assets/NabooFighter/NabooFighter.3ds", oogl::Model::LOAD_NORMALIZE_TWO);
}


Producer::Producer(cml::vector3f position, ProducerSpecification producerSpecification, Particle::ParticleSpecification particleSpecification):
	SelectableObject(position),
	spawnTime_(producerSpecification.spawnTime),
	elapsedTime_(0),
	initialForce_(producerSpecification.initialForce),
	particleSpecification_(particleSpecification)
{
	if(initialForce_.length_squared() > 0){
		spreadStrength_ = initialForce_.length() * producerSpecification.spreadStrength;
	}
	else{
		spreadStrength_ = producerSpecification.spreadStrength;
	}
	alpha_=std::asin(initialForce_[0]/initialForce_.length())*(2*M_PI/360);
	beta_=std::acos(initialForce_[2]/initialForce_.length())*(2*M_PI/360);

	model_ = oogl::loadModel("assets/NabooFighter/NabooFighter.3ds", oogl::Model::LOAD_NORMALIZE_TWO);
}


Producer::~Producer(void)
{
	std::list<Particle*>::iterator i = storedParticles_.begin();
	while(i != storedParticles_.end()){
		delete (*i);
		i++;
	}
}


void Producer::update()
{
	elapsedTime_ += 1;
	while(elapsedTime_ >= spawnTime_){
		elapsedTime_ -= spawnTime_;
		Particle* particle = new Particle( position_, particleSpecification_);

		cml::vector3f randomForce;
		cml::random_unit(randomForce);
		randomForce *= spreadStrength_;

		particle->addForce(initialForce_ + randomForce);
		storedParticles_.push_back(particle);
	}
}


void Producer::draw()
{
	glPushMatrix();
		glTranslatef(position_[0], position_[1], position_[2]);
		glRotated(alpha_,0,1,0);	
		glRotated(-beta_,1,0,0);	
		glColor4f(1.0, 1.0, 1.0, 0.0);
		//glutSolidSphere(size_, 10, 10);
		model_->render();
	glPopMatrix();
}


std::list<Particle*> Producer::extractParticles()
{
	std::list<Particle*> particles = storedParticles_;
	storedParticles_.clear();
	return particles;
}


HudElement* Producer::getHudElement(cml::vector2f size)
{
	HudElement* hudElement = new HudElement(size);
	hudElement->setPosition(cml::vector2f(0.0,1.0-size[1]));

	ImageElement* hudBG = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	hudBG->setImage("assets/ProducerBG.png");
	//POS
	ImageElement* imageincreaseX = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imageincreaseX->setImage("assets/buttonMinus.png");
	ImageElement* imagedecreaseX = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imagedecreaseX->setImage("assets/buttonPlus.png");
	
	ImageElement* imageincreaseY = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imageincreaseY->setImage("assets/buttonMinus.png");
	ImageElement* imagedecreaseY = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imagedecreaseY->setImage("assets/buttonPlus.png");
	
	ImageElement* imageincreaseZ = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imageincreaseZ->setImage("assets/buttonMinus.png");
	ImageElement* imagedecreaseZ = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imagedecreaseZ->setImage("assets/buttonPlus.png");
	//DIRECT
	ImageElement* imageincreaseX2 = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imageincreaseX2->setImage("assets/buttonMinus.png");
	ImageElement* imagedecreaseX2 = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imagedecreaseX2->setImage("assets/buttonPlus.png");
	
	ImageElement* imageincreaseY2 = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imageincreaseY2->setImage("assets/buttonMinus.png");
	ImageElement* imagedecreaseY2 = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imagedecreaseY2->setImage("assets/buttonPlus.png");
	//Strengh
	ImageElement* imageincreaseStrength = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imageincreaseStrength->setImage("assets/buttonPlus.png");
	ImageElement* imagedecreaseStrength = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imagedecreaseStrength->setImage("assets/buttonMinus.png");

	//Spread
	ImageElement* imageincreaseS = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imageincreaseS->setImage("assets/buttonMinus.png");
	ImageElement* imagedecreaseS = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imagedecreaseS->setImage("assets/buttonPlus.png");

	Button<Producer>* buttonIncreaseStrength = new Button<Producer>(this, &Producer::increaseSpreadStrength, cml::vector2f(0.285, 0.1), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonIncreaseStrength->addSubElement(imagedecreaseS);
	Button<Producer>* buttonDecreaseStrength = new Button<Producer>(this, &Producer::decreaseSpreadStrength, cml::vector2f(0.285, 0.6), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonDecreaseStrength->addSubElement(imageincreaseS);
	//Pos
	Button<Producer>* buttonincreaseX= new Button<Producer>(this, &Producer::decreasePosX, cml::vector2f(0.05, 0.1), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseX->addSubElement(imageincreaseX);
	Button<Producer>* buttondecreaseX= new Button<Producer>(this, &Producer::increasePosX, cml::vector2f(0.01, 0.1), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttondecreaseX->addSubElement(imagedecreaseX);

	Button<Producer>* buttonincreaseY= new Button<Producer>(this, &Producer::decreasePosY, cml::vector2f(0.05, 0.6), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseY->addSubElement(imageincreaseY);
	Button<Producer>* buttondecreaseY= new Button<Producer>(this, &Producer::increasePosY, cml::vector2f(0.01, 0.6), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttondecreaseY->addSubElement(imagedecreaseY);

	Button<Producer>* buttonincreaseZ= new Button<Producer>(this, &Producer::increasePosZ, cml::vector2f(0.05, 0.35), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseZ->addSubElement(imageincreaseZ);
	Button<Producer>* buttondecreaseZ= new Button<Producer>(this, &Producer::decreasePosZ, cml::vector2f(0.01, 0.35), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttondecreaseZ->addSubElement(imagedecreaseZ);
	//DIRECT
	Button<Producer>* buttonincreaseDirecX= new Button<Producer>(this, &Producer::decreaseDirecX, cml::vector2f(0.1, 0.1), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseDirecX->addSubElement(imageincreaseX2);
	Button<Producer>* buttondecreaseDirecX= new Button<Producer>(this, &Producer::increaseDirecX, cml::vector2f(0.14, 0.1), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttondecreaseDirecX->addSubElement(imagedecreaseX2);

	Button<Producer>* buttonincreaseDirecY= new Button<Producer>(this, &Producer::decreaseDirecY, cml::vector2f(0.1, 0.5), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseDirecY->addSubElement(imageincreaseY2);
	Button<Producer>* buttondecreaseDirecY= new Button<Producer>(this, &Producer::increaseDirecY, cml::vector2f(0.14, 0.5), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttondecreaseDirecY->addSubElement(imagedecreaseY2);
	//Strengh
	Button<Producer>* buttonincreaseStrength= new Button<Producer>(this, &Producer::increaseStrength, cml::vector2f(0.4, 0.1), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseStrength->addSubElement(imageincreaseStrength);
	Button<Producer>* buttondecreaseStrength= new Button<Producer>(this, &Producer::decreaseStrength, cml::vector2f(0.4, 0.6), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttondecreaseStrength->addSubElement(imagedecreaseStrength);

	hudElement->addSubElement(buttonIncreaseStrength);
	hudElement->addSubElement(buttonDecreaseStrength);
	//POS
	hudElement->addSubElement(buttonincreaseX);
	hudElement->addSubElement(buttondecreaseX);
	hudElement->addSubElement(buttonincreaseY);
	hudElement->addSubElement(buttondecreaseY);
	hudElement->addSubElement(buttonincreaseZ);
	hudElement->addSubElement(buttondecreaseZ);
	//DIREC
	hudElement->addSubElement(buttonincreaseDirecX);
	hudElement->addSubElement(buttondecreaseDirecX);
	hudElement->addSubElement(buttonincreaseDirecY);
	hudElement->addSubElement(buttondecreaseDirecY);
	//STRENGTH
	hudElement->addSubElement(buttondecreaseStrength);
	hudElement->addSubElement(buttonincreaseStrength);
	//BG
	hudElement->addSubElement(hudBG);
	 
	 return hudElement;
}

void Producer::increaseSpreadStrength()
{
	spreadStrength_ += 0.005;
}


void Producer::decreaseSpreadStrength()
{
	if(spreadStrength_>0.005){
		spreadStrength_ -= 0.005;
	}
}

void Producer::increasePosX()
{
	position_[0]+=1;
}
void Producer::decreasePosX()
{
	position_[0]-=1;
}
void Producer::increasePosY()
{
	position_[1]+=1;
}
void Producer::decreasePosY()
{
	position_[1]-=1;
}
void Producer::increasePosZ()
{
	position_[2]+=1;
}
void Producer::decreasePosZ()
{
	position_[2]-=1;
}

void Producer::increaseDirecX()
{
	GLfloat lenght= initialForce_.length();
	alpha_+=10;
	initialForce_[1]=(std::sin(beta_*(2*M_PI/360))*lenght);
	initialForce_[2]=std::cos(beta_*(2*M_PI/360))*cos(alpha_*(2*M_PI/360))*lenght;
	initialForce_[0]=std::cos(beta_*(2*M_PI/360))*sin(alpha_*(2*M_PI/360))*lenght;
}

void Producer::increaseDirecY()
{
	GLfloat lenght= initialForce_.length();
	beta_+=10;
	initialForce_[1]=(std::sin(beta_*(2*M_PI/360))*lenght);
	initialForce_[2]=std::cos(beta_*(2*M_PI/360))*cos(alpha_*(2*M_PI/360))*lenght;
	initialForce_[0]=std::cos(beta_*(2*M_PI/360))*sin(alpha_*(2*M_PI/360))*lenght;
}

void Producer::decreaseDirecX()
{
	GLfloat lenght= initialForce_.length();
	alpha_-=10;
	initialForce_[1]=(std::sin(beta_*(2*M_PI/360))*lenght);
	initialForce_[2]=std::cos(beta_*(2*M_PI/360))*cos(alpha_*(2*M_PI/360))*lenght;
	initialForce_[0]=std::cos(beta_*(2*M_PI/360))*sin(alpha_*(2*M_PI/360))*lenght;
}

void Producer::decreaseDirecY()
{
	GLfloat lenght= initialForce_.length();
	beta_-=10;
	initialForce_[1]=(std::sin(beta_*(2*M_PI/360))*lenght);
	initialForce_[2]=std::cos(beta_*(2*M_PI/360))*cos(alpha_*(2*M_PI/360))*lenght;
	initialForce_[0]=std::cos(beta_*(2*M_PI/360))*sin(alpha_*(2*M_PI/360))*lenght;
}

void Producer::increaseStrength()
{
	initialForce_+=cml::normalize(initialForce_)/125;
}
void Producer::decreaseStrength()
{
	initialForce_-=cml::normalize(initialForce_)/125;
}
