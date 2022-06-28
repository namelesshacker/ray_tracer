#ifndef __CAMERA_H__
#define __CAMERA_H__

/* Includes */

#include "matrix_operations.h"
#include "vector.h"
#include "Sphere.h"

#include <algorithm>
#include <cmath>


/* Class */

class Camera
{
public:
    Camera(double r, double alfa, double beta);
    ~Camera();

    double rayTrace(Vector &origin, Vector &unit, Sphere balls[], int n, double altitute, double coeff, int limit);

    double x, y, z;
    double matrix[16], inv[16];
};

#endif