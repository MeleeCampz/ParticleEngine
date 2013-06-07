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
	return 0;
}
