#pragma once

#include "vector.h"
#include "Sphere.h"

class Ray
{
	public:
	Ray();
	Ray(double r, double alfa, double beta);
	~Ray()
	{
		
	}
	double rayTrace(Vector &origin, Vector &unit, Sphere balls[], int n, double altitute, double coeff, int limit);
	double rayTraceObject(Vector &origin, Vector &unit, Sphere balls[], int n, double altitute, double coeff, int limit);
	
	double x, y, z;
    double matrix[16], inv[16];
};