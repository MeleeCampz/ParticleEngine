#include "..\include\Image.h"


Image::Image(cml::vector2f position,cml::vector2f size,cml::vector4f backgroundColor):
	HudElement(size)
{
	position_=position;
	backgroundColor_=backgroundColor;
	path_="assets/";
}


Image::~Image(void)
{
}

void Image::setImage(std::string path)
{
	path_.append(path);
	GL::Image image( path_);
	image_ = new GL::Texture(image);

}
void Image::draw()
{
	windowSize_=cml::vector2i(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));

	glBindTexture( (*image_), 0 );

	glTexCoord2d(position_[0],position_[1]); 
		glVertex2d(position_[0],position_[1]);
		glTexCoord2d((position_[0]+size_[0])*windowSize_[0],position_[1]); 
		glVertex2d((position_[0]+size_[0])*windowSize_[0],position_[1]);
		glTexCoord2d((position_[0]+size_[0])*windowSize_[0],(position_[1]+size_[1])*windowSize_[1]); 
		glVertex2d((position_[0]+size_[0])*windowSize_[0],(position_[1]+size_[1])*windowSize_[1]);
		glTexCoord2d(position_[0],(position_[1]+size_[1])*windowSize_[1]); 
		glVertex2d(position_[0],(position_[1]+size_[1])*windowSize_[1]);
	glEnd();
}
