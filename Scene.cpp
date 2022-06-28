#include "Scene.h"



#include "Floor.h"
#include "vector.h"
#include "camera.h"
#include "matrix_operations.h"
#include "Sphere.h"



#include <algorithm>
#include <cmath>

#include <cstdio>
#include <cstring>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#endif


/* Defines */

#define PI          3.14159265358979323846
#define WIDTH       800         /* Screen width */
#define HEIGHT      600         /* Screen height */
#define C_WIDTH     4           /* Width of each character in pixels */
#define C_HEIGHT    8           /* Height of each character in pixels */
const char palette[] = " .:;~=#OB8%&";

using namespace std;

constexpr chrono::nanoseconds timestep(17ms);  /* Minimum Duration of each loop*/


inline 
float clamp(const float &lo, const float &hi, const float &v) 
{ return std::max(lo, std::min(hi, v)); } 

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


/* Main function */
void Scene::show(void) {
	/* ball declaration */
	Sphere balls[3];
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

	double alfa = 0;
	double beta = PI / 2;
	double r = 1.9;

	/* starting screen */
	Floor mygrid(HEIGHT,C_HEIGHT,WIDTH,C_WIDTH);
	mygrid.show_floor();


	char platno[HEIGHT / C_HEIGHT * (WIDTH / C_WIDTH + 1) + 1];

	/* time tracking variables */
	/*
	chrono::nanoseconds lag(0ns);
	chrono::system_clock::time_point time_start;
	chrono::system_clock::time_point time_end;
	*/
	double luminantie;
	while (true) {
		/* main loop start time */
		/*
		time_start = chrono::high_resolution_clock::now();
		*/

		Camera cam(r, alfa, beta);

		int p = 0;

		/*
		 * Floor
		*/
		for (int i = 0; i < HEIGHT / C_HEIGHT; i++) {
			for (int j = 0; j < WIDTH / C_WIDTH; j++) {
				Vector origin(cam.x, cam.y, cam.z);

				Vector unit(-((double)(j - WIDTH / C_WIDTH / 2) + 0.5) / (double)(WIDTH / C_WIDTH / 2),
				            ((double)(i - HEIGHT / C_HEIGHT / 2) + 0.5) / (double)(WIDTH / C_HEIGHT / 2),
				            -1);

				unit = unit.transformMatrixToVector(cam.matrix);
				unit.set(unit.getX() - cam.x, unit.getY() - cam.y, unit.getZ() - cam.z);
				/* normalize the direction */
				unit.normalize();
				
				
				/*
				 * executing raytrace here
				*/
				double altitute = 2;
				double coeff=0.3;
				int limit = 5;
				int n =3;
				
				double distanceToPlane = -(origin.getZ() + altitute) / unit.getZ(); /* this is signed distance */
				int index = -1;
				double distance;
				
				/*
				 * calculate intersect
				*/
				for (int i = 0; i < n; i++) {
					Vector diff = origin - balls[i].center;
					double discriminant = unit.dot(diff) * unit.dot(diff) + balls[i].radius * balls[i].radius - diff.dot(diff);

					if (discriminant < 0) {
						continue;
					}

					distance = -unit.dot(diff) - sqrt(discriminant);

					if (distance <= 0) {
						continue;
					}
					index = i;
					break;
				}
				if (index == -1) {
					if (unit.getZ() > 0) {
					luminantie=0;   /*  no intersection, ray hit the sky */
					} else {        /* ray hit the ground */
						
						/* point of intersection  */
						double tx = origin.getX() + distanceToPlane * unit.getX();
						double ty = origin.getY() + distanceToPlane * unit.getY();

						double color = clamp(1 / (1 + distanceToPlane / 10), 0.0, 1.0);

						Vector origin2( origin.getX() + distanceToPlane * unit.getX(),
						                origin.getY() + distanceToPlane * unit.getY(),
						                origin.getZ() + distanceToPlane * unit.getZ());

						Vector unit2(   unit.getX(),
						                unit.getY(),
						                -unit.getZ());

						if ((int)(floor(tx) + floor(ty)) % 2 == 0) {
						luminantie=	 (1 - coeff) * color + coeff * cam.rayTrace(origin2, unit2, balls, n, altitute, coeff, limit - 1);
						} else {
							luminantie= 0;
						}
					}
				}

				/*   surfacecolor should print   a chess-map like structure */
				if (unit.getZ() < 0 && distance > distanceToPlane) { /* ray hit the ground */
					double tx = origin.getX() + distanceToPlane * unit.getX();
					double ty = origin.getY() + distanceToPlane * unit.getY();
					/*  surface color */
					luminantie= (double)((int)(floor(tx) + floor(ty)) % 2);
				}

				/* ray hit a ball */
				Vector origin2( origin.getX() + unit.getX() * distance,
				                origin.getY() + unit.getY() * distance,
				                origin.getZ() + unit.getZ() * distance);

				/* normal at the intersection point */
				Vector normal = origin2 - balls[index].center;
				/* normalize normal direction */
				normal.normalize();

				/*  compute reflectiondirection */
				double k = 2 * unit.dot(normal);
				normal = normal * k;

				Vector unit2 = unit - normal;

				if (limit == 0) {
					luminantie= balls[index].get_color();
				}
				/* result of reflection and refraction*/
				 luminantie= (1 - balls[index].coeff) * balls[index].color + balls[index].coeff *
				       cam.rayTrace(origin2, unit2, balls, n, altitute, coeff, limit - 1);


				/*
				 *	Print surface color
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
		if (beta > PI / 2000) {
			beta -= 0.0003 * PI;
		}


	}

}