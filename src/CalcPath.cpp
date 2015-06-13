// PAULO BRUNO DE SOUSA SERAFIM, 2014, Fortaleza - Ce, Brasil

#include "CalcPath.h"

void calc_path_ver(unsigned int *c, IMG_TYPE *m, int W, int H)
{
    for (int w = 0; w < W; ++w)
    {
        (*c) = (*m);
        ++c;
        ++m;
    }

    for (int h = 1; h < H; ++h)
    {
        // lateral esquerda
        if ((*(c-W)) > (*(c-W+1)))
        {
            (*c) = (*m) + (*(c-W+1));
        }
        else
        {
            (*c) = (*m) + (*(c-W));
        }
        ++c;
        ++m;

        // parte interna
        for (int w = 1; w < W - 1; ++w)
        {
            if ((*(c-W-1)) > (*(c-W)))   // relaxamento
            {
                if ((*(c-W)) > (*(c-W+1)))
                {
                    (*c) = (*m) + (*(c-W+1));
                }
                else
                {
                    (*c) = (*m) + (*(c-W));
                }
            }
            else
            {
                if ((*(c-W-1)) > (*(c-W+1)))
                {
                    (*c) = (*m) + (*(c-W+1));
                }
                else
                {
                    (*c) = (*m) + (*(c-W-1));
                }
            }
            ++c;
            ++m;
        }

        // lateral direita
        if ((*(c-W-1)) > (*(c-W)))
        {
            (*c) = (*m) + (*(c-W));
        }
        else
        {
            (*c) = (*m) + (*(c-W-1));
        }
        ++c;
        ++m;
    }
}

void calc_path_hor(unsigned int *c, IMG_TYPE *m, int W, int H)
{
    for (int h = 0; h < H; ++h)
    {
        (*c) = (*m);
        c += W;
        m += W;
    }
    c = c - H*W + 1;
    m = m - H*W + 1;

    for (int w = 1; w < W; ++w)
    {
        // topo
        if ((*(c-1)) > (*(c+W-1)))
        {
            (*c) = (*m) + (*(c+W-1));
        }
        else
        {
            (*c) = (*m) + (*(c-1));
        }
        c += W;
        m += W;

        // parte interna
        for (int h = 1; h < H - 1; ++h)
        {
            if ((*(c-W-1)) > (*(c-1)))   // relaxamento
            {
                if ((*(c-1)) > (*(c+W-1)))
                {
                    (*c) = (*m) + (*(c+W-1));
                }
                else
                {
                    (*c) = (*m) + (*(c-1));
                }
            }
            else
            {
                if ((*(c-W-1)) > (*(c+W-1)))
                {
                    (*c) = (*m) + (*(c+W-1));
                }
                else
                {
                    (*c) = (*m) + (*(c-W-1));
                }
            }
            c += W;
            m += W;
        }

        // inferior
        if ((*(c-W-1)) > (*(c-1)))
        {
            (*c) = (*m) + (*(c-1));
        }
        else
        {
            (*c) = (*m) + (*(c-W-1));
        }

        c = c + W - H*W + 1;
        m = m + W - H*W + 1;
    }
}

void select_path_ver(IMG_TYPE *m, unsigned int *c, int W, int H)
{
    c += (H-1)*W;   //ultima linha
    m += (H-1)*W;

    int min = 0;

    for (int w = 1; w < W; ++w)
    {
        if ( (*(c+min)) > (*(c+w)) )
        {
            min = w;
        }
    }

    // marcar celula minima
    (*(m+min)) = MAX_VALUE;

    // coluna minima
    c += min;

    for (int h = H - 1; h > 0; --h)
    {
        m -= W;
        c -= W;

        // lateral esquerda
        if (0 == min)
        {
            if ((*c) > (*(c+1)))
            {
                ++min;
                ++c;
            }
        }
        // lateral direita
        else if (W-1 == min)
        {
            if ((*c) > (*(c-1)))
            {
                --min;
                --c;
            }
        }
        // interno
        else
        {
            if ((*(c-1)) > (*c))   // relaxamento
            {
                if ((*c) > (*(c+1)))
                {
                    ++min;
                    ++c;
                }
            }
            else
            {
                if ((*(c-1)) > (*(c+1)))
                {
                    ++min;
                    ++c;
                }
                else
                {
                    --min;
                    --c;
                }
            }
        }

        // aplica o valor flag na linha minima
        (*(m+min)) = MAX_VALUE;
    }
}

void select_path_hor(IMG_TYPE *m, unsigned int *c, int W, int H)
{
    // ultima coluna
    c = c + W - 1;
    m = m + W - 1;

    int min = 0;

    for (int h = 1; h < H; ++h)
    {
        if ( (*(c+min*W)) > (*(c+h*W)) )
        {
            min = h;
        }
    }

    // marcar celula minima
    (*(m + min*W)) = MAX_VALUE;

    //linha minima
    c += min*W;

    for (int w = W - 1; w > 0; --w)
    {
        --c;
        --m;

        // superior
        if (0 == min)
        {
            if ((*c) > (*(c+W)))
            {
                ++min;
                c += W;
            }
        }
        // inferior
        else if (H-1 == min)
        {
            if ((*c) > (*(c-W)))
            {
                --min;
                c -= W;
            }
        }
        // interno
        else
        {
            if ((*(c-W)) > (*c))   // relaxamento
            {
                if ((*c) > (*(c+W)))
                {
                    ++min;
                    c += W;
                }
            }
            else
            {
                if ((*(c-W)) > (*(c+W)))
                {
                    ++min;
                    c += W;
                }
                else
                {
                    --min;
                    c -= W;
                }
            }
        }

        // aplica o valor flag na coluna minima
        (*(m + min*W)) = MAX_VALUE;
    }
}
