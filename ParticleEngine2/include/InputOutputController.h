#pragma once

#include <cml\cml.h>
#include <Glee/GLee.h>
#include <GL/glut.h>
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
	void mousePos(int x, int y);
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
	GLint			gridRange_;

	void initSzeneLight();
	void initSzeneMaterial();
	void initHudLight();
	void initHudMaterial();
	void select3dObject(int x, int y);
	void drawGrid();

	GLboolean clicked;
	GLint currentMousePosX_,currentMousePosY_;
	//zum wieder löschen
	HudElement*	hud;
	void addAffector();
	void addProducer();
	void deleteSelectedObj();
};
