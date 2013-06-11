#include "..\include\AttractorLocal.h"


AttractorLocal::AttractorLocal(cml::vector3f position, GLfloat strength):
	Affector(position),
	strength_(strength)
{
	model_ = oogl::loadModel("assets/deathstar/dstar.3ds", oogl::Model::LOAD_NORMALIZE_TWO);
}


AttractorLocal::~AttractorLocal(void)
{
}


void AttractorLocal::draw()
{
	glPushMatrix();
		glTranslatef(position_[0], position_[1], position_[2]);
		glScalef(size_*0.5,size_*0.5,size_*0.5);
		glColor4f(1.0, 1.0, 1.0, 0.0);
		//glutSolidSphere(size_, 10, 10);
		model_->render();
	glPopMatrix();
}


void AttractorLocal::affect(Particle* particle)
{
	cml::vector3f difference = position_ - particle->getPosition();
	GLfloat distance = difference.length();

	cml::vector3f force = cml::normalize(difference);
	// maximum force length is strength
	if( distance > strength_ ){
		force *= strength_ / distance;
	}
	else{
		force *= strength_;
	}

	particle->addForce(force);
}


HudElement* AttractorLocal::getHudElement(cml::vector2f size)
{
	HudElement* hudElement = new HudElement(size);
	hudElement->setPosition(cml::vector2f(0.0,1.0-size[1]));

	ImageElement* hudBG = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	hudBG->setImage("assets/hudBG1.png");
	
	ImageElement* imageincreaseX = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imageincreaseX->setImage("assets/x-.png");
	ImageElement* imagedecreaseX = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imagedecreaseX->setImage("assets/x+.png");
	
	ImageElement* imageincreaseY = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imageincreaseY->setImage("assets/y-.png");
	ImageElement* imagedecreaseY = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imagedecreaseY->setImage("assets/y+.png");
	
	ImageElement* imageincreaseZ = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imageincreaseZ->setImage("assets/z-.png");
	ImageElement* imagedecreaseZ = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imagedecreaseZ->setImage("assets/z+.png");

	ImageElement* imageincreaseS = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imageincreaseS->setImage("assets/s-.png");
	ImageElement* imagedecreaseS = new ImageElement(cml::vector2f(0,0),cml::vector2i(1,1),cml::vector4d(0,0,0,0));
	imagedecreaseS->setImage("assets/s+.png");
	
	Button<AttractorLocal>* buttonIncreaseStrength = new Button<AttractorLocal>(this, &AttractorLocal::increaseStrength, cml::vector2f(0.7, 0.1), cml::vector2f(0.1,0.3), cml::vector4f(0.0, 1.0, 0.0, 0.0));
	buttonIncreaseStrength->addSubElement(imagedecreaseS);
	Button<AttractorLocal>* buttonDecreaseStrength = new Button<AttractorLocal>(this, &AttractorLocal::decreaseStrength, cml::vector2f(0.7, 0.6), cml::vector2f(0.1,0.3), cml::vector4f(1.0, 0.0, 0.0, 0.0));
	buttonDecreaseStrength->addSubElement(imageincreaseS);

	Button<AttractorLocal>* buttonincreaseX= new Button<AttractorLocal>(this, &AttractorLocal::decreasePosX, cml::vector2f(0.0, 0.4), cml::vector2f(0.1,0.3), cml::vector4f(0.0, 1.0, 0.0, 0.0));
	buttonincreaseX->addSubElement(imageincreaseX);
	Button<AttractorLocal>* buttondecreaseX= new Button<AttractorLocal>(this, &AttractorLocal::increasePosX, cml::vector2f(0.3, 0.4), cml::vector2f(0.1,0.3), cml::vector4f(1.0, 0.0, 0.0, 0.0));
	buttondecreaseX->addSubElement(imagedecreaseX);

	Button<AttractorLocal>* buttonincreaseY= new Button<AttractorLocal>(this, &AttractorLocal::decreasePosY, cml::vector2f(0.5, 0.6), cml::vector2f(0.1,0.3), cml::vector4f(1.0, 0.0, 0.0, 0.0));
	buttonincreaseY->addSubElement(imageincreaseY);
	Button<AttractorLocal>* buttondecreaseY= new Button<AttractorLocal>(this, &AttractorLocal::increasePosY, cml::vector2f(0.5, 0.1), cml::vector2f(0.1,0.3), cml::vector4f(1.0, 0.0, 0.0, 0.0));
	buttondecreaseY->addSubElement(imagedecreaseY);

	Button<AttractorLocal>* buttonincreaseZ= new Button<AttractorLocal>(this, &AttractorLocal::increasePosZ, cml::vector2f(0.15, 0.6), cml::vector2f(0.1,0.3), cml::vector4f(1.0, 0.0, 0.0, 0.0));
	buttonincreaseZ->addSubElement(imageincreaseZ);
	Button<AttractorLocal>* buttondecreaseZ= new Button<AttractorLocal>(this, &AttractorLocal::decreasePosZ, cml::vector2f(0.15, 0.1), cml::vector2f(0.1,0.3), cml::vector4f(0.0, 1.0, 0.0, 0.0));
	buttondecreaseZ->addSubElement(imagedecreaseZ);
	
	hudElement->addSubElement(buttonIncreaseStrength);
	hudElement->addSubElement(buttonDecreaseStrength);
	hudElement->addSubElement(buttonincreaseX);
	hudElement->addSubElement(buttondecreaseX);
	hudElement->addSubElement(buttonincreaseY);
	hudElement->addSubElement(buttondecreaseY);
	hudElement->addSubElement(buttonincreaseZ);
	hudElement->addSubElement(buttondecreaseZ);
	hudElement->addSubElement(hudBG);

	return hudElement;
}


void AttractorLocal::increaseStrength()
{
	strength_ += 0.01;
}


void AttractorLocal::decreaseStrength()
{
	strength_ -= 0.01;
}

void AttractorLocal::increasePosX()
{
	position_[0]+=1;
}
void AttractorLocal::decreasePosX()
{
	position_[0]-=1;
}
void AttractorLocal::increasePosY()
{
	position_[1]+=1;
}
void AttractorLocal::decreasePosY()
{
	position_[1]-=1;
}
void AttractorLocal::increasePosZ()
{
	position_[2]+=1;
}
void AttractorLocal::decreasePosZ()
{
	position_[2]-=1;
}