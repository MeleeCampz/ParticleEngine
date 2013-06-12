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
	//caluculate the direction the Gravitation is aiming at in two angles
	GLfloat dump;
	cml::cartesian_to_spherical(initialForce_, dump, beta_, alpha_, 2, cml::SphericalType::colatitude);

	model_ = oogl::loadModel("assets/stardestroyer/stardestroyer.3ds", oogl::Model::LOAD_NORMALIZE_TWO);
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
	//caluculate the direction the Gravitation is aiming at in two angles
	GLfloat dump;
	cml::cartesian_to_spherical(initialForce_, dump, beta_, alpha_, 2, cml::SphericalType::colatitude);

	model_ = oogl::loadModel("assets/stardestroyer/stardestroyer.3ds", oogl::Model::LOAD_NORMALIZE_TWO);
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
		//right direction
		glRotated(alpha_ / (2*M_PI/360), 0, 1, 0);	
		glRotated(-beta_ / (2*M_PI/360), 1, 0, 0);
		//model things
		glRotated(-90,0,1,0);
		glRotated(-90,1,0,0);

		glScalef(size_*0.5,size_*0.5,size_*0.5);
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
	Button<Producer>* buttonIncreaseStrength = new Button<Producer>(this, &Producer::increaseSpreadStrength, cml::vector2f(0.28, 0.1), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonIncreaseStrength->addSubElement(imagedecreaseS);
	Button<Producer>* buttonDecreaseStrength = new Button<Producer>(this, &Producer::decreaseSpreadStrength, cml::vector2f(0.28, 0.6), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonDecreaseStrength->addSubElement(imageincreaseS);
	
	//Particle
	//Mass
	ImageElement* imageIncMass = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imageIncMass->setImage("assets/buttonPlus.png");
	ImageElement* imageDecMass = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imageDecMass->setImage("assets/buttonMinus.png");
	Button<Producer>* buttonincreaseMass= new Button<Producer>(this, &Producer::increaseMass, cml::vector2f(0.528, 0.1), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseMass->addSubElement(imageIncMass);
	Button<Producer>* buttondecreaseMass= new Button<Producer>(this, &Producer::decreaseMass, cml::vector2f(0.528, 0.6), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttondecreaseMass->addSubElement(imageDecMass);
	//Size
	ImageElement* imageIncSize = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imageIncSize->setImage("assets/buttonPlus.png");
	ImageElement* imageDecSize = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imageDecSize->setImage("assets/buttonMinus.png");
	Button<Producer>* buttonincreaseSize= new Button<Producer>(this, &Producer::increaseSize, cml::vector2f(0.64, 0.1), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseSize->addSubElement(imageIncSize);
	Button<Producer>* buttondecreaseSize= new Button<Producer>(this, &Producer::decreaseSize, cml::vector2f(0.64, 0.6), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttondecreaseSize->addSubElement(imageDecSize);
	//Lifetime
	ImageElement* imageIncLife = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imageIncLife->setImage("assets/buttonPlus.png");
	ImageElement* imageDecLife = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imageDecLife->setImage("assets/buttonMinus.png");
	Button<Producer>* buttonincreaseLife= new Button<Producer>(this, &Producer::increaseLifeTime, cml::vector2f(0.815, 0.1), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseLife->addSubElement(imageIncLife);
	Button<Producer>* buttondecreaseLife= new Button<Producer>(this, &Producer::decreaseLifeTime, cml::vector2f(0.815, 0.6), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttondecreaseLife->addSubElement(imageDecLife);
	//Color
	ImageElement* imageColor = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imageColor->setImage("assets/buttonMinus.png");
	Button<Producer>* buttonColor= new Button<Producer>(this, &Producer::changeColor, cml::vector2f(0.9125, 0.16), cml::vector2f(0.06,0.6), cml::vector4f(0.4,0.4,0.4,0));
	buttonColor->addSubElement(imageColor);

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
	Button<Producer>* buttonincreaseStrength= new Button<Producer>(this, &Producer::increaseStrength, cml::vector2f(0.4125, 0.1), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseStrength->addSubElement(imageincreaseStrength);
	Button<Producer>* buttondecreaseStrength= new Button<Producer>(this, &Producer::decreaseStrength, cml::vector2f(0.4125, 0.6), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
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
	//Particle
	//MASS
	hudElement->addSubElement(buttonincreaseMass);
	hudElement->addSubElement(buttondecreaseMass);
	//Size
	hudElement->addSubElement(buttonincreaseSize);
	hudElement->addSubElement(buttondecreaseSize);
	//Life
	hudElement->addSubElement(buttonincreaseLife);
	hudElement->addSubElement(buttondecreaseLife);
	//Color
	hudElement->addSubElement(buttonColor);
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
	else{
		spreadStrength_=0;
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
	alpha_ += 10  * (2*M_PI /360);
	initialForce_[1]=(std::sin(beta_)*lenght);
	initialForce_[2]=std::cos(beta_)*cos(alpha_)*lenght;
	initialForce_[0]=std::cos(beta_)*sin(alpha_)*lenght;
}

void Producer::increaseDirecY()
{
	GLfloat lenght= initialForce_.length();
	beta_ += 10 * (2*M_PI /360);
	initialForce_[1]=(std::sin(beta_)*lenght);
	initialForce_[2]=std::cos(beta_)*cos(alpha_)*lenght;
	initialForce_[0]=std::cos(beta_)*sin(alpha_)*lenght;
}

void Producer::decreaseDirecX()
{
	GLfloat lenght= initialForce_.length();
	alpha_ -= 10 * (2*M_PI /360);
	initialForce_[1]=(std::sin(beta_)*lenght);
	initialForce_[2]=std::cos(beta_)*cos(alpha_)*lenght;
	initialForce_[0]=std::cos(beta_)*sin(alpha_)*lenght;
}

void Producer::decreaseDirecY()
{
	GLfloat lenght= initialForce_.length();
	beta_ -= 10 * (2*M_PI /360);
	initialForce_[1]=(std::sin(beta_)*lenght);
	initialForce_[2]=std::cos(beta_)*cos(alpha_)*lenght;
	initialForce_[0]=std::cos(beta_)*sin(alpha_)*lenght;
}

void Producer::increaseStrength()
{
	GLfloat lenght= initialForce_.length() + 0.002;
	initialForce_[1]=(std::sin(beta_)*lenght);
	initialForce_[2]=std::cos(beta_)*cos(alpha_)*lenght;
	initialForce_[0]=std::cos(beta_)*sin(alpha_)*lenght;
}
void Producer::decreaseStrength()
{
	GLfloat lenght;
	if(initialForce_.length() > 0.002){
		lenght= initialForce_.length() - 0.002;
	}
	else{
		lenght = 0;
	}
	initialForce_[1]=(std::sin(beta_)*lenght);
	initialForce_[2]=std::cos(beta_)*cos(alpha_)*lenght;
	initialForce_[0]=std::cos(beta_)*sin(alpha_)*lenght;
}
//Particle

void Producer::increaseMass()
{
	particleSpecification_.mass+=0.2;
}
void Producer::decreaseMass()
{
	if(particleSpecification_.mass>0.2)	{
		particleSpecification_.mass-=0.2;
	}
}
void Producer::increaseSize()
{
	particleSpecification_.size+=0.01;
}
void Producer::decreaseSize()
{
	if(particleSpecification_.size>0.02){	
		particleSpecification_.size-=0.01;
	}
}
void Producer::increaseLifeTime()
{
	particleSpecification_.lifetime+=10;
}
void Producer::decreaseLifeTime()
{
	if(particleSpecification_.lifetime>=10){
		particleSpecification_.lifetime-=10;
	}
}
void Producer::changeColor()
{
	cml::vector4d color;
	color.random(0,1);
	color[3]=0;
	particleSpecification_.color=color;
}
