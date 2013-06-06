#include "..\include\HudElement.h"


HudElement::HudElement(cml::vector2i position,cml::vector2i size,cml::vector4f backgroundColor,std::list<HudElement*> subElements):
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
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		glOrtho(0,glutGet(GLUT_WINDOW_WIDTH),0,glutGet(GLUT_WINDOW_HEIGHT),-1,1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glBegin(GL_QUADS);
			glColor4f(backgroundColor_[0],backgroundColor_[1],backgroundColor_[2],backgroundColor_[3]);
				glVertex2i(position_[0],position_[1]);
				glVertex2i(position_[0]+size_[0],position_[1]);
				glVertex2i(position_[0]+size_[0],position_[1]+size_[1]);
				glVertex2i(position_[0],position_[1]+size_[1]);
			glEnd();
			glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	for(std::list<HudElement*>::iterator itr = subElements_.begin();itr!=subElements_.end();itr++){
		(*itr)->draw();
	}
}

void HudElement::mouseClick(int button, int state, cml::vector2i position)
{
}