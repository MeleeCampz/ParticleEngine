#include "..\include\SelectableObject.h"


SelectableObject::SelectableObject(void)
{
	isHudElementUsed=true;
}


SelectableObject::~SelectableObject(void)
{
}

void SelectableObject::freeHudElement()
{
}

//test:
void test_func()
{
std::cout<<"Button wurde gedrückt"<<std::endl;
}

HudElement SelectableObject::getHudElement(cml::vector2f size)
{
	//test
	void(*test_ptr)()(&test_func);
	return Button(test_ptr,cml::vector2f(0.5,0.8),cml::vector2f(0.2,0.1),cml::vector4f(0.5,0.5,0.5,0));
}
