#include "matrix4.h"

using namespace simple;

void matrix4::setToOrtho(float left, float right, float bottom, float top, float near, float far)
{
    setToIdentity();
    float x_orth = 2 / (right - left);
    float y_orth = 2 / (top - bottom);
    float z_orth = -2 / (far - near);

    float tx = -(right + left) / (right - left);
    float ty = -(top + bottom) / (top - bottom);
    float tz = -(far + near) / (far - near);

    m[0][0] = x_orth;
    m[1][0] = 0;
    m[2][0] = 0;
    m[3][0] = 0;
    m[0][1] = 0;
    m[1][1] = y_orth;
    m[2][1] = 0;
    m[3][1] = 0;
    m[0][2] = 0;
    m[1][2] = 0;
    m[2][2] = z_orth;
    m[3][2] = 0;
    m[0][3] = tx;
    m[1][3] = ty;
    m[2][3] = tz;
    m[3][3] = 1;
}
