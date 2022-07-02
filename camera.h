#ifndef __CAMERA_H__
#define __CAMERA_H__

/* Includes */

#include "matrix_operations.h"
#include "Vec.h"
#include "Sphere.h"
#include <vector>

#include <algorithm>
#include <cmath>
#include <memory>

using namespace std;


/* Class */

class Camera
{
public:
    Camera(double r, double alfa, double beta);
    ~Camera();

    //double rayTrace(Vector &origin, Vector &unit, Ball balls[], int n, double altitute, double coeff, int limit);
	double rayTrace(Vector &origin, Vector &unit, Sphere balls[], int number_of_objects, double altitute, double coeff, int limit);
    double x, y, z;
    double matrix[16], inv[16];
};

#endif
