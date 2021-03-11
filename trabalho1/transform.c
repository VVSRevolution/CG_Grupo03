#include "transform.h"

#include <stdio.h>

Mat33 identity33()
{
    Mat33 i;

    // 1st row
    i.values[0] = 1;
    i.values[1] = 0;
    i.values[2] = 0;

    // 2nd row
    i.values[3] = 0;
    i.values[4] = 1;
    i.values[5] = 0;

    // 3rd row
    i.values[6] = 0;
    i.values[7] = 0;
    i.values[8] = 1;

    return i;
}

Mat33 translate(float tx, float ty)
{
    Mat33 t;

    // 1st row
    t.values[0] = 1;
    t.values[1] = 0;
    t.values[2] = tx;

    // 2nd row
    t.values[3] = 0;
    t.values[4] = 1;
    t.values[5] = ty;

    // 3rd row
    t.values[6] = 0;
    t.values[7] = 0;
    t.values[8] = 1;

    return t;
}

Mat33 rotate(float degree)
{
    Mat33 r;
    float rad = degree * (3.141593 / 180.0f);

    // 1st row
    r.values[0] = (float) cos(rad);
    r.values[1] = -(float) sin(rad);
    r.values[2] = 0;

    // 2nd row
    r.values[3] = (float) sin(rad);
    r.values[4] = (float) cos(rad);
    r.values[5] = 0;

    // 3rd row
    r.values[6] = 0;
    r.values[7] = 0;
    r.values[8] = 1;

    return r;
}

Mat33 scale(float sx, float sy)
{
    Mat33 s;

    // 1st row
    s.values[0] = sx;
    s.values[1] = 0;
    s.values[2] = 0;

    // 2nd row
    s.values[3] = 0;
    s.values[4] = sy;
    s.values[5] = 0;

    // 3rd row
    s.values[6] = 0;
    s.values[7] = 0;
    s.values[8] = 1;

    return s;
}

void apply_transform(Mat33 transform, Shape * shape)
{
    for (int i = 0; i < shape->count; i++)
    {
        Mat31 p;
        p.values[0] = shape->points[i].x;
        p.values[1] = shape->points[i].y;
        p.values[2] = 1;

        p = mul31(transform, p);

        shape->points[i].x = p.values[0];
        shape->points[i].y = p.values[1];
    }
}

void apply_trasnforms(Mat33 transform, Shape * shape, const char * path)
{
    FILE * arq = fopen(path, "r");
    char buffer[128];
    char type;
    float a, b;

    while(fscanf(arq, "%[^\n]%*c", buffer) != EOF)
    {
        sscanf(buffer, "%c", &type);

        if (type == 'T')
        {
            sscanf(buffer + 1, "%f %f", &a, &b);
            transform = mul33(translate(a, b), transform);
        } 
        else if (type == 'R')
        {
            sscanf(buffer + 1, "%f", &a);
            transform = mul33(rotate(a), transform);
        }
        else if (type == 'S')
        {
            sscanf(buffer + 1, "%f %f", &a, &b);
            transform = mul33(scale(a, b), transform);
        }
    }

    apply_transform(transform, shape);

    fclose(arq);
}