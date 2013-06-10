#pragma once

#include "HudElement.h"

template <class T>
class Button : 
	public HudElement
{
public:
	Button(T* thisObject, void(T::*funktion)(),cml::vector2f position,cml::vector2f size,cml::vector4f backgroundColor):
		HudElement(position, size, backgroundColor),
		thisObject_(thisObject),
		funktion_(funktion)
	{
	}

	~Button(void)
	{
	}

	void draw()
	{
		HudElement::draw();
		//windowSize_=cml::vector2i(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
		//Draw an octangon around the button:
		glBegin(GL_TRIANGLE_FAN);
			glColor4f(0.4,0.4,0.4,0);
			glVertex2i(position_[0]*windowSize_[0]-1,position_[1]*windowSize_[1]-1);
			glVertex2i(position_[0]*windowSize_[0]+size_[0]*windowSize_[0]/2,position_[1]*windowSize_[1]-5);
			glVertex2i(position_[0]*windowSize_[0]+1+size_[0]*windowSize_[0],position_[1]*windowSize_[1]-1);
			glVertex2i(position_[0]*windowSize_[0]+5+size_[0]*windowSize_[0],position_[1]*windowSize_[1]+size_[1]*windowSize_[1]/2);
			glVertex2i(position_[0]*windowSize_[0]+size_[0]*windowSize_[0]+1,position_[1]*windowSize_[1]+size_[1]*windowSize_[1]+1);
			glVertex2i(position_[0]*windowSize_[0]+size_[0]*windowSize_[0]/2,position_[1]*windowSize_[1]+size_[1]*windowSize_[1]+5);
			glVertex2i(position_[0]*windowSize_[0]-1,position_[1]*windowSize_[1]+size_[1]*windowSize_[1]+1);
			glVertex2i(position_[0]*windowSize_[0]-5,position_[1]*windowSize_[1]+size_[1]*windowSize_[1]/2);
		glEnd();
	}


	GLboolean mouseClick(int button, int state, cml::vector2f position)
	{
		//check if mouse pos is inside the button
		if(position[0]>position_[0]*windowSize_[0] && position[1]>position_[1]*windowSize_[1] && position[0]<(position_[0]+size_[0])*windowSize_[0] && position[1]<(position_[1]+size_[1])*windowSize_[1]){
			if(funktion_!=nullptr){
				(thisObject_->*funktion_)();
				//std::cout<<"hi"<<std::endl;
				return true;
			}
			return true;
		}
		else{
			return false;
		}
	}
private:

	T* thisObject_;

	void(T::*funktion_)();
};
