#include "..\include\Friction.h"


Friction::Friction(cml::vector3f position, GLfloat strength):
	Affector(position),
	strength_(strength)
{
	model_ = oogl::loadModel("assets/endor/endor.3ds", oogl::Model::LOAD_NORMALIZE_TWO);
}


Friction::~Friction(void)
{
}


void Friction::draw()
{
	glPushMatrix();
		glTranslatef(position_[0], position_[1], position_[2]);
		//glRotated(alpha_,0,1,0);	
		//glRotated(-beta_,1,0,0);	
		glScalef(size_*0.5,size_*0.5,size_*0.5);
		glColor4f(1.0, 1.0, 1.0, 0.0);
		//glutSolidSphere(size_, 10, 10);
		model_->render();
	glPopMatrix();
}


void Friction::affect(Particle* particle)
{
	cml::vector3f force = particle->getVelocity() * (-strength_);

	particle->addForce(force);
}


HudElement* Friction::getHudElement(cml::vector2f size)
{
	HudElement* hudElement = new HudElement(size);
	hudElement->setPosition(cml::vector2f(0.0,1.0-size[1]));

	ImageElement* hudBG = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	hudBG->setImage("assets/FrictionBG.png");

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

	//Strengh
	ImageElement* imageincreaseStrength = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imageincreaseStrength->setImage("assets/buttonPlus.png");
	ImageElement* imagedecreaseStrength = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imagedecreaseStrength->setImage("assets/buttonMinus.png");


	//Pos
	Button<Friction>* buttonincreaseX= new Button<Friction>(this, &Friction::decreasePosX, cml::vector2f(0.05, 0.1), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseX->addSubElement(imageincreaseX);
	Button<Friction>* buttondecreaseX= new Button<Friction>(this, &Friction::increasePosX, cml::vector2f(0.01, 0.1), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttondecreaseX->addSubElement(imagedecreaseX);

	Button<Friction>* buttonincreaseY= new Button<Friction>(this, &Friction::decreasePosY, cml::vector2f(0.05, 0.35), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseY->addSubElement(imageincreaseY);
	Button<Friction>* buttondecreaseY= new Button<Friction>(this, &Friction::increasePosY, cml::vector2f(0.01, 0.35), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttondecreaseY->addSubElement(imagedecreaseY);

	Button<Friction>* buttonincreaseZ= new Button<Friction>(this, &Friction::increasePosZ, cml::vector2f(0.05, 0.6), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseZ->addSubElement(imageincreaseZ);
	Button<Friction>* buttondecreaseZ= new Button<Friction>(this, &Friction::decreasePosZ, cml::vector2f(0.01, 0.6), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttondecreaseZ->addSubElement(imagedecreaseZ);

	//Strengh
	Button<Friction>* buttonincreaseStrength= new Button<Friction>(this, &Friction::increaseStrength, cml::vector2f(0.28, 0.1), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttonincreaseStrength->addSubElement(imageincreaseStrength);
	Button<Friction>* buttondecreaseStrength= new Button<Friction>(this, &Friction::decreaseStrength, cml::vector2f(0.28, 0.6), cml::vector2f(0.03,0.15), cml::vector4f(0.4,0.4,0.4,0));
	buttondecreaseStrength->addSubElement(imagedecreaseStrength);

	//POS
	hudElement->addSubElement(buttonincreaseX);
	hudElement->addSubElement(buttondecreaseX);
	hudElement->addSubElement(buttonincreaseY);
	hudElement->addSubElement(buttondecreaseY);
	hudElement->addSubElement(buttonincreaseZ);
	hudElement->addSubElement(buttondecreaseZ);
	//STRENGTH
	hudElement->addSubElement(buttondecreaseStrength);
	hudElement->addSubElement(buttonincreaseStrength);
	//BG
	hudElement->addSubElement(hudBG);


	return hudElement;
}

void Friction::increasePosX()
{
	position_[0]+=1;
}
void Friction::decreasePosX()
{
	position_[0]-=1;
}
void Friction::increasePosY()
{
	position_[1]+=1;
}
void Friction::decreasePosY()
{
	position_[1]-=1;
}
void Friction::increasePosZ()
{
	position_[2]+=1;
}
void Friction::decreasePosZ()
{
	position_[2]-=1;
}

void Friction::increaseStrength()
{
	strength_ += 0.002;
}


void Friction::decreaseStrength()
{
	strength_ -= 0.002;
}