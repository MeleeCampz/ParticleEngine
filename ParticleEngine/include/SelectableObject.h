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
	virtual HudElement getHudElement(cml::vector2i size);
private:
	HudElement hudElement_;
};
