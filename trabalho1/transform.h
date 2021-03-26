#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <math.h>

#include "mat.h"
#include "shape.h"

// Matriz identidade - nenhuma transformação é feita!
// Usada para iniciar a cadeia de transformações.
Mat33 identity33();

// Retorna a matriz 3x3 responsável por fazer a translação
Mat33 translate(float tx, float ty);
// Retorna a matriz 3x3 responsável por fazer a rotação
Mat33 rotate(float degree);
// Retorna a matriz 3x3 responsável por fazer a escala
Mat33 scale(float sx, float sy);

// Aplica as transformações contidas na matriz @transform no objeto @shape
void apply_transform(Mat33 transform, Shape * shape);
// Aplica sequência de transformações escritas num arquivo no objeto @shape
void apply_trasnforms(Mat33 transform, Shape * shape, const char * path);

#endif // _TRANSFORM_H