#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <math.h>

#include "mat.h"
#include "shape.h"

Mat33 identity33();

Mat33 translate(float tx, float ty);
Mat33 rotate(float degree);
Mat33 scale(float sx, float sy);

void apply_transform(Mat33 transform, Shape * shape);
void apply_trasnforms(Mat33 transform, Shape * shape, const char * path);

#endif // _TRANSFORM_H