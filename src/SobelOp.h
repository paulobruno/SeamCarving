// PAULO BRUNO DE SOUSA SERAFIM, 2014, Fortaleza - Ce, Brasil

#ifndef SOBELOP_H
#define SOBELOP_H

#include <math.h>

#define IMG_TYPE unsigned int

inline double grad(int gx, int gy)
{
    return sqrt(gx*gx + gy*gy);
}

void sobel_detection(IMG_TYPE *d, unsigned char *g, int W, int H);

#endif // SOBELOP_H
