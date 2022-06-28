 #ifndef __BALL_H__
#define __BALL_H__

/* Includes */

#include "vector.h"
#include "Object.h"

/* Defines */

class Sphere : public Object
{
	public:
		Sphere()
		{
			
		}
    	Vector center;
    	double radius;
    	double color;   /* Interval between 0 (dark) to 1 (light) */
    	double coeff;   /* Interval between 0 and 1 how much the ball reflect light (1 means it's the perfect mirror) */
    	
    	Vector get_center();
    	double get_radius();
    	double get_color();
    	double get_coeff();
};

#endif