#include "..\include\InputOutputController.h"

#include <math.h>

//wieder löschen:
#include "HudElement.h"
#include"Button.h"
#include "Image.h"
void InputOutputController::addAffector()
{
	//AttractorLocal:
	AttractorLocal* att= new AttractorLocal(cml::vector3i(0,0,-5),-0.003);	
	engine_->addAffector(att);
}

void InputOutputController::addProducer()
{
	Particle::ParticleSpecification particleSpecification;
	particleSpecification.mass = 1.0;
	particleSpecification.lifetime = 1000;
	particleSpecification.color = cml::vector4f(0.0, 1.0, 1.0, 0.00);
	particleSpecification.size = 0.1;
	Producer* prod= new Producer(cml::vector3i(-10,0,5),0.5,cml::vector3f(0.1,0,0),0.1,particleSpecification);
	engine_->addProducer(prod);
}
//Ende wieder löschen
InputOutputController::InputOutputController(void)
{
	engine_ = new Engine();

	distanceToCenter_= 50;
	cameraPosition_=cml::vector3f(0,0,distanceToCenter_);
	angleX=0;
	angleY=0;
	gridRange_=30;
	clicked=false;

	//wieder löschen:
	//button1:
		//Images::
		Image* img=new Image(cml::vector2f(0.0,0.0),cml::vector2f(1.0,1.0),cml::vector4f(1,1,1,1));
		img->setImage("test.png");
		//Button:
		Button<InputOutputController>* newAtr = new Button<InputOutputController>(this, &InputOutputController::addAffector, cml::vector2f(0.025, 0.1),cml::vector2f(0.95,0.3), cml::vector4f(1.0, 0.0, 0.0, 0.0));
		newAtr->addSubElement(img);
	//button2:
		//Images::
		Image* img2=new Image(cml::vector2f(0.0,0.0),cml::vector2f(1.0,1.0),cml::vector4f(1,1,1,1));
		img2->setImage("floor.jpg");
		//Button:
		Button<InputOutputController>* newProd = new Button<InputOutputController>(this, &InputOutputController::addProducer, cml::vector2f(0.025, 0.5),cml::vector2f(0.95,0.3), cml::vector4f(1.0, 0.0, 0.0, 0.0));
		newProd->addSubElement(img2);
	//right hudElement
	hud=new HudElement(cml::vector2f(0.9,0.1),cml::vector2f(0.1,0.8),cml::vector4f(0,0.8,0,0.6));
	hud->addSubElement(newAtr);
	hud->addSubElement(newProd);
	//ende wieder löschen
	
	hudElementRight_=hud;
	hudElementBottom_=0;

}


InputOutputController::~InputOutputController(void)
{
	delete engine_;
}


void InputOutputController::update()
{
	engine_->update();
}


void InputOutputController::draw()
{
	glPushMatrix();
		glColor3f(1,1,1);
		glPushMatrix();
			gluLookAt(	cameraPosition_[0],	cameraPosition_[1],	cameraPosition_[2],			
						0,					0,					0,
						0,					1,					0					);
			//glutSolidTeapot(1);
			initSzeneLight();
			initSzeneMaterial();
			engine_->draw();
			drawGrid();
			if(clicked){
				select3dObject(currentMousePosX_,currentMousePosY_);
				clicked=false;
			}
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT),0,-10,10);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		initHudLight();
		initSzeneMaterial();
		if(hudElementBottom_!=0){
			hudElementBottom_->draw();
		}
		if(hudElementRight_!=0){
			hudElementRight_->draw();
		}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ((float)800)/600,1, 300);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void InputOutputController::keyboard(unsigned char key,int x, int y)
{
	if((int)key==27){ //ESC-KEY
		exit(0);
	}
	switch (key)
	{
		case 'r':
			angleX=0;
			angleY=0;
			distanceToCenter_=10;
			break;
		case 'w':
			if(angleY<89){
				angleY+=2;
			}
			break;
		case 'a':
				angleX-=2;
			break;
		case 's':
			if(angleY>-89){
				angleY-=2;
			}
			break;
		case 'd':
				angleX+=2;
			break;
		case 'q':
			distanceToCenter_++;
			break;
		case 'e':
			distanceToCenter_--;
			break;
	}
	//Calculation the Coordinates of the camera on a sphera around the center of coor-system with the radius=distanceToCenter
	cameraPosition_[1]=(std::sin(angleY*(2*M_PI/360))*distanceToCenter_);
	cameraPosition_[2]=std::cos(angleY*(2*M_PI/360))*cos(angleX*(2*M_PI/360))*distanceToCenter_;
	cameraPosition_[0]=std::cos(angleY*(2*M_PI/360))*sin(angleX*(2*M_PI/360))*distanceToCenter_;
}

void InputOutputController::mouseClick(int button, int state ,int x, int y)
{
	GLboolean wasclicked=false;
	if(button==GLUT_LEFT_BUTTON && state==GLUT_UP){
		if(hudElementBottom_ != 0){
			wasclicked=hudElementBottom_->mouseClick(button,state,cml::vector2i(x,y));
		}
		if(hudElementRight_ != 0 && !wasclicked){
			wasclicked=hudElementRight_->mouseClick(button,state,cml::vector2i(x,y));
		}
		if(!wasclicked){
			clicked=true;
		}
	}
}

void InputOutputController::mousePos(int x, int y){
	currentMousePosX_=x;
	currentMousePosY_=y;
}

void InputOutputController::initSzeneLight()
{
    glEnable(GL_LIGHTING);

    // set color of the light
    GLfloat ambient[4]  = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuse[4]  = { 0.6f, 0.6f, 0.6f, 1.0f };
    GLfloat specular[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
	//settings for Light0
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	//Set Light0 at 0,0,0
	GLfloat positionLight0[4]= {0,20,0,0};
	glLightfv(GL_LIGHT0, GL_POSITION,positionLight0);
}

void InputOutputController::initSzeneMaterial()
{
	// set material values
	GLfloat globalAmbient[4] = {0.0, 0.0, 0.0, 1.0};
    GLfloat ambient[4]       = {0.0, 0.0, 0.0, 1.0};
    GLfloat diffuse[4]       = {1.0, 1.0, 1.0, 1.0};
    GLfloat specular[4]      = {1.0, 1.0, 1.0, 1.0};


    // settings for material
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
    glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,16.0f);

}

void InputOutputController::initHudLight()
{
	glEnable(GL_LIGHTING);

    // set color of the light
    GLfloat ambient[4]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat diffuse[4]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat specular[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	//settings for Light0
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	//Set Light0 at 0,0,0
	GLfloat positionLight0[4]= {0,0,0,1};
	glLightfv(GL_LIGHT0, GL_POSITION,positionLight0);
}

void InputOutputController::initHudMaterial()
{
	// set material values
	GLfloat globalAmbient[4] = {0.0, 0.0, 0.0, 0.0};
    GLfloat ambient[4]       = {1.0, 1.0, 1.0, 1.0};
    GLfloat diffuse[4]       = {0.0, 0.0, 0.0, 1.0};
    GLfloat specular[4]      = {0.0, 0.0, 0.0, 0.0};


    // settings for material
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
    glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,16.0f);
}

void InputOutputController::select3dObject(int x, int y)
{
	if(hudElementBottom_!=0){
		delete hudElementBottom_;
	}
	//the selected Object
	SelectableObject* selected=0;
	//varibales to save the results
	GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
	GLfloat winX,winY,winZ;
    GLdouble posX, posY, posZ;

	//get the matrix for each MatrixMode
	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
	winX = (float)x;
	winY = (float)viewport[3]-(float)y;
	glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	//get the mouse coords on the near clipping plane
	gluUnProject( winX,winY,winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	cml::vector3f mouseOnNearClippingPlane = cml::vector3f(posX,posY,posZ);
	std::cout<<mouseOnNearClippingPlane[0]<<"  "<<mouseOnNearClippingPlane[1]<<"  "<<mouseOnNearClippingPlane[2]<<std::endl;
	
	//get the list of all selectable Objects and save the closet one that hit´s the ray
	std::list<SelectableObject*> allSelectableObjects=engine_->getSelectableObjects();
	for(std::list<SelectableObject*>::iterator itr=allSelectableObjects.begin();itr!=allSelectableObjects.end();itr++){
		if(((*itr)->getPos()-mouseOnNearClippingPlane).length()<3){
			selected=*itr;
		}
	}
	if(selected!=0){
		hudElementBottom_=selected->getHudElement(cml::vector2f(0.6,0.2));
	}
	else{
		hudElementBottom_=0;
	}
}

void InputOutputController::drawGrid()
{
	glEnable(GL_BLEND);
	for(GLint i= -gridRange_; i<=gridRange_;i++){
		glColor4d(0.0,1.0,0.0,0.6);
		glBegin(GL_LINES);
			glVertex3i(i,0,gridRange_);
			glVertex3i(i,0,-gridRange_);
		glEnd();
		glBegin(GL_LINES);
			glVertex3i(gridRange_,0,i);
			glVertex3i(-gridRange_,0,i);
		glEnd();
	}
	glBegin(GL_QUADS);
		glColor4d(0.3,0.3,0.3,0.6);	
		glVertex3i(-gridRange_,0,-gridRange_);
		glVertex3i(gridRange_,0,-gridRange_);
		glVertex3i(gridRange_,0,gridRange_);
		glVertex3i(-gridRange_,0,gridRange_);
	glEnd();
	glDisable(GL_BLEND);
}

