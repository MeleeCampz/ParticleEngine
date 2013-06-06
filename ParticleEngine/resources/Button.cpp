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
	//Draw HudElement background rect
	HudElement::draw();
	//Draw an octangon around the button:
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		glOrtho(0,glutGet(GLUT_WINDOW_WIDTH),0,glutGet(GLUT_WINDOW_HEIGHT),-1,1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glBegin(GL_TRIANGLE_FAN);
				glColor4f(1,1,1,0);
				glVertex2i(position_[0]-3,position_[1]-3);
				glVertex2i(position_[0]+size_[0]/2,position_[1]-10);
				glVertex2i(position_[0]+3+size_[0],position_[1]-3);
				glVertex2i(position_[0]+10+size_[0],position_[1]+size_[1]/2);
				glColor4f(0.3,0.3,0.3,0);
				glVertex2i(position_[0]+size_[0]+5,position_[1]+size_[1]+3);
				glVertex2i(position_[0]+size_[0]/2,position_[1]+size_[1]+10);
				glVertex2i(position_[0]-5,position_[1]+size_[1]+3);
				glVertex2i(position_[0]-10,position_[1]+size_[1]/2);
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
		if(position[0]>position_[0] && position[1]<glutGet(GLUT_WINDOW_HEIGHT) -position_[1] && position[0]<position_[0]+size_[0] && position[1]>glutGet(GLUT_WINDOW_HEIGHT)-position_[1]-size_[1]){
			(*funktion_)();
		}
	}
}

//TODO:
// Numbers 800 and 600 have to be changed to const/vars