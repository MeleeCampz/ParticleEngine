#include "..\include\InputOutputController.h"


InputOutputController::InputOutputController(void)
{
	cameraPosition_=cml::vector3f(0,0,-10);
	gluLookAt(cameraPosition_[0],cameraPosition_[1],cameraPosition_[2],0,0,0,0,1,1);


}


InputOutputController::~InputOutputController(void)
{
}

void InputOutputController::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//test
	glPushMatrix();
		glTranslated(0.0, 0.0, -10.0);
		glutSolidTeapot(1.0);
	glPopMatrix();

	glutSwapBuffers();
}

void InputOutputController::keyboard(unsigned char key,int x, int y)
{
	switch (key)
	{
		case 'w':
			break;
		case 'a':
			break;
		case 's':
			break;
		case 'd':
			break;
		default:
			break;
	}
}

void InputOutputController::mouseClick(int button, int x, int y)
{
}
