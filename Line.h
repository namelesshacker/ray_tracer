#pragma once
#include "Vec.h"
class Line
{
	public:
		Line()
		{
			
		}
		
		Vector direction;
		
		void draw(float x1, float y1, float x2, float y2)
		{
			float dx = x2 -x1;
			float dy = y2 -y1;
			
			float length = std::sqrt(dx * dx + dy * dy);
			float angle = std::atan2(dy,dx);
			
			float(float i=0; i< length; i++)
			{
			//	writePixe(x1+ std::cos(angle) *i, y1+std::sin(angle)*i));
			}
		}
		
		void show()
		{
		//	line.draw(0,0,300,300);
		}
};
