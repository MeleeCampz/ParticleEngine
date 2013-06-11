#pragma once

#include <cml\cml.h>
#include <Glee/GLee.h>
#include <GL/gl.h>	

#include <oogl/image.h>
#include "HudElement.h"

class ImageElement :
	public HudElement
{
public:
	ImageElement(cml::vector2f position,cml::vector2f size,cml::vector4f backgroundColor);
	~ImageElement(void);

	void setImage(std::string path);
	void draw();
private:
	GLuint textureID_;
};
