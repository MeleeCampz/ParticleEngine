#include "..\include\ImageElement.h"


ImageElement::ImageElement(cml::vector2f position,cml::vector2f size,cml::vector4f backgroundColor):
	HudElement(size)
{
	position_=position;
	backgroundColor_=backgroundColor;
}


ImageElement::~ImageElement(void)
{
	glDeleteTextures(1,&textureID_);
}

void ImageElement::setImage(std::string path)
{
	oogl::Image* image = oogl::loadImage(path);
	
	glEnable(GL_TEXTURE_2D);
	
	glGenTextures(1, &textureID_);

	glBindTexture(GL_TEXTURE_2D, textureID_);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		image->getWidth(),
		image->getHeight(),
		0,
		image->getFormat(),
		image->getType(),
		image->getData());

	glBindTexture(GL_TEXTURE_2D, 0);

}
void ImageElement::draw()
{
	//HudElement::draw();
	windowSize_=cml::vector2i(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
	//windowSize_ = cml::vector2i(1600, 900);
	
	glBindTexture(GL_TEXTURE_2D, textureID_);
	
	glColor3d(1,1,1);
	glBegin(GL_QUADS);	
		glTexCoord2d(0,1);
		glVertex2d(position_[0]*windowSize_[0],position_[1]*windowSize_[1]);

		glTexCoord2d(1,1); 
		glVertex2d((position_[0]+size_[0])*windowSize_[0],position_[1]*windowSize_[1]);
		
		glTexCoord2d(1,0); 
		glVertex2d((position_[0]+size_[0])*windowSize_[0],(position_[1]+size_[1])*windowSize_[1]);
		
		glTexCoord2d(0,0); 
		glVertex2d(position_[0]*windowSize_[0],(position_[1]+size_[1])*windowSize_[1]);
	glEnd();

	//"unbind" durty way to get rid of texture without deleting it
	glBindTexture(GL_TEXTURE_2D,0);

}
