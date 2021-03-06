#include <iostream>
#include <cstdlib>

#include <Glee/GLee.h>
#include <GL/gl.h>	
#include <GL/glu.h>
#include <GL/glut.h>

#include <oogl/gl_error.h>
#include <oogl/timer.h>

#include <oogl/Model.h>

#include <InputOutputController.h>

/**
 * updates everything
 * is called every 25 ms
 * @param value gets passed from update to update
 */
void update(int value);

/**
 * renders a frame
 */
void draw();

/**
 * called when nothing else needs to be done
 * forces a redisplay
 */
void idle();

/**
 * called when the window was resized
 * @param w new window width in pixel
 * @param h new window height in pixel
 */
void reshape(int w, int h);

/**
 * initialises glut
 * @return id of the created window
 */
int setupGLUT(int argc, char** argv);

/**
 * initialises gl and everything else
 */
void init();

/**
* used for handling keyboard input
*/
void keyboardEvent(unsigned char i, int x, int y);

/**
* used fot handling mouse input
*/
void mouseEvent(int button, int state, int x, int y);


/**
* used to keep track of the moause coords
*/
void mousepos(int x, int y);


/**
 * frees all memory
 */
void cleanup();

InputOutputController* inputOutController_;


int main(int argc, char** argv) 
{
	std::cout << "ParticleEngine starts to initialise..." << std::endl;

	setupGLUT(argc, argv);

	init();

	std::cout << "ParticleEngine has started!" << std::endl;
	glutMainLoop();
	return 0;
}


void update(int value)
{

	inputOutController_->update();

	//calls the next update in 25 ms
	glutTimerFunc(25, update, 0);
}


void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	inputOutController_->draw();
	glutSwapBuffers();
}


void idle() {
	glutPostRedisplay();
}


void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ((float)w)/h,0.1f, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int setupGLUT(int argc, char** argv) 
{
	glutInit(&argc, argv);
	// glutInitContextVersion(3, 0);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1600, 900);
	glutInitWindowPosition(100, 100);

	int windowId = glutCreateWindow("ParticleEngine");

	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardEvent);
	glutMouseFunc(mouseEvent);
	glutPassiveMotionFunc(mousepos);

	glutTimerFunc(25, update, 0);


	std::cout << "GLUT is succesfully initialised." << std::endl;
	return windowId;
}


void init()
{
	atexit(cleanup);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glHint(GL_POINT_SMOOTH, GL_FASTEST);
	glHint(GL_LINE_SMOOTH, GL_FASTEST);
	glHint(GL_POLYGON_SMOOTH, GL_FASTEST);
	
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glShadeModel(GL_SMOOTH);

	inputOutController_ = new InputOutputController();

	std::cout << "Everything else is succesfully initialised." << std::endl;
}


void keyboardEvent(unsigned char i, int x, int y)
{
	inputOutController_->keyboard(i,x,y);
}


void mouseEvent(int button, int state, int x, int y)
{
	inputOutController_->mouseClick(button,state,x,y);
}


void mousepos(int x, int y){
	inputOutController_->mousePos(x,y);
}


void cleanup()
{
	delete inputOutController_;
	std::cout << "Everything is cleaned up. Have a nice day!" << std::endl;
}