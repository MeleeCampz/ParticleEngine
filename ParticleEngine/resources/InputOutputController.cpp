#include "..\include\InputOutputController.h"

#include <math.h>

//wieder löschen:
#include "HudElement.h"
#include"Button.h"



InputOutputController::InputOutputController(void)
{
	engine_ = new Engine();

	distanceToCenter_= 10;
	cameraPosition_=cml::vector3f(0,0,distanceToCenter_);
	angleX=0;
	angleY=0;

	buttonlist.push_back(new Button(nullptr,cml::vector2f(0.0,0.1),cml::vector2f(0.2,0.1),cml::vector4f(1,0,0,0)));
	buttonlist.push_back(new Button(nullptr,cml::vector2f(0.0,0.3),cml::vector2f(0.2,0.1),cml::vector4f(0,1,0,0)));
	buttonlist.push_back(new Button(nullptr,cml::vector2f(0.0,0.5),cml::vector2f(0.2,0.1),cml::vector4f(0,0,1,0)));
	hud=HudElement(cml::vector2f(0.8,0.0),cml::vector2f(0.2,1),cml::vector4f(0,0.8,0,0.6),buttonlist);
	hudElementRight_=&hud;
	hudElementBottom_=0;

	initSzeneLight();
	initSzeneMaterial();
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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ((float)800)/600,0.1f, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
		glColor3f(1,1,1);
		glPushMatrix();
			gluLookAt(	cameraPosition_[0],	cameraPosition_[1],	cameraPosition_[2],			
						0,					0,					0,
						0,					1,					0					);
			//glutSolidTeapot(1);
			engine_->draw();
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT),0,-10,10);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//GLfloat positionLight1[4]= {0,0,0,1};
		//glLightfv(GL_LIGHT1, GL_POSITION,positionLight1);
		if(hudElementBottom_!=0){
			hudElementBottom_->draw();
		}
		if(hudElementRight_!=0){
			hudElementRight_->draw();
		}
	glPopMatrix();;
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
	if(hudElementBottom_!=0){
		hudElementBottom_->mouseClick(button,state,cml::vector2i(x,y));
	}
	if(hudElementRight_!=0){
		hudElementRight_->mouseClick(button,state,cml::vector2i(x,y));
	}
}

void InputOutputController::initSzeneLight()
{
    // Beleuchtung global einschalten
    glEnable(GL_LIGHTING);

    // Farben der Lichtquelle setzen (r,g,b,a)
    GLfloat ambient[4]  = { 0.1f, 0.1f, 0.1f, 0.1f };
    GLfloat diffuse[4]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	GLfloat positionLight0[4]= {0,0,0,1};
	glLightfv(GL_LIGHT0, GL_POSITION,positionLight0);
}

void InputOutputController::initSzeneMaterial()
{
	// Materialfarben setzen (r,g,b,a)
    GLfloat globalAmbient[4] = {0.0, 0.0, 0.0, 1.0};
    GLfloat ambient[4]       = {1.0, 1.0, 1.0, 1.0};
    GLfloat diffuse[4]       = {1.0, 1.0, 1.0, 1.0};
    GLfloat specular[4]      = {1.0, 1.0, 1.0, 1.0};


    // Materialparameter setzen
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
    glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,16.0f);

}
