#ifndef UTILS_H
#define UTILS_H

#include <glm/glm.hpp>

glm::mat4 I = glm::mat4(1.0f);

// matriz de rotação 2D
// 0 -1  0
// 1  0  0
// 0  0  1
glm::mat3 rotation2D()
{
    glm::mat3 R90 = I;
    R90[0][0] =  0.0f;
    R90[0][1] =  1.0f;
    R90[1][0] = -1.0f;
    R90[1][1] =  0.0f;
    return R90;
}

// matrix de translação 2D
// 1  0  x
// 0  1  y
// 0  0  1
glm::mat3 translation2D(float x, float y)
{
    glm::mat3 T = I;
    T[2][0] = x;
    T[2][1] = y;

    return T;
}

// matriz de escala 2D
// x  0  0
// 0  y  0
// 0  0  1
glm::mat3 scale2D(float x, float y)
{
    glm::mat3 S = I;
    S[0][0] = x;
    S[1][1] = y;

    return S;
}

#endif // UTILS_H