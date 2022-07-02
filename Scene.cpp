#include "Scene.h"


#include "Vec.h"
#include "camera.h"
#include "matrix_operations.h"
#include "Sphere.h"
#include "Floor.h"


#include <cstdio>
#include <cstring>
#include <chrono>
#include <thread>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif


/* Defines */

#include "Options.h"

#define PI          3.14159265358979323846
#define WIDTH       800         /* Screen width */
#define HEIGHT      600         /* Screen height */
#define C_WIDTH     4           /* Width of each character in pixels */
#define C_HEIGHT    8           /* Height of each character in pixels */
#define MAX_NUMBER_F_OBJECTS 3
const char palette[] = " .:;~=#OB8%&";

using namespace std;

constexpr chrono::nanoseconds timestep(17ms);  /* Minimum Duration of each loop*/
Sphere balls[MAX_NUMBER_F_OBJECTS];

/* Functions */

/* set cursor at start to avoid flickering (avoid clearing screen) */
void gotoxy(short x, short y) {
#ifdef _WIN32
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    printf("%c[%d;%df", 0x1B, y, x);
#endif
}




void  Scene::generateList()
{
		/* ball declaration */
	
	balls[0].center.set(0, 0, 0);
	balls[0].radius = 1;
	balls[0].color = 1;
	balls[0].coeff = 0.9;
	balls[1].center.set(-3, 0, 0);
	balls[1].radius = 0.5;
	balls[1].color = 1;
	balls[1].coeff = 0.7;
	balls[2].center.set(0, -3, 0);
	balls[2].radius = 0.5;
	balls[2].color = 1;
	balls[2].coeff = 0.7;
}


/* Main function */
void Scene::run()
{
    Options settings;
	
	generateList();
	
    
    double alfa = settings.alfa; /* alfa is camera's angle along the xy plane */
    double beta = PI / 2;  /* beta is camera's angle along z axis */
    double r = settings.r; // distance to origin, focal length

	 

    /* starting screen */
   Floor mygrid(HEIGHT,C_HEIGHT,WIDTH,C_WIDTH);
	mygrid.show_floor();
	
	/* Screen buffer */
    char platno[HEIGHT / C_HEIGHT * (WIDTH / C_WIDTH + 1) + 1];

    /* time tracking variables */
    
    while (true)
    {
        /* main loop start time */
         
        
        Camera cam(r, alfa, beta);

        int p = 0;
        for (int i = 0; i < HEIGHT / C_HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH / C_WIDTH; j++)
            {
                Vector origin(cam.x, cam.y, cam.z);

                Vector unit(-((double)(j - WIDTH / C_WIDTH / 2) + 0.5) / (double)(WIDTH / C_WIDTH / 2), // PixelCameraX
                            ((double)(i - HEIGHT / C_HEIGHT / 2) + 0.5) / (double)(WIDTH / C_HEIGHT / 2), // PixelCameraY
                            -1);
				/* express the translation and rotation values of the camera with a 4x4 matrix.*/
				/* Applying the camera-to-world transform to O and P transforms these two points from camera space to world space.  */
                unit = unit.transformMatrixToVector(cam.matrix);
                unit.set(unit.getX() - cam.x, unit.getY() - cam.y, unit.getZ() - cam.z);
                unit.normalize();

				/*
				 *	Print surface color
				*/
				
				/**
				*	TO DO
				* the value of limit here is 5 why?
				*/
                double luminance = cam.rayTrace(origin, unit, balls, 3, 2, 0.3, 5);
                int color = (int)((strlen(palette) - 1) * luminance);
                platno[p++] = palette[color];
            }
            platno[p++] = '\n';
        }
        platno[p] = 0;

        /* puts function is very fast */
        puts(platno);

        /* instead of system("cls") i used this because it looks smoother */
        gotoxy(0, 0);

        /* update camera position, using very small angle increments to get a smoother transition */
        alfa += 0.0003 * PI;
        if (beta > PI / 2000)
        {
            beta -= 0.0003 * PI;
        }

        /* elapsed time of this loop */
         
        
        /* sleeping for the remaning duration to get a constant refreh rate */
         
    }            
}