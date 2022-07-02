#pragma once

//#include "Cube.h"
#include <memory>
#include "Light.h"
#include "Options.h"

class Scene
{
	public:
		Scene()
		{
			
    			

		}
		/*
		Scene(const std::vector<std::unique_ptr<Object>> &objects,const std::vector<std::unique_ptr<Light>> &lights,const Options &options)
		{
			
		}
		*/
		
		void run();
		
		void generateList();
		
		void importScene();
	
	void exportScene();
};

extern Scene sceneObject;