#include "..\include\SelectableObject.h"


SelectableObject::SelectableObject(void)
{
	isHudElementUsed=true;
	size_=5;
}


SelectableObject::~SelectableObject(void)
{
}

void SelectableObject::freeHudElement()
{
}

cml::vector3i SelectableObject::getPos()
{
	return position_;
}
GLint SelectableObject::getSize()
{
	return size_;
}

//test:
void test_func()
{
std::cout<<"Button wurde gedrückt"<<std::endl;
}

HudElement* SelectableObject::getHudElement(cml::vector2f size)
{
	//test
	return new Button(nullptr,cml::vector2f(0.0,0.0),size,cml::vector4f(0.5,0.5,0.5,0));
}
