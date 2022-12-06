#ifndef HEADER_H
#define HEADER_H

#include "Textures/All_Textures.ppm"
#include "Textures/title.ppm"
#include "Textures/won.ppm"
#include "Textures/lost.ppm"
#include "Textures/sprites.ppm"
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

/**
 * struct - button state on off
 * @w: forwards
 * @a: look to the left
 * @d: look to the right
 * @s: backwards
 */
typedef struct
{
	int w, a, d, s;
} ButtonKeys;
ButtonKeys Keys;

/**
 * struct - All veriables per sprite
 * @type: static, key, enemy
 * @state: on off
 * @map: texture to show
 * @x: position argument
 * @y: position argument
 * @z: position argument
 */
typedef struct
{
	int type;
	int state;
	int map;
	float x, y, z;
} sprite;
sprite sp[4];

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
