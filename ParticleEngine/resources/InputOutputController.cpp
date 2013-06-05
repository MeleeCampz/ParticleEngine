#include "..\include\InputOutputController.h"


InputOutputController::InputOutputController(void)
{
	distanceToCenter= 10;
	angleX=0;
	angleY=0;
	cameraPosition_=cml::vector3f(0,0,distanceToCenter);
}


InputOutputController::~InputOutputController(void)
{
}

void InputOutputController::draw()
{
	glPushMatrix();
		glTranslatef(-cameraPosition_[0],-cameraPosition_[1],-cameraPosition_[2]);
		glRotatef(angleX,0,1,0);
		glRotatef(angleY,1,0,0);
		//glutSolidTeapot(1);
		engine_.draw();
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
			cameraPosition_=cml::vector3f(0,0,distanceToCenter);
			break;
		case 'w':
			angleY+=2;
			break;
		case 'a':
			angleX+=2;
			break;
		case 's':
			angleY-=2;
			break;
		case 'd':
			angleX-=2;
			break;
		case 'q':
			cameraPosition_[2]--;
			break;
		case 'e':
			cameraPosition_[2]++;
			break;
	}
	std::cout<<key<<std::endl;
	glutPostRedisplay();
}

void InputOutputController::mouseClick(int button, int x, int y)
{
}
