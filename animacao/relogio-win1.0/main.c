#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#include "point.h"
#include "shape.h"
#include "mat.h"
#include "transform.h"
#include "clock.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

Shape * little_pointer = NULL;  // segundos
Shape * middle_pointer = NULL;  // horas
Shape * big_pointer = NULL;     // minutos

unsigned int timer = 1000; // milisegundos, 10 <= times <= 1000

void display(void);
void keyboard(unsigned char key, int x, int y);
void timer_callback(int value);

void init_clock_pointers();
void draw_minutes_markings();
void draw_hours_markings();
void draw_shape(Shape * shape, float r, float g, float b);

int main(int argc, char **argv)
{
    // Glut and window setup
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // glutInitWindowPosition(100, 100);
    glutCreateWindow("Win3.0 Clock");

    // OpenGL setup
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
    double aspectRatio = (double) WINDOW_WIDTH / (double) WINDOW_HEIGHT;
    glOrtho(-1.0, 1.0, -1.0 / aspectRatio, 1.0 / aspectRatio, -1, 1);

    // Set callback functions
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(timer, timer_callback, 0);

    // Clock setup
    init_clock_pointers();

    // Main loop
    glutMainLoop();

    return 0;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    draw_minutes_markings();
    draw_hours_markings();

    draw_shape(big_pointer, 0.4f, 0.25f, 0.15f);
    draw_shape(middle_pointer, 0.4f, 0.25f, 0.85f);
    draw_shape(little_pointer, 0.8f, 0.25f, 0.15f);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'a')
    {
        timer *= 1.25;
        if (timer > 1000)
            timer = 1000;
    }
    else if (key == 'b')
    {
        timer *= 0.8;
        if (timer < 5)
            timer = 5;
    }
}

void timer_callback(int value)
{
    static Clock clock = { 0, 0, 0};

    Mat33 sec_transform = rotate(-6.0f);
    Mat33 min_transform = rotate(-6.0f);
    Mat33 hor_transform = rotate(-30.0f);

    unsigned int h = clock.h;
    unsigned int m = clock.m;
    increase_seconds(&clock);

    apply_transform(sec_transform, little_pointer);
    if (m != clock.m)
        apply_transform(min_transform, big_pointer);
    if (h != clock.h)
        apply_transform(hor_transform, middle_pointer);
    
    glutPostRedisplay();
    glutTimerFunc(timer, timer_callback, 0);
}

void init_clock_pointers()
{
    little_pointer = (Shape *) malloc(sizeof(Shape));
    little_pointer->points = (Point *) malloc(4 * sizeof(Point));
    little_pointer->points[0].x =  0.01f;
    little_pointer->points[0].y = -0.01f;
    little_pointer->points[1].x =  0.01f;
    little_pointer->points[1].y =  0.7f;
    little_pointer->points[2].x = -0.01f;
    little_pointer->points[2].y =  0.7f;
    little_pointer->points[3].x = -0.01f;
    little_pointer->points[3].y = -0.01f;
    little_pointer->count = 4;

    middle_pointer = (Shape *) malloc(sizeof(Shape));
    middle_pointer->points = (Point *) malloc(4 * sizeof(Point));
    middle_pointer->points[0].x =  0.0f;
    middle_pointer->points[0].y = -0.03f;
    middle_pointer->points[1].x =  0.03f;
    middle_pointer->points[1].y =  0.0f;
    middle_pointer->points[2].x =  0.0f;
    middle_pointer->points[2].y =  0.65f;
    middle_pointer->points[3].x = -0.03f;
    middle_pointer->points[3].y =  0.0f;
    middle_pointer->count = 4;

    big_pointer = (Shape *) malloc(sizeof(Shape));
    big_pointer->points = (Point *) malloc(4 * sizeof(Point));
    big_pointer->points[0].x =  0.0f;
    big_pointer->points[0].y = -0.05f;
    big_pointer->points[1].x =  0.05f;
    big_pointer->points[1].y =  0.0f;
    big_pointer->points[2].x =  0.0f;
    big_pointer->points[2].y =  0.8f;
    big_pointer->points[3].x = -0.05f;
    big_pointer->points[3].y =  0.0f;
    big_pointer->count = 4;
}

void draw_minutes_markings()
{
    float PI = 3.141593f;
    float delta = 2 * PI / 60;

    for (int i = 0; i < 60; i++)
    {
        float cx = ((float) cos(PI / 2 + i * delta)) * 0.9f;
        float cy = ((float) sin(PI / 2 + i * delta)) * 0.9f;

        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glVertex2f(cx + 0.01f, cy - 0.01f);
            glVertex2f(cx + 0.01f, cy + 0.01f);
            glVertex2f(cx - 0.01f, cy + 0.01f);
            glVertex2f(cx - 0.01f, cy - 0.01f);
        glEnd();
    }
}

void draw_hours_markings()
{
    float PI = 3.141593f;
    float delta = 2 * PI / 12;

    for (int i = 0; i < 12; i++)
    {
        float cx = ((float) cos(PI / 2 + i * delta)) * 0.9f;
        float cy = ((float) sin(PI / 2 + i * delta)) * 0.9f;

        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glVertex2f(cx + 0.04f, cy - 0.04f);
            glVertex2f(cx + 0.04f, cy + 0.04f);
            glVertex2f(cx - 0.04f, cy + 0.04f);
            glVertex2f(cx - 0.04f, cy - 0.04f);
        glEnd();
    }
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