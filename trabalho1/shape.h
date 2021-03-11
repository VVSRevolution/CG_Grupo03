#ifndef _SHAPE_H
#define _SHAPE_H

#include "point.h"

struct _shape
{
    Point * points;
    int count;
};

typedef struct _shape Shape;

Shape * load_shape(const char * path);
void free_shape(Shape * shape);


#endif // _SHAPE_H