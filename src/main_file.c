#include "header.h"

float degToRad(float a)
{
	return (a * M_PI / 180.0);
}
float FixAng(float a)
{
	if (a > 359)
	{
		a -= 360;
	}
	if (a < 0)
	{
		a += 360;
	}
	return (a);
}
float distance(float ax, float ay, float bx, float by, float ang)
{
	return (cos(degToRad(ang)) * (bx - ax) - sin(degToRad(ang)) * (by - ay));
}
float plx, py, pdx, pdy, pa;
float frame1, frame2, fps;
/* game state. init, start screen, game loop, win/lose */
int gameState = 0, timer = 0;
/* the 3 screens can fade up from black */
float fade = 0;

typedef struct
/* button state on off */
{
	int w, a, d, s;
} ButtonKeys;
ButtonKeys Keys;

/* All veriables per sprite */
typedef struct
{
	/* static, key, enemy */
	int type;
	/* on off */
	int state;
	/* texture to show */
	int map;
	/* position */
	float x, y, z;
} sprite;
sprite sp[4];
/* hold wall line depth to compare for sprite depth */
int depth[120];
