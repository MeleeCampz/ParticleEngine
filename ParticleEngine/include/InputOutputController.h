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

	void update();
	void draw();
	void keyboard(unsigned char key,int x, int y);
	void mouseClick(int button, int state, int x, int y);
private:
	cml::vector3f		cameraPosition_;
	Engine*				engine_;
	HudElement*			hudElementBottom_;
	HudElement*			hudElementRight_;
	SelectableObject*	selectedObject_;
	//Noch nicht im KlassenDiagramm:
	GLfloat			distanceToCenter_;
	GLfloat			angleX;	//Rotation around the Y-Axe
	GLfloat			angleY; //Rotation around the X-Axe

	void initSzeneLight();
	void initSzeneMaterial();
	//zum wieder löschen
	std::list<HudElement*> buttonlist;
	HudElement	hud;
};
