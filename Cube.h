#pragma once

#include "Surface.h"
#include "Shape.h"
#include "Object.h"
#include <vector>




class Cube  : public Shape , public Object
{
	public:
		Cube()
		{
			
		}
		
		void translate();
		void rotate();
		void bindtexture();
		
		std::vector<Surface> faces;
		
		void front_face();
		void backface();
		void top_face();
		void bottom_face();
		void right_face();
		void left_face();
		
		void addvertices(std::vector<Surface> points);
		
		void show();

};

void Cube::addvertices(	std::vector<Surface> points)
{
	points.emplace_back(Vector(1,2,3));
}

	


