#pragma once

#include <cml\cml.h>
#include <Glee/GLee.h>
#include <GL/glut.h>
#include <list>

class HudElement
{
public:
	HudElement(cml::vector2f position,cml::vector2f size,cml::vector4f backgroundColor);
	HudElement(cml::vector2f size);
	virtual ~HudElement(void);

	void addSubElement(HudElement* subElement);
	void addSubElement(std::list<HudElement*> subElements);
	void setPosition(cml::vector2f position);
	virtual void draw();
	virtual GLboolean mouseClick(int button, int state, cml::vector2f position);
protected:
	cml::vector4f backgroundColor_;
	cml::vector2f position_;
	cml::vector2f size_;
	std::list<HudElement*> subElements_;
	cml::vector2i windowSize_;
};
