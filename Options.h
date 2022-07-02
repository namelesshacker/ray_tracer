#pragma once

#include "Vec.h"

#define PI          3.14159265358979323846
//#define WIDTH       800         /* Screen width */
//#define HEIGHT      600         /* Screen height */
//#define C_WIDTH     4           /* Width of each character in pixels */
//#define C_HEIGHT    8           /* Height of each character in pixels */


class Options
{
	public:
		Options()
		{
			
		}
		
		void set();
		Options get();
		
		//float M_PI = 3.14159265358979323846;
		uint32_t WIDTH=800; 
    	uint32_t HEIGHT=600;
    	uint32_t C_WIDTH=4; 
		uint32_t C_HEIGHT=8;  
    	float fov; 
    	float imageAspectRatio; 
    	uint8_t maxDepth; 
    	Vector backgroundColor; 
    	float bias; 
    
     	double alfa = 0;
    	double beta = PI / 2;
    	double r = 1.9;
};


/*

struct Options 
{ 
    
}; 
 
 */