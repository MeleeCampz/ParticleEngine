#pragma once

#include "HudElement.h"
#include "cml\cml.h"
#include "GL\glut.h"

//wieder entfernen:
#include "Button.h"

class SelectableObject
{
public:
	SelectableObject(void);
	~SelectableObject(void);

	GLboolean	isHudElementUsed;

	void freeHudElement();
	cml::vector3i getPos();
	GLint getSize();
	virtual HudElement* getHudElement(cml::vector2f size);
private:
	HudElement hudElement_;
protected:
	cml::vector3i	position_;
	GLint			size_;
};
