#pragma once

#include "GL\OOGL.hpp"
#include "HudElement.h"

class Image :
	public HudElement
{
public:
	Image(cml::vector2f position,cml::vector2f size,cml::vector4f backgroundColor);
	~Image(void);

	void setImage(std::string path);
	void draw();
private:
	std::string path_;
	GL::Image* image_;
};
