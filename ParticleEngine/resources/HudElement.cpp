#include "..\include\HudElement.h"


HudElement::HudElement(cml::vector2i position,cml::vector2i size,cml::vector4f backgroundColor,std::list<HudElement> subElements):
	position_(position),
	size_(size),
	backgroundColor_(backgroundColor),
	subElements_(subElements)
{
}

HudElement::HudElement()
{
}

HudElement::~HudElement(void)
{
}

void HudElement::setPosition(cml::vector2i position)
{
	position_=position;
}

void HudElement::draw()
{
}

void HudElement::mouseClick(int button, int state, cml::vector2i position)
{
}