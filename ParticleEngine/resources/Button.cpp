#include "..\include\Button.h"

/*
template <class T>
Button<T>::Button(T* thisObject, void(T::*funktion)(),cml::vector2f position,cml::vector2f size,cml::vector4f backgroundColor):
	HudElement(position, size, backgroundColor)
	thisObject_(thisObject),
	funktion_(funktion)
{
}


template <class T>
Button<T>::~Button(void)
{
}


template <class T>
void Button<T>::draw()
{
	windowSize_=cml::vector2i(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
	//Draw an octangon around the button:
	HudElement::draw();
	glBegin(GL_TRIANGLE_FAN);
		glColor4f(1,1,1,0);
		glVertex2i(position_[0]*windowSize_[0]-3,position_[1]*windowSize_[1]-3);
		glVertex2i(position_[0]*windowSize_[0]+size_[0]*windowSize_[0]/2,position_[1]*windowSize_[1]-10);
		glVertex2i(position_[0]*windowSize_[0]+3+size_[0]*windowSize_[0],position_[1]*windowSize_[1]-3);
		glVertex2i(position_[0]*windowSize_[0]+10+size_[0]*windowSize_[0],position_[1]*windowSize_[1]+size_[1]*windowSize_[1]/2);
		glColor4f(0.3,0.3,0.3,0);
		glVertex2i(position_[0]*windowSize_[0]+size_[0]*windowSize_[0]+5,position_[1]*windowSize_[1]+size_[1]*windowSize_[1]+3);
		glVertex2i(position_[0]*windowSize_[0]+size_[0]*windowSize_[0]/2,position_[1]*windowSize_[1]+size_[1]*windowSize_[1]+10);
		glVertex2i(position_[0]*windowSize_[0]-5,position_[1]*windowSize_[1]+size_[1]*windowSize_[1]+3);
		glVertex2i(position_[0]*windowSize_[0]-10,position_[1]*windowSize_[1]+size_[1]*windowSize_[1]/2);
	glEnd();
}


template <class T>
GLboolean Button<T>::mouseClick(int button, int state, cml::vector2i position)
{
		//check if mouse pos is inside the button
	if(position[0]>position_[0]*windowSize_[0] && position[1]>position_[1]*windowSize_[1] && position[0]<(position_[0]+size_[0])*windowSize_[0] && position[1]<(position_[1]+size_[1])*windowSize_[1]){
		if(funktion_!=nullptr){
			thisObject_->funktion_();
			return true;
		}
		return true;
	}
	else{
		return false;
	}
}

*/
//TODO:
// Numbers 800 and 600 have to be changed to const/vars