#pragma once

#include "Vec.h"
class Light
{
	public:
		Light()
		{
			
		}
		
		Light(Vector position)
		{
			
		}
		
		 Light(const Vector &p, const Vector &i) : position(p), intensity(i) {} 
    Vector position; 
    Vector intensity; 
		
		void on();
		void off();
};