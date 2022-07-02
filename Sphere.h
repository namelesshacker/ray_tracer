#ifndef __BALL_H__
#define __BALL_H__

/* Includes */

#include "Vec.h"
#include "Object.h"

/* Defines */

class Sphere : public Object
{
	public:
		Sphere()
		{
			
		}
		Sphere(Vector _center ,double _radius,double _color,double _coef)
		{
			center =_center;
			radius =_radius;
			color = _color;
			coeff = _coef;
		}
    Vector center;
    double radius;
    double color;   /* Interval between 0 (dark) to 1 (light) */
    double coeff;   /* Interval between 0 and 1 how much the ball reflect light (1 means it's the perfect mirror) */
    void set_center(Vector centre)
    {
    	center= centre;
	}
	Vector get_center()
    {
    	return center;
	}
    void set_radius(double rad)
    {
    	radius = rad;
	}
	double get_radius()
    {
    	return radius;
	}
    void set_color(double col)
    {
    	color = col;
	}
	double get_color()
    {
    	return color;
	}
    void set_coeff(double cff)
    {
    	coeff = cff;
	}
	double get_coeff()
    {
    	return coeff;
	}
    
};

#endif
