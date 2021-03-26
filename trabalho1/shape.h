#ifndef _SHAPE_H
#define _SHAPE_H

#include "point.h"

// Struct para representar uma forma geométrica através de
// um array de pontos no plano
struct _shape
{
    Point * points;
    int count;
};

typedef struct _shape Shape;

// Carrega um forma a partir de um arquivo
Shape * load_shape(const char * path);
void free_shape(Shape * shape);


#endif // _SHAPE_H