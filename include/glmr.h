/*----------------------------------------*/
/* (C)GLM REPLACEMENT LIBRARY DEFINITIONS */
/*----------------------------------------*/

typedef float glmr_vec2[2];
typedef float glmr_vec3[3];
typedef float glmr_mat4[4][4];

#define GLMR_MAT4_IDENTITY_INIT {{1.0f, 0.0f, 0.0f, 0.0f}, \
                                {0.0f, 1.0f, 0.0f, 0.0f}, \
                                {0.0f, 0.0f, 1.0f, 0.0f}, \
                                {0.0f, 0.0f, 0.0f, 1.0f}}

#define GLMR_PI 3.14159265358979323846

/* include function library */
#include "glmr.c"
