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
	image_=new GL::Image( path_);

}
void Image::draw()
{
	windowSize_=cml::vector2i(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));

	glEnable(GL_TEXTURE_2D);
	
	GLuint textureID;
	glGenTextures(1, &textureID);


	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, image_->GetWidth(), image_->GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, image_->GetPixels());

	
	glColor3d(1,1,1);
	glBegin(GL_QUADS);	
		glTexCoord2d(0,0); 
		glVertex2d(position_[0]*windowSize_[0],position_[1]*windowSize_[1]);
		glTexCoord2d(1,0); 
		glVertex2d((position_[0]+size_[0])*windowSize_[0],position_[1]*windowSize_[1]);
		glTexCoord2d(1,1); 
		glVertex2d((position_[0]+size_[0])*windowSize_[0],(position_[1]+size_[1])*windowSize_[1]);
		glTexCoord2d(0,1); 
		glVertex2d(position_[0]*windowSize_[0],(position_[1]+size_[1])*windowSize_[1]);
	glEnd();

}
