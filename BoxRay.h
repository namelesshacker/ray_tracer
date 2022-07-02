#pragma once

#include "geometry.h"
#include <cstdlib>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0, 1);


class BoxRay
{
	public:
		BoxRay(const Vec3f &orig, const Vec3f &dir) : orig(orig), dir(dir)
		{
			invdir = 1 / dir;
        sign[0] = (invdir.x < 0);
        sign[1] = (invdir.y < 0);
        sign[2] = (invdir.z < 0);
		}
		~BoxRay()
		{
			
		}
		
	    Vec3f orig, dir; // ray orig and dir
    	Vec3f invdir;
   	 	int sign[3];		
};