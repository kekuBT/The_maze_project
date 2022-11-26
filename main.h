#ifndef MAIN_H
#define MAIN_H

#define mapX 8
/* map height */
#define mapY 8
/* map cube size */
#define mapS 64

/* Edit these 3 arrays with values 0-9 to create your own level */
/* walls */
int mapW[]= {
	2, 2, 2, 2, 2, 2, 2, 2,
	6, 0, 0, 9, 4, 0, 0, 2,
	2, 0, 0, 4, 0, 9, 0, 2,
	2, 9, 4, 9, 4, 9, 0, 2,
	2, 0, 0, 0, 0, 0, 0, 2,
	2, 0, 0, 9, 0, 9, 0, 2,
	2, 0, 0, 0, 0, 0, 0, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
};

int mapF[]= {
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 2, 2, 4, 4, 4, 4, 4,
	4, 2, 2, 2, 4, 4, 4, 4,
	4, 2, 2, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
};

int mapC[]= {
	6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6,
};

#include "Textures/All_Textures.ppm"
#include "Textures/title.ppm"
#include "Textures/won.ppm"
#include "Textures/lost.ppm"
#include "Textures/sprites.ppm"
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

float degToRad(float a);
float FixAng(float a);
float distance(float ax, float ay, float bx, float by, float ang);
void drawSprite(void);
void drawRays2D(void);
void screen(int v);
void init(void);
void display(void);
void ButtonUp(unsigned char key, int x, int y);
void resize(int w, int h);
int main(int argc, char *argv[]);
#endif
