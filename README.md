# glmr

**-- ABOUT --**

glmr  - or "glimmer" (OpenGL Mathematics Replacement) - is a (fairly) modular subset replacement to some cglm functions


The aim is to allow for certain (graphical) mathematic calculations without the need to include the complete library; you can lift out and use only the functions you require for your project.


I am trying to avoid internal dependencies when possible, so in any future updates, helper code may be duplicated inside functions that depend on them.


**-- HELPERS --**


    glmr_sqrt()  
    glmr_tanf()


**-- DROP-IN REPLACEMENTS --**


    glmr_lookat()
    glmr_mat4_copy()
    glmr_mat4_identity()
    glmr_mat4_inv()
    glmr_mat4_translate()
    glmr_ortho()
    glmr_perspective()
    glmr_rad()
    glmr_vec3_add()
    glmr_vec3_copy()
    glmr_vec3_cross()
    glmr_vec3_norm2()
    glmr_vec3_normalize)
    glmr_vec3_sub()


To avoid potential conflicts with other includes, the following type definitions are recommended to use with glmr:


    typedef float glmr_vec2[2];
    typedef float glmr_vec3[3];
    typedef float glmr_mat4[4][4];

    #define GLMR_MAT4_IDENTITY_INIT {{1.0f, 0.0f, 0.0f, 0.0f}, \
                                    {0.0f, 1.0f, 0.0f, 0.0f}, \
                                    {0.0f, 0.0f, 1.0f, 0.0f}, \
                                    {0.0f, 0.0f, 0.0f, 1.0f}}

    #define GLMR_PI 3.14159265358979323846


**-- ARE THESE FEATURE COMPLETE? --**


glmr is far from complete, and include only the functions I currently use with my projects. It is not meant to be a replacement to the cglm library. The included functions may or may not be optimized or full featured.

As the scope is focused on size optimization over efficiency, I strongly recommend you to do your own benchmark tests to compare cglm with glmr


**-- CGLM --**


Check out cglm here: https://github.com/recp/cglm


**-- LICENCE --**


This project is released under the MIT license. If you are a demo scener and choose to use any of this code in your productions, additional conditions apply as follows: Greetings to dMG and diViNE sTYLERs, UP ROUGH, and TiTAN in your production! :D


Toodiloo!

