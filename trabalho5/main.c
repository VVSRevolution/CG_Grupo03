#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define WINDOW_WIDTH 600.0
#define WINDOW_HEIGHT 480.0

// Struct que representa um ponto no espaço
struct _point
{
    float x, y, z;
};
typedef struct _point Point;

// Matriz 4x4
struct _mat44
{
    float values[16];
};
typedef struct _mat44 Mat44;

// Matriz 4x1
struct _mat41
{
    float values[4];
};
typedef struct _mat41 Mat41;

Point cubeModel[24] = {
    // face +Z (sentido anti-horário)
    { -0.5, -0.5f,  0.5f },
    {  0.5, -0.5f,  0.5f },
    {  0.5,  0.5f,  0.5f },
    { -0.5,  0.5f,  0.5f },

    // face -Z (sentido anti-horário)
    { -0.5, -0.5f, -0.5f },
    { -0.5,  0.5f, -0.5f },
    {  0.5,  0.5f, -0.5f },
    {  0.5, -0.5f, -0.5f },

    // face +X (sentido anti-horário)
    {  0.5, -0.5f,  0.5f },
    {  0.5, -0.5f, -0.5f },
    {  0.5,  0.5f, -0.5f },
    {  0.5,  0.5f,  0.5f },

    // face -X (sentido anti-horário)
    { -0.5, -0.5f,  0.5f },
    { -0.5,  0.5f,  0.5f },
    { -0.5,  0.5f, -0.5f },
    { -0.5, -0.5f, -0.5f },

    // face +Y (sentido anti-horário)
    {  0.5,  0.5f,  0.5f },
    {  0.5,  0.5f, -0.5f },
    { -0.5,  0.5f, -0.5f },
    { -0.5,  0.5f,  0.5f },

    // face -Y (sentido anti-horário)
    {  0.5, -0.5f,  0.5f },
    { -0.5, -0.5f,  0.5f },
    { -0.5, -0.5f, -0.5f },
    {  0.5, -0.5f, -0.5f }
};

Point cube[24];

float cores[6][3] = {
    { 0.85f, 0.15f, 0.25f },
    { 0.45f, 0.55f, 0.25f },
    { 0.15f, 0.85f, 0.25f },
    { 0.15f, 0.45f, 0.55f },
    { 0.15f, 0.15f, 0.85f },
    { 0.65f, 0.15f, 0.55f }
};

// Retorna a * b
Mat44 mul44(Mat44 a, Mat44 b)
{
    Mat44 r;

    // i -> linha
    for (int i = 0; i < 4; i++)
    {
        // j -> coluna
        for (int j = 0; j < 4; j++)
        {
            // calcula r na linha i e coluna j
            // (produto interno da linha i de a com a coluna j de b)
            float c = 0;
            for (int k = 0; k < 4; k++)
            {
                c += a.values[i * 4 + k] * b.values[k * 4 + j];
            }
            r.values[i * 4 + j] = c;
        }
    }

    return r;
}

Mat41 mul41(Mat44 a, Mat41 b)
{
    Mat41 r;

    // i -> linha
    for (int i = 0; i < 4; i++)
    {
        // j -> coluna
        for (int j = 0; j < 1; j++)
        {
            // calcula r na linha i e coluna j
            // (produto interno da linha i de a com a coluna j de b)
            float c = 0;
            for (int k = 0; k < 4; k++)
            {
                c += a.values[i * 4 + k] * b.values[k * 1 + j];
            }
            r.values[i * 1 + j] = c;
        }
    }

    return r;
}

void show_mat44(Mat44 a)
{
    printf("%.2lf %.2lf %.2lf %.2lf\n", a.values[0], a.values[1], a.values[2], a.values[3]);
    printf("%.2lf %.2lf %.2lf %.2lf\n", a.values[4], a.values[5], a.values[6], a.values[7]);
    printf("%.2lf %.2lf %.2lf %.2lf\n", a.values[8], a.values[9], a.values[10], a.values[11]);
    printf("%.2lf %.2lf %.2lf %.2lf\n", a.values[12], a.values[13], a.values[14], a.values[15]);
}

void show_mat41(Mat41 a)
{
    printf("%.2lf\n", a.values[0]);
    printf("%.2lf\n", a.values[1]);
    printf("%.2lf\n", a.values[2]);
    printf("%.2lf\n", a.values[3]);
}

// Transformações
Mat44 rotate_x(float degrees)
{
    Mat44 r;
    float rad = degrees * (3.141593 / 180.0f);

    // 1o linha
    r.values[0] = 1.0f;
    r.values[1] = 0.0f;
    r.values[2] = 0.0f;
    r.values[3] = 0.0f;

    // 2o linha
    r.values[4] = 0.0f;
    r.values[5] = (float) cos(rad);
    r.values[6] = -(float) sin(rad);
    r.values[7] = 0.0f;

    // 3o linha
    r.values[8] = 0.0f;
    r.values[9] = (float) sin(rad);
    r.values[10] = (float) cos(rad);
    r.values[11] = 0.0f;

    //4o linha
    r.values[12] = 0.0f;
    r.values[13] = 0.0f;
    r.values[14] = 0.0f;
    r.values[15] = 1.0f;

    return r;
}

Mat44 rotate_y(float degrees)
{
    Mat44 r;
    float rad = degrees * (3.141593 / 180.0f);

    // 1o linha
    r.values[0] = (float) cos(rad);
    r.values[1] = 0.0f;
    r.values[2] = -(float) sin(rad);
    r.values[3] = 0.0f;

    // 2o linha
    r.values[4] = 0.0f;
    r.values[5] = 1.0f;
    r.values[6] = 0.0f;
    r.values[7] = 0.0f;

    // 3o linha
    r.values[8] = (float) sin(rad);
    r.values[9] = 0.0f;
    r.values[10] = (float) cos(rad);
    r.values[11] = 0.0f;

    //4o linha
    r.values[12] = 0.0f;
    r.values[13] = 0.0f;
    r.values[14] = 0.0f;
    r.values[15] = 1.0f;

    return r;
}

Mat44 translate(float x, float y, float z)
{
    Mat44 r;

    // 1o linha
    r.values[0] = 1.0f;
    r.values[1] = 0.0f;
    r.values[2] = 0.0f;
    r.values[3] = x;

    // 2o linha
    r.values[4] = 0.0f;
    r.values[5] = 1.0f;
    r.values[6] = 0.0f;
    r.values[7] = y;

    // 3o linha
    r.values[8] = 0.0f;
    r.values[9] = 0.0f;
    r.values[10] = 1.0f;
    r.values[11] = z;

    //4o linha
    r.values[12] = 0.0f;
    r.values[13] = 0.0f;
    r.values[14] = 0.0f;
    r.values[15] = 1.0f;

    return r;
}

// Projeções
Mat44 perspective_projection(float fov, float aspectRatio, float n, float f)
{
    Mat44 p;

    // 1o linha
    p.values[0] = 1.0f / (aspectRatio * tanf(fov / 2));
    p.values[1] = 0.0f;
    p.values[2] = 0.0f;
    p.values[3] = 0.0f;

    // 2o linha
    p.values[4] = 0.0f;
    p.values[5] = 1.0f / (tanf(fov / 2));
    p.values[6] = 0.0f;
    p.values[7] = 0.0f;

    // 3o linha
    p.values[8] = 0.0f;
    p.values[9] = 0.0f;
    p.values[10] = -(f + n) / (f - n);
    p.values[11] = -2*f*n / (f - n);

    // 4o linha
    p.values[12] = 0.0f;
    p.values[13] = 0.0f;
    p.values[14] = -1.0f;
    p.values[15] = 0.0f;

    return p;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);
    {
        for (int i = 0; i < 24; i++)
        {
            if (i % 4 == 0)
                glColor3f(cores[i/4][0], cores[i/4][1], cores[i/4][2]);
            glVertex3f(cube[i].x, cube[i].y, cube[i].z);
        }
    }
    glEnd();

    glFlush();
}

float randf()
{
    return (float) rand() / RAND_MAX;
}

void timer_callback(int value)
{
    static float rx = 0;
    static float ry = 0;

    rx += randf() * 0.25;
    ry += randf() * 0.15;

    Mat44 transform = rotate_x(rx);
    transform = mul44(transform, rotate_y(ry));
    transform = mul44(translate(0, 0, -2.5f), transform);

    double aspectRatio = (double) WINDOW_WIDTH / (double) WINDOW_HEIGHT;
    Mat44 projection = perspective_projection(45, aspectRatio, 0.1, -1000.0f);
    
    Mat44 modelViewProjection = mul44(projection, transform);  // view = identity
    for (int i = 0; i < 24; i++)
    {
        Mat41 p = { cubeModel[i].x, cubeModel[i].y, cubeModel[i].z, 1.0f };
        p = mul41(modelViewProjection, p);
        cube[i].x = p.values[0]  / p.values[3];
        cube[i].y = p.values[1]  / p.values[3];
        cube[i].z = p.values[2]  / p.values[3];
    }
    
    glutPostRedisplay();
    glutTimerFunc(5, timer_callback, 0);
}

int main(int argc, char **argv)
{
	// Glut and window setup
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // glutInitWindowPosition(100, 100);
    glutCreateWindow("Projecao Perspectiva");

    // OpenGL setup
    glClearColor(0.1f, 0.05f, 0.15f, 1.0f);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    // Set callback functions
    glutDisplayFunc(display);
    glutTimerFunc(5, timer_callback, 0);

    // Main loop
    glutMainLoop();

    return 0;
}