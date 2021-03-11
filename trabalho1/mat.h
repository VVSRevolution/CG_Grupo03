#ifndef _MAT_H
#define _MAT_H

struct _mat33
{
    float values[9];
};

typedef struct _mat33 Mat33;

struct _mat31
{
    float values[3];
};

typedef struct _mat31 Mat31;

// return a * b
Mat33 mul33(Mat33 a, Mat33 b);
Mat31 mul31(Mat33 a, Mat31 b);

void show_mat33(Mat33 a);
void show_mat31(Mat33 a);

#endif // _MAT_H