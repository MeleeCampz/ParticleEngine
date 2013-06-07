#pragma once

#include "HudElement.h"
#include "cml\cml.h"
#include "GL\glut.h"

//wieder entfernen:
#include "Button.h"

class SelectableObject
{
public:
	SelectableObject(cml::vector3f position);
	~SelectableObject(void);

	cml::vector3i getPos();
	GLfloat getSize();
	virtual HudElement* getHudElement(cml::vector2f size);

protected:
	cml::vector3i	position_;
	GLfloat			size_;
};
