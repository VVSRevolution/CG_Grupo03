#include "shape.h"

#include <stdio.h>
#include <stdlib.h>

Shape * load_shape(const char * path)
{
    Shape * shape = (Shape *) malloc(sizeof(Shape));

    if (shape)
    {
        FILE *arq = fopen(path, "r");

        fscanf(arq, "%d", &shape->count);
        shape->points = (Point *) malloc(sizeof(Point) * shape->count);
        for (int i = 0; i < shape->count; i++)
        {
            float x, y;
            fscanf(arq, "%f %f", &x, &y);
            shape->points[i].x = x;
            shape->points[i].y = y;
        }

        fclose(arq);
    }

    return shape;
}

void free_shape(Shape * shape)
{
    if (shape)
    {
        shape->count = 0;
        free(shape->points);
        free(shape);
    }
}