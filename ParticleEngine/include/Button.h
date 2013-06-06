#pragma once

#include "HudElement.h"

class Button : public HudElement
{
public:
	Button(void(*funktion)(),cml::vector2i position,cml::vector2i size,cml::vector4f backgroundColor);
	~Button(void);

	void draw();
	void mouseClick(int button, int state, cml::vector2i position);
private:
	void(*funktion_)();
};
