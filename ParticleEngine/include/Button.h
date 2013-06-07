#pragma once

#include "HudElement.h"

class Button : public HudElement
{
public:
	Button(void(*funktion)(),cml::vector2f position,cml::vector2f size,cml::vector4f backgroundColor);
	~Button(void);

	void draw();
	GLboolean mouseClick(int button, int state, cml::vector2i position);
private:
	void(*funktion_)();
};
