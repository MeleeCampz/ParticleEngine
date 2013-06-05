#pragma once

#include "cml\cml.h"
#include "Engine.h"
#include "HudElement.h"
#include "SelectableObject.h"

class InputOutputController
{
public:
	InputOutputController(void);
	~InputOutputController(void);

	void draw();
	void keyboard(unsigned char key,int x, int y);
	void mouseClick(int button, int x, int y);
private:
	cml::vector3f		cameraPosition_;
	Engine				engine_;
	HudElement			hubElementBottom_;
	HudElement			hudElementEight_;
	SelectableObject	selectedObject_;
	//Noch nicht im KlassenDiagramm:
	GLfloat			distanceToCenter;
	GLfloat			angleX;
	GLfloat			angleY;
};
