#include "Floor.h"


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

Floor::Floor(int x, int x1, int y, int y1)
{
	x= HEIGHT, x1=C_HEIGHT, y=WIDTH,y1=C_WIDTH;
}
		
		
void Floor::show_floor()
{
	 /* starting screen */
    for (int i = 0; i < HEIGHT / C_HEIGHT - 4; i++)
    {
        for (int j = 0; j < WIDTH / C_WIDTH; j++)
        {
            putchar('.');
        }
        putchar('\n');
    }
    
}