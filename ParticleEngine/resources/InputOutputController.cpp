#include "..\include\InputOutputController.h"

#include <math.h>

//wieder löschen:
#include"Button.h"
void test(){std::cout<<"button pressed!"<<std::endl;}
void (*test_ptr)()(&test);
Button b=Button(test_ptr,cml::vector2i(200,0),cml::vector2i(400,120),cml::vector4f(1,0.2,0.2,0));


InputOutputController::InputOutputController(void)
{
	engine_ = new Engine();

	distanceToCenter_= 10;
	cameraPosition_=cml::vector3f(0,0,distanceToCenter_);
	angleX=0;
	angleY=0;

	hudElementBottom_=&b;
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
		//hudElementRight_.draw();
		hudElementBottom_->draw();
		//b.draw();
	glPopMatrix();
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
				angleX+=2;
			break;
		case 's':
			if(angleY>-89){
				angleY-=2;
			}
			break;
		case 'd':
				angleX-=2;
			break;
		case 'q':
			distanceToCenter_--;
			break;
		case 'e':
			distanceToCenter_++;
			break;
	}
	//Calculation the Coordinates of the camera on a sphera around the center of coor-system with the radius=distanceToCenter
	cameraPosition_[1]=(std::sin(angleY*(2*M_PI/360))*distanceToCenter_);
	cameraPosition_[2]=std::cos(angleY*(2*M_PI/360))*cos(angleX*(2*M_PI/360))*distanceToCenter_;
	cameraPosition_[0]=std::cos(angleY*(2*M_PI/360))*sin(angleX*(2*M_PI/360))*distanceToCenter_;
}

void InputOutputController::mouseClick(int button, int state ,int x, int y)
{
	b.mouseClick(button,state ,cml::vector2i(x,y));
}
