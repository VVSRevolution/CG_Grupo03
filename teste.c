/* programa teste.c */
#include <GL/glut.h>
#include <stdlib.h>
void display(void);
void keyboard(unsigned char key, int x, int
y);
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (256, 256);
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
	glOrtho (0, 1, 0, 1, -1 ,1);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
} 
void display(void){
int i,j;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (255.0, 255.0, 0.0); 
    
    glBegin(GL_POLYGON);
    glVertex2f(0.6,0.5);
    glVertex2f(0.25,0.25);
    glVertex2f(0.7,0.3);
    glVertex2f(0.7,0.7);
    glVertex2f(0.25,0.75);
    

    glEnd();
    glFlush();
}

