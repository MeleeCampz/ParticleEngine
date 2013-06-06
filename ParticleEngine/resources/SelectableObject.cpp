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

HudElement SelectableObject::getHudElement(cml::vector2i size)
{
	//test
	void(*test_ptr)()(&test_func);
	return Button(test_ptr,cml::vector2i(350,750),cml::vector2i(100,50),cml::vector4f(0.5,0.5,0.5,0));
}
