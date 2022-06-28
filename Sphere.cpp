#include "Sphere.h"



Vector Sphere::get_center()
{
	return center;
}

double Sphere::get_radius()
{
	return radius;
}

/* Interval between 0 (dark) to 1 (light) */
double Sphere::get_color()
{
	return color;
}

/* Interval between 0 and 1 how much the ball reflect light (1 means it's the perfect mirror) */
double Sphere::get_coeff()
{
	return coeff;
}
