/*--------------------------------------*/
/* (C)GLM REPLACEMENT LIBRARY FUNCTIONS */
/*--------------------------------------*/

/* prototypes */
double glmr_sqrt(double x);
float glmr_tanf(float x);
void glmr_lookat(glmr_vec3 eye, glmr_vec3 center, glmr_vec3 up, glmr_mat4 dst);
void glmr_mat4_copy(const glmr_mat4 src, glmr_mat4 dst);
void glmr_mat4_identity(glmr_mat4 matrix); // dependency to glmr_mat4_translate
void glmr_mat4_inv(const glmr_mat4 mat, glmr_mat4 inv);
void glmr_mat4_translate(glmr_mat4 matrix, glmr_vec3 translation);
void glmr_ortho(float left, float right, float bottom, float top, float nearZ, float farZ, glmr_mat4 dst);
void glmr_perspective(float fovy, float aspect, float nearZ, float farZ, glmr_mat4 dst); // dependency to glmr_perspective
double glmr_rad(double degrees);
void glmr_vec3_add(glmr_vec3 a, glmr_vec3 b, glmr_vec3 dst);
void glmr_vec3_copy(glmr_vec3 src, glmr_vec3 dst); // dependency to glmr_mat4_inv
void glmr_vec3_cross(glmr_vec3 a, glmr_vec3 b, glmr_vec3 dst);
double glmr_vec3_norm2(glmr_vec3 vector);
void glmr_vec3_normalize(glmr_vec3 vector); // dependency to glmr_vec3_normalize
void glmr_vec3_sub(glmr_vec3 a, glmr_vec3 b, glmr_vec3 dst);

/* math helper functions */
double glmr_sqrt(double x) {
    double y = 1.0;
    double epsilon = 0.000001; // Precision level
    double x0 = x;

    while (x - y > epsilon) {
        x = (x + y) / 2;
        y = x0 / x;
    }
    return x;
}
float glmr_tanf(float x) {
    const float a = 0.3333314036f;
    const float b = 0.1333923995f;
    const float c = 0.0533740603f;
    const float d = 0.0245650893f;
    const float e = 0.0029671978f;
    const float f = 0.0002729889f;

    float x2 = x * x;
    return x * (1 + x2 * (a + x2 * (b + x2 * (c + x2 * (d + x2 * (e + x2 * f))))));
}

/* cglm replacement functions */
void glmr_lookat(glmr_vec3 eye, glmr_vec3 center, glmr_vec3 up, glmr_mat4 dst) {
    /* glm_lookat() replacement */

    glmr_vec3 f, s, u;

    glmr_vec3_sub(center, eye, f);
    glmr_vec3_normalize(f);

    glmr_vec3_cross(f, up, s);
    glmr_vec3_normalize(s);

    glmr_vec3_cross(s, f, u);

    dst[0][0] = s[0];
    dst[0][1] = u[0];
    dst[0][2] = -f[0];
    dst[0][3] = 0.0f;

    dst[1][0] = s[1];
    dst[1][1] = u[1];
    dst[1][2] = -f[1];
    dst[1][3] = 0.0f;

    dst[2][0] = s[2];
    dst[2][1] = u[2];
    dst[2][2] = -f[2];
    dst[2][3] = 0.0f;

    dst[3][0] = -(s[0] * eye[0] + s[1] * eye[1] + s[2] * eye[2]);
    dst[3][1] = -(u[0] * eye[0] + u[1] * eye[1] + u[2] * eye[2]);
    dst[3][2] = f[0] * eye[0] + f[1] * eye[1] + f[2] * eye[2];
    dst[3][3] = 1.0f;
}
void glmr_mat4_copy(const glmr_mat4 src, glmr_mat4 dst) {
    /* glm_mat4_copy() replacement */

    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            dst[i][j] = src[i][j];
        }
    }
}
void glmr_mat4_inv(const glmr_mat4 mat, glmr_mat4 inv) {
    /* glm_mat4_inv() replacement */

    float inv_out[16], det;
    int i;

    inv_out[0] = mat[1][1] * mat[2][2] * mat[3][3] -
                 mat[1][1] * mat[2][3] * mat[3][2] -
                 mat[2][1] * mat[1][2] * mat[3][3] +
                 mat[2][1] * mat[1][3] * mat[3][2] +
                 mat[3][1] * mat[1][2] * mat[2][3] -
                 mat[3][1] * mat[1][3] * mat[2][2];

    inv_out[4] = -mat[1][0] * mat[2][2] * mat[3][3] +
                 mat[1][0] * mat[2][3] * mat[3][2] +
                 mat[2][0] * mat[1][2] * mat[3][3] -
                 mat[2][0] * mat[1][3] * mat[3][2] -
                 mat[3][0] * mat[1][2] * mat[2][3] +
                 mat[3][0] * mat[1][3] * mat[2][2];

    inv_out[8] = mat[1][0] * mat[2][1] * mat[3][3] -
                 mat[1][0] * mat[2][3] * mat[3][1] -
                 mat[2][0] * mat[1][1] * mat[3][3] +
                 mat[2][0] * mat[1][3] * mat[3][1] +
                 mat[3][0] * mat[1][1] * mat[2][3] -
                 mat[3][0] * mat[1][3] * mat[2][1];

    inv_out[12] = -mat[1][0] * mat[2][1] * mat[3][2] +
                  mat[1][0] * mat[2][2] * mat[3][1] +
                  mat[2][0] * mat[1][1] * mat[3][2] -
                  mat[2][0] * mat[1][2] * mat[3][1] -
                  mat[3][0] * mat[1][1] * mat[2][2] +
                  mat[3][0] * mat[1][2] * mat[2][1];

    inv_out[1] = -mat[0][1] * mat[2][2] * mat[3][3] +
                 mat[0][1] * mat[2][3] * mat[3][2] +
                 mat[2][1] * mat[0][2] * mat[3][3] -
                 mat[2][1] * mat[0][3] * mat[3][2] -
                 mat[3][1] * mat[0][2] * mat[2][3] +
                 mat[3][1] * mat[0][3] * mat[2][2];

    inv_out[5] = mat[0][0] * mat[2][2] * mat[3][3] -
                 mat[0][0] * mat[2][3] * mat[3][2] -
                 mat[2][0] * mat[0][2] * mat[3][3] +
                 mat[2][0] * mat[0][3] * mat[3][2] +
                 mat[3][0] * mat[0][2] * mat[2][3] -
                 mat[3][0] * mat[0][3] * mat[2][2];

    inv_out[9] = -mat[0][0] * mat[2][1] * mat[3][3] +
                 mat[0][0] * mat[2][3] * mat[3][1] +
                 mat[2][0] * mat[0][1] * mat[3][3] -
                 mat[2][0] * mat[0][3] * mat[3][1] -
                 mat[3][0] * mat[0][1] * mat[2][3] +
                 mat[3][0] * mat[0][3] * mat[2][1];

    inv_out[13] = mat[0][0] * mat[2][1] * mat[3][2] -
                  mat[0][0] * mat[2][2] * mat[3][1] -
                  mat[2][0] * mat[0][1] * mat[3][2] +
                  mat[2][0] * mat[0][2] * mat[3][1] +
                  mat[3][0] * mat[0][1] * mat[2][2] -
                  mat[3][0] * mat[0][2] * mat[2][1];

    inv_out[2] = mat[0][1] * mat[1][2] * mat[3][3] -
                 mat[0][1] * mat[1][3] * mat[3][2] -
                 mat[1][1] * mat[0][2] * mat[3][3] +
                 mat[1][1] * mat[0][3] * mat[3][2] +
                 mat[3][1] * mat[0][2] * mat[1][3] -
                 mat[3][1] * mat[0][3] * mat[1][2];

    inv_out[6] = -mat[0][0] * mat[1][2] * mat[3][3] +
                 mat[0][0] * mat[1][3] * mat[3][2] +
                 mat[1][0] * mat[0][2] * mat[3][3] -
                 mat[1][0] * mat[0][3] * mat[3][2] -
                 mat[3][0] * mat[0][2] * mat[1][3] +
                 mat[3][0] * mat[0][3] * mat[1][2];

    inv_out[10] = mat[0][0] * mat[1][1] * mat[3][3] -
                  mat[0][0] * mat[1][3] * mat[3][1] -
                  mat[1][0] * mat[0][1] * mat[3][3] +
                  mat[1][0] * mat[0][3] * mat[3][1] +
                  mat[3][0] * mat[0][1] * mat[1][3] -
                  mat[3][0] * mat[0][3] * mat[1][1];

    inv_out[14] = -mat[0][0] * mat[1][1] * mat[3][2] +
                  mat[0][0] * mat[1][2] * mat[3][1] +
                  mat[1][0] * mat[0][1] * mat[3][2] -
                  mat[1][0] * mat[0][2] * mat[3][1] -
                  mat[3][0] * mat[0][1] * mat[1][2] +
                  mat[3][0] * mat[0][2] * mat[1][1];

    inv_out[3] = -mat[0][1] * mat[1][2] * mat[2][3] +
                 mat[0][1] * mat[1][3] * mat[2][2] +
                 mat[1][1] * mat[0][2] * mat[2][3] -
                 mat[1][1] * mat[0][3] * mat[2][2] -
                 mat[2][1] * mat[0][2] * mat[1][3] +
                 mat[2][1] * mat[0][3] * mat[1][2];

    inv_out[7] = mat[0][0] * mat[1][2] * mat[2][3] -
                 mat[0][0] * mat[1][3] * mat[2][2] -
                 mat[1][0] * mat[0][2] * mat[2][3] +
                 mat[1][0] * mat[0][3] * mat[2][2] +
                 mat[2][0] * mat[0][2] * mat[1][3] -
                 mat[2][0] * mat[0][3] * mat[1][2];

    inv_out[11] = -mat[0][0] * mat[1][1] * mat[2][3] +
                  mat[0][0] * mat[1][3] * mat[2][1] +
                  mat[1][0] * mat[0][1] * mat[2][3] -
                  mat[1][0] * mat[0][3] * mat[2][1] -
                  mat[2][0] * mat[0][1] * mat[1][3] +
                  mat[2][0] * mat[0][3] * mat[1][1];

    inv_out[15] = mat[0][0] * mat[1][1] * mat[2][2] -
                  mat[0][0] * mat[1][2] * mat[2][1] -
                  mat[1][0] * mat[0][1] * mat[2][2] +
                  mat[1][0] * mat[0][2] * mat[2][1] +
                  mat[2][0] * mat[0][1] * mat[1][2] -
                  mat[2][0] * mat[0][2] * mat[1][1];

    det = mat[0][0] * inv_out[0] + mat[0][1] * inv_out[4] + mat[0][2] * inv_out[8] + mat[0][3] * inv_out[12];

    if (det == 0) {
        glmr_mat4_copy(mat, inv);
        return;
    }

    det = 1.0 / det;

    for (i = 0; i < 16; i++) {
        ((float*)inv)[i] = inv_out[i] * det;
    }
}
void glmr_mat4_identity(glmr_mat4 matrix) {
    /* glm_mat4_identity() replacement */

    matrix[0][0] = 1.0f; matrix[0][1] = 0.0f; matrix[0][2] = 0.0f; matrix[0][3] = 0.0f;
    matrix[1][0] = 0.0f; matrix[1][1] = 1.0f; matrix[1][2] = 0.0f; matrix[1][3] = 0.0f;
    matrix[2][0] = 0.0f; matrix[2][1] = 0.0f; matrix[2][2] = 1.0f; matrix[2][3] = 0.0f;
    matrix[3][0] = 0.0f; matrix[3][1] = 0.0f; matrix[3][2] = 0.0f; matrix[3][3] = 1.0f;
}
void glmr_mat4_translate(glmr_mat4 matrix, glmr_vec3 translation) {
    /* glm_mat4_translate() replacement */

    glmr_mat4 identity = GLMR_MAT4_IDENTITY_INIT;
    glmr_mat4_identity(identity);

    identity[3][0] = translation[0];
    identity[3][1] = translation[1];
    identity[3][2] = translation[2];

    glmr_mat4 temp;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            temp[i][j] = matrix[i][0] * identity[0][j] +
                         matrix[i][1] * identity[1][j] +
                         matrix[i][2] * identity[2][j] +
                         matrix[i][3] * identity[3][j];
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix[i][j] = temp[i][j];
        }
    }
}
void glmr_ortho(float left, float right, float bottom, float top, float nearZ, float farZ, glmr_mat4 dst) {
    /* glm_ortho() replacement */

    float rl = 1.0f / (right - left);
    float tb = 1.0f / (top - bottom);
    float fn = 1.0f / (farZ - nearZ);

    dst[0][0] = 2.0f * rl;
    dst[0][1] = 0.0f;
    dst[0][2] = 0.0f;
    dst[0][3] = 0.0f;

    dst[1][0] = 0.0f;
    dst[1][1] = 2.0f * tb;
    dst[1][2] = 0.0f;
    dst[1][3] = 0.0f;

    dst[2][0] = 0.0f;
    dst[2][1] = 0.0f;
    dst[2][2] = -2.0f * fn;
    dst[2][3] = 0.0f;

    dst[3][0] = -(right + left) * rl;
    dst[3][1] = -(top + bottom) * tb;
    dst[3][2] = -(farZ + nearZ) * fn;
    dst[3][3] = 1.0f;
}
void glmr_perspective(float fovy, float aspect, float nearZ, float farZ, glmr_mat4 dst) {
    /* glm_perspective() replacement */

    float f = 1.0f / glmr_tanf(fovy / 2.0f);
    float nf = 1.0f / (nearZ - farZ);

    dst[0][0] = f / aspect;
    dst[0][1] = 0.0f;
    dst[0][2] = 0.0f;
    dst[0][3] = 0.0f;

    dst[1][0] = 0.0f;
    dst[1][1] = f;
    dst[1][2] = 0.0f;
    dst[1][3] = 0.0f;

    dst[2][0] = 0.0f;
    dst[2][1] = 0.0f;
    dst[2][2] = (farZ + nearZ) * nf;
    dst[2][3] = -1.0f;

    dst[3][0] = 0.0f;
    dst[3][1] = 0.0f;
    dst[3][2] = (2.0f * farZ * nearZ) * nf;
    dst[3][3] = 0.0f;
}
double glmr_rad(double degrees) {
    /* degrees to radians. glm_rad() replacement */

    return degrees * (GLMR_PI / 180.0);
}
void glmr_vec3_add(glmr_vec3 a, glmr_vec3 b, glmr_vec3 dst) {
    /* glm_vec3_add() replacement */

    dst[0] = a[0] + b[0];
    dst[1] = a[1] + b[1];
    dst[2] = a[2] + b[2];
}
void glmr_vec3_copy(glmr_vec3 src, glmr_vec3 dst) {
    /* glm_vec3_copy() replacement */
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}
void glmr_vec3_cross(glmr_vec3 a, glmr_vec3 b, glmr_vec3 dst) {
    /* glm_vec3_cross() replacement */

    dst[0] = (a[1] * b[2]) - (a[2] * b[1]);
    dst[1] = (a[2] * b[0]) - (a[0] * b[2]);
    dst[2] = (a[0] * b[1]) - (a[1] * b[0]);
}
double glmr_vec3_norm2(glmr_vec3 vector) {
    /*  calculates the squared norm (length) of a vec3. glm_vec3_norm2() replacement */

    return (vector[0] * vector[0]) + (vector[1] * vector[1]) + (vector[2] * vector[2]);
}
void glmr_vec3_normalize(glmr_vec3 vector) {
    /* glm_vec3_normalize() replacement */

    float length = glmr_sqrt((vector[0] * vector[0]) + (vector[1] * vector[1]) + (vector[2] * vector[2]));
    if (length != 0.0f) {
        vector[0] /= length;
        vector[1] /= length;
        vector[2] /= length;
    }
}
void glmr_vec3_sub(glmr_vec3 a, glmr_vec3 b, glmr_vec3 dst) {
    /* glm_vec3_sub() replacement */

    dst[0] = a[0] - b[0];
    dst[1] = a[1] - b[1];
    dst[2] = a[2] - b[2];
}
