#include <cstdlib>
#include <iostream>

#include <GL/glut.h>


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
 * frees all memory
 */
void cleanup();


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


	//calls the next update in 25 ms
	glutTimerFunc(25, update, 0);
}


void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//test
	glPushMatrix();
		glTranslated(0.0, 0.0, -10.0);
		glutSolidTeapot(1.0);
	glPopMatrix();

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
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);

	int windowId = glutCreateWindow("ParticleEngine");

	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);

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
	glEnable(GL_LIGHT0);

	std::cout << "Everything else is succesfully initialised." << std::endl;
}


void cleanup()
{
	std::cout << "Everything is cleaned up. Have a nice day!" << std::endl;
}


//TBD:
/*


*/