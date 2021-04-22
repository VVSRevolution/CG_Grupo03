#include "mat.h"

#include <stdio.h>

Mat33 mul33(Mat33 a, Mat33 b)
{
    Mat33 r;

    // 1st row
    r.values[0] = a.values[0] * b.values[0 + 0] + a.values[1] * b.values[3 + 0] + a.values[2] * b.values[6 + 0];
    r.values[1] = a.values[0] * b.values[0 + 1] + a.values[1] * b.values[3 + 1] + a.values[2] * b.values[6 + 1];
    r.values[2] = a.values[0] * b.values[0 + 2] + a.values[1] * b.values[3 + 2] + a.values[2] * b.values[6 + 2];

    // 2nd row
    r.values[3] = a.values[3] * b.values[0 + 0] + a.values[4] * b.values[3 + 0] + a.values[5] * b.values[6 + 0];
    r.values[4] = a.values[3] * b.values[0 + 1] + a.values[4] * b.values[3 + 1] + a.values[5] * b.values[6 + 1];
    r.values[5] = a.values[3] * b.values[0 + 2] + a.values[4] * b.values[3 + 2] + a.values[5] * b.values[6 + 2];

    // 3rd row
    r.values[6] = a.values[6] * b.values[0 + 0] + a.values[7] * b.values[3 + 0] + a.values[8] * b.values[6 + 0];
    r.values[7] = a.values[6] * b.values[0 + 1] + a.values[7] * b.values[3 + 1] + a.values[8] * b.values[6 + 1];
    r.values[8] = a.values[6] * b.values[0 + 2] + a.values[7] * b.values[3 + 2] + a.values[8] * b.values[6 + 2];

    return r;
}

Mat31 mul31(Mat33 a, Mat31 b)
{
    Mat31 r;

    // 1st row
    r.values[0] = a.values[0] * b.values[0] + a.values[1] * b.values[1] + a.values[2] * b.values[2];

    // 2nd row
    r.values[1] = a.values[3] * b.values[0] + a.values[4] * b.values[1] + a.values[5] * b.values[2];

    // 3rd row
    r.values[2] = a.values[6] * b.values[0] + a.values[7] * b.values[1] + a.values[8] * b.values[2];

    return r;
}

void show_mat33(Mat33 a)
{
    printf("%.2lf %.2lf %.2lf\n", a.values[0], a.values[1], a.values[2]);
    printf("%.2lf %.2lf %.2lf\n", a.values[3], a.values[4], a.values[5]);
    printf("%.2lf %.2lf %.2lf\n", a.values[6], a.values[7], a.values[8]);
}

void show_mat31(Mat33 a)
{
    printf("%.2lf\n", a.values[0]);
    printf("%.2lf\n", a.values[1]);
    printf("%.2lf\n", a.values[2]);
}