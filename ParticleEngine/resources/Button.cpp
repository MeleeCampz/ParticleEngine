#include "..\include\Button.h"


Button::Button(void(*funktion)(),cml::vector2i position,cml::vector2i size,cml::vector4f backgroundColor):
	funktion_(funktion)
{
	position_=position;
	size_=size;
	backgroundColor_=backgroundColor;
}

Button::~Button(void)
{
}

void Button::draw()
{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0,800,0,600,-1,1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glBegin(GL_QUADS);
			glColor3f(backgroundColor_[0],backgroundColor_[1],backgroundColor_[2]);
			glVertex2i(position_[0],position_[1]);
			glVertex2i(position_[0]+size_[0],position_[1]);
			glVertex2i(position_[0]+size_[0],position_[1]+size_[1]);
			glVertex2i(position_[0],position_[1]+size_[1]);
		glEnd();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	glPopMatrix();
}

void Button::mouseClick(int button, int state, cml::vector2i position)
{
	//Check if button was realed
	if(button==GLUT_LEFT_BUTTON && state==GLUT_UP){
		//check if button is in right position
		if(position[0]>position_[0] && position[1]<600-position_[1] && position[0]<position_[0]+size_[0] && position[1]>600-position_[1]-size_[1]){
			(*funktion_)();
		}
	}
}

//TODO:
// Numbers 800 and 600 have to be changed to const/vars