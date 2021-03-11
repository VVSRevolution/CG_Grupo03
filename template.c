#include <GL/glut.h>
#include <stdlib.h>

void display(void);

int main(int argc, char **argv)
{
	// Glut and window setup
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 480);
    // glutInitWindowPosition(100, 100);
    glutCreateWindow("Window Name");

    // OpenGL setup
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
    glOrtho(-1, 1, -1, 1, -1, 1);

    // Set callback functions
    glutDisplayFunc(display);

    // Main loop
    glutMainLoop();

    return 0;
}

void display(void)
{
	int i, j;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(255.0, 255.0, 0.0);

	glBegin(GL_POLYGON);
	{
		glVertex2f(0.6, 0.5);
		glVertex2f(0.25, 0.25);
		glVertex2f(0.7, 0.3);
		glVertex2f(0.7, 0.7);
		glVertex2f(0.25, 0.75);
	}
	glEnd();

	glFlush();
}