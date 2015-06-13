// PAULO BRUNO DE SOUSA SERAFIM, 2014, Fortaleza - Ce, Brasil

#ifndef CALCPATH_H
#define CALCPATH_H

#define IMG_TYPE unsigned int
#define MAX_VALUE 99999

void calc_path_ver(unsigned int *c, IMG_TYPE *m, int W, int H);
void calc_path_hor(unsigned int *c, IMG_TYPE *m, int W, int H);

void select_path_ver(IMG_TYPE *m, unsigned int *c, int W, int H);
void select_path_hor(IMG_TYPE *m, unsigned int *c, int W, int H);


#endif // CALCPATH_H
