#include "..\include\HudElement.h"


HudElement::HudElement(cml::vector2f position,cml::vector2f size,cml::vector4f backgroundColor):
	position_(position),
	size_(size),
	backgroundColor_(backgroundColor)
{
}

HudElement::HudElement(cml::vector2f size):
	position_(cml::vector2f(0.0, 0.0)),
	size_(size),
	backgroundColor_(cml::vector4f( 1.0, 1.0, 1.0, 0.0))
{
}

HudElement::~HudElement(void)
{
	for(std::list<HudElement*>::iterator itr = subElements_.begin();itr!=subElements_.end();itr++){
	//	(*itr)->~HudElement();
	}	
}
void HudElement::addSubElement(HudElement* subElement)
{
	subElements_.push_back(subElement);
}
void HudElement::addSubElement(std::list<HudElement*> subElements)
{
	subElements_.merge(subElements);
}

void HudElement::setPosition(cml::vector2f position)
{
	position_=position;
}

void HudElement::draw()
{
	windowSize_=cml::vector2i(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
	//draw a rectangle in the backgroundcolor
	glBegin(GL_QUADS);
		glColor4f(backgroundColor_[0],backgroundColor_[1],backgroundColor_[2],backgroundColor_[3]);
		glVertex2i(position_[0]*windowSize_[0],position_[1]*windowSize_[1]);
		glVertex2i((position_[0]+size_[0])*windowSize_[0],position_[1]*windowSize_[1]);
		glVertex2i((position_[0]+size_[0])*windowSize_[0],(position_[1]+size_[1])*windowSize_[1]);
		glVertex2i(position_[0]*windowSize_[0],(position_[1]+size_[1])*windowSize_[1]);
	glEnd();
	glPushMatrix();
		//translate the matrix towards the camera, so the subElemenst are always on top
		glTranslated(position_[0]*windowSize_[0],position_[1]*windowSize_[1],0.001);
		for(std::list<HudElement*>::iterator itr = subElements_.begin();itr!=subElements_.end();itr++){
			(*itr)->draw();
		}
	glPopMatrix();
}

GLboolean HudElement::mouseClick(int button, int state, cml::vector2i position)
{
	if(position[0]>position_[0]*windowSize_[0] && position[1]>position_[1]*windowSize_[1] && position[0]<(position_[0]+size_[0])*windowSize_[0] && position[1]<(position_[1]+size_[1])*windowSize_[1]){
		for(std::list<HudElement*>::iterator itr = subElements_.begin();itr!=subElements_.end();itr++){
			//calculate the mousecoordinates realative to the HudElement
			(*itr)->mouseClick(button,state,cml::vector2i(position[0]-position_[0]*windowSize_[0],position[1]-position_[1]*windowSize_[1]));
		}
		return true;
	}
	else{
		return false;
	}
}