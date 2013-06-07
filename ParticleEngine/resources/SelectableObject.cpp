#include "..\include\SelectableObject.h"


SelectableObject::SelectableObject(cml::vector3f position):
	position_(position),
	size_(0.5)
{
}


SelectableObject::~SelectableObject(void)
{
}


cml::vector3i SelectableObject::getPos()
{
	return position_;
}


GLfloat SelectableObject::getSize()
{
	return size_;
}


HudElement* SelectableObject::getHudElement(cml::vector2f size)
{
	//test
	return new Button(nullptr,cml::vector2f(0.0,0.0),size,cml::vector4f(0.5,0.5,0.5,0));
}
