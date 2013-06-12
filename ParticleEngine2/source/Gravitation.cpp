#include "..\include\Gravitation.h"


Gravitation::Gravitation(cml::vector3f position, cml::vector3f force):
	Affector(position),
	force_(force)
{
	//caluculate the direction the Gravitation is aiming at in two angles
	/*if( force.length() != 0 ){
		beta_ = std::asin( force[1] / force.length() );
		alpha_ = cml:://std::asin( force[1] / (force.length() * cos(beta_)) );
	}
	else{
		beta_ = 1;
		alpha_ = 0;
	}*/

	GLfloat dump;

	cml::cartesian_to_spherical(force, dump, beta_, alpha_, 2, cml::SphericalType::latitude);


	model_ = oogl::loadModel("assets/Apple/apple.3ds", oogl::Model::LOAD_NORMALIZE_TWO);
}


Gravitation::~Gravitation(void)
{
}


void Gravitation::draw()
{
	glPushMatrix();
		glTranslatef(position_[0], position_[1], position_[2]);
		glRotated(alpha_ / (2*M_PI/360), 0, 1, 0);	
		glRotated(-beta_ / (2*M_PI/360), 1, 0, 0);	
		glScalef(size_*0.5,size_*0.5,size_*0.5);
		glRotated(-90, 1, 0, 0);
		glColor4f(1.0, 1.0, 1.0, 0.0);
		//glutSolidSphere(size_, 10, 10);
		model_->render();
	glPopMatrix();
}


void Gravitation::affect(Particle* particle)
{
	particle->addForce(force_);
}


HudElement* Gravitation::getHudElement(cml::vector2f size)
{
	HudElement* hudElement = new HudElement(size);
	hudElement->setPosition(cml::vector2f(0.0,1.0-size[1]));

	ImageElement* hudBG = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	hudBG->setImage("assets/GravitationBG.png");

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


	//Pos
	Button<Gravitation>* buttonincreaseX= new Button<Gravitation>(this, &Gravitation::decreasePosX, cml::vector2f(0.05, 0.1), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseX->addSubElement(imageincreaseX);
	Button<Gravitation>* buttondecreaseX= new Button<Gravitation>(this, &Gravitation::increasePosX, cml::vector2f(0.01, 0.1), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttondecreaseX->addSubElement(imagedecreaseX);

	Button<Gravitation>* buttonincreaseY= new Button<Gravitation>(this, &Gravitation::decreasePosY, cml::vector2f(0.05, 0.6), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseY->addSubElement(imageincreaseY);
	Button<Gravitation>* buttondecreaseY= new Button<Gravitation>(this, &Gravitation::increasePosY, cml::vector2f(0.01, 0.6), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttondecreaseY->addSubElement(imagedecreaseY);

	Button<Gravitation>* buttonincreaseZ= new Button<Gravitation>(this, &Gravitation::increasePosZ, cml::vector2f(0.05, 0.35), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseZ->addSubElement(imageincreaseZ);
	Button<Gravitation>* buttondecreaseZ= new Button<Gravitation>(this, &Gravitation::decreasePosZ, cml::vector2f(0.01, 0.35), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttondecreaseZ->addSubElement(imagedecreaseZ);
	//DIRECT
	Button<Gravitation>* buttonincreaseDirecX= new Button<Gravitation>(this, &Gravitation::decreaseDirecX, cml::vector2f(0.1, 0.1), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseDirecX->addSubElement(imageincreaseX2);
	Button<Gravitation>* buttondecreaseDirecX= new Button<Gravitation>(this, &Gravitation::increaseDirecX, cml::vector2f(0.14, 0.1), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttondecreaseDirecX->addSubElement(imagedecreaseX2);

	Button<Gravitation>* buttonincreaseDirecY= new Button<Gravitation>(this, &Gravitation::decreaseDirecY, cml::vector2f(0.1, 0.5), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseDirecY->addSubElement(imageincreaseY2);
	Button<Gravitation>* buttondecreaseDirecY= new Button<Gravitation>(this, &Gravitation::increaseDirecY, cml::vector2f(0.14, 0.5), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttondecreaseDirecY->addSubElement(imagedecreaseY2);
	//Strengh
	Button<Gravitation>* buttonincreaseStrength= new Button<Gravitation>(this, &Gravitation::increaseStrength, cml::vector2f(0.28, 0.1), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseStrength->addSubElement(imageincreaseStrength);
	Button<Gravitation>* buttondecreaseStrength= new Button<Gravitation>(this, &Gravitation::decreaseStrength, cml::vector2f(0.28, 0.6), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttondecreaseStrength->addSubElement(imagedecreaseStrength);

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

void Gravitation::increasePosX()
{
	position_[0]+=1;
}
void Gravitation::decreasePosX()
{
	position_[0]-=1;
}
void Gravitation::increasePosY()
{
	position_[1]+=1;
}
void Gravitation::decreasePosY()
{
	position_[1]-=1;
}
void Gravitation::increasePosZ()
{
	position_[2]+=1;
}
void Gravitation::decreasePosZ()
{
	position_[2]-=1;
}

void Gravitation::increaseDirecX()
{
	GLfloat lenght= force_.length();
	alpha_ += 10 * (2*M_PI /360);
	force_[1]=(std::sin(beta_)*lenght);
	force_[2]=std::cos(beta_)*cos(alpha_)*lenght;
	force_[0]=std::cos(beta_)*sin(alpha_)*lenght;
}

void Gravitation::increaseDirecY()
{
	GLfloat lenght= force_.length();
	beta_ += 10 * (2*M_PI /360);
	force_[1]=(std::sin(beta_)*lenght);
	force_[2]=std::cos(beta_)*cos(alpha_)*lenght;
	force_[0]=std::cos(beta_)*sin(alpha_)*lenght;
}

void Gravitation::decreaseDirecX()
{
	GLfloat lenght= force_.length();
	alpha_ -= 10 * (2*M_PI /360);
	force_[1]=(std::sin(beta_)*lenght);
	force_[2]=std::cos(beta_)*cos(alpha_)*lenght;
	force_[0]=std::cos(beta_)*sin(alpha_)*lenght;
}

void Gravitation::decreaseDirecY()
{
	GLfloat lenght= force_.length();
	beta_ -= 10 * (2*M_PI /360) ;
	force_[1]=(std::sin(beta_)*lenght);
	force_[2]=std::cos(beta_)*cos(alpha_)*lenght;
	force_[0]=std::cos(beta_)*sin(alpha_)*lenght;
}

void Gravitation::increaseStrength()
{
	GLfloat lenght= force_.length() + 0.002;
	force_[1]=(std::sin(beta_)*lenght);
	force_[2]=std::cos(beta_)*cos(alpha_)*lenght;
	force_[0]=std::cos(beta_)*sin(alpha_)*lenght;
}

void Gravitation::decreaseStrength()
{
	GLfloat lenght;
	if(force_.length() > 0.002){
		lenght= force_.length() - 0.002;
	}
	else{
		lenght = 0;
	}
	force_[1]=(std::sin(beta_)*lenght);
	force_[2]=std::cos(beta_)*cos(alpha_)*lenght;
	force_[0]=std::cos(beta_)*sin(alpha_)*lenght;
}