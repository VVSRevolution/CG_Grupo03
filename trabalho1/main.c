#include <GL/glut.h>
#include <stdlib.h>

#include "point.h"
#include "shape.h"
#include "mat.h"
#include "transform.h"

#define WINDOW_WIDTH 853.333
#define WINDOW_HEIGHT 480.0

Shape * shape = NULL;

void display(void);
void keyboard(unsigned char key, int x, int y);

void draw_axis();
void draw_grid();
void draw_shape(Shape * shape, float r, float g, float b);

int main(int argc, char **argv)
{
    // Glut and window setup
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // glutInitWindowPosition(100, 100);
    glutCreateWindow("Template");

    // OpenGL setup
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
    double aspectRatio = (double) WINDOW_WIDTH / (double) WINDOW_HEIGHT;
    // Left = -10, Right = 10, Bottom = -1, Top = 1, Near = -1, Far = 1
    glOrtho(-10.0, 10.0, -10.0 / aspectRatio, 10.0 / aspectRatio, -1, 1);

    // Set callback functions
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    // Shape setup
    shape = load_shape("shape");
    apply_trasnforms(identity33(), shape, "transformations");

    // Main loop
    glutMainLoop();

    free_shape(shape);

    return 0;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    draw_grid();
    draw_axis();

    draw_shape(shape, 0.8f, 0.25f, 0.15f);

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == ' ')
    {
        free_shape(shape);
        shape = load_shape("shape");
        apply_trasnforms(identity33(), shape, "transformations");
    }

    // Call the display function
    glutPostRedisplay();
}

void draw_axis()
{
    glColor3f(0.2f, 0.15f, 0.2f);
    glBegin(GL_LINES);
    {
        //  x
        glVertex2f(100.0f, 0.0f);
        glVertex2f(-100.0f, 0.0f);

        // y
        glVertex2f(0.0f, 100.0f);
        glVertex2f(0.0f, -100.0f);
    }
    glEnd();
}

void draw_grid()
{
    float x, y;

    glColor3f(0.9f, 0.85f, 0.9f);
    glBegin(GL_LINES);
    {
        for (x = -9.0f; x < 10.0f; x += 1.0f)
        {
            if (x == 0.0f) continue;

            glVertex2f(x, 100.0f);
            glVertex2f(x, -100.0f);
        }

        for (y = -9.0f; y < 10.0f; y += 1.0f)
        {
            if (y == 0.0f) continue;

            glVertex2f(100.0f, y);
            glVertex2f(-100.0f, y);
        }
    }
    glEnd();
}

void draw_shape(Shape * shape, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    {
        for (int i = 0; i < shape->count; i++)
        {
            glVertex2f(shape->points[i].x, shape->points[i].y);
        }
    }
    glEnd();
}