// PAULO BRUNO DE SOUSA SERAFIM, 2014, Fortaleza - Ce, Brasil

#include "SobelOp.h"

void sobel_detection(IMG_TYPE *d, unsigned char *g, int W, int H)
{
    int h, w;

    g += W+1;
    d += W+1;

    // aplica o operador de Sobel para cada pixel
    // nao eh possivel aplicar nas bordas
    for (h = 1; h < H - 1; ++h)
    {
        for (w = 1; w < W - 1; ++w)
        {
            /*************************************************
             * Sobel Operator:
             *
             *      +-       -+            +-        -+
             *      | -1 0 +1 |            | +1 +2 +1 |
             * Gx = | -2 0 +2 | * A   Gy = |  0  0  0 | * A
             *      | -1 0 +1 |            | -1 -2 -1 |
             *      +-       -+            +-        -+
             *
             * G = sqrt(Gx^2 + Gy^2)
             *
             *************************************************/

            int gx = (*(g+W+1)) + 2*(*(g+1)) + (*(g-W+1))
                   - (*(g+W-1)) - 2*(*(g-1)) - (*(g-W-1));
            int gy = (*(g+W-1)) + 2*(*(g+W)) + (*(g+W+1))
                   - (*(g-W-1)) - 2*(*(g-W)) - (*(g-W+1));

            int sobel_grad = (int)grad(gx, gy);

            if (255 <= sobel_grad)
            {
                sobel_grad = 254;
            }

            // aplica o valor na matriz
            (*d) = sobel_grad;

            ++g;
            ++d;
        }
        ++g;
        ++g;
        ++d;
        ++d;
    }
}
