#pragma once

#include "cml\cml.h"
#include "GL\glut.h"
#include <list>

class HudElement
{
public:
	HudElement(cml::vector2i position,cml::vector2i size,cml::vector4f backgroundColor,std::list<HudElement*> subElements);
	HudElement();
	~HudElement(void);

	void setPosition(cml::vector2i position);
	virtual void draw();
	virtual void mouseClick(int button, int state, cml::vector2i position);
//Änderung ins Klassendiagramm übernehmen private erlaub zugirff in Unterklasse nicht
protected:
	cml::vector4f backgroundColor_;
	cml::vector2i position_;
	cml::vector2i size_;
	std::list<HudElement*> subElements_;
};
