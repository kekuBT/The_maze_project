#include "main.h"

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
float px, py, pdx, pdy, pa;
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

/*-----------------------------MAP----------------------------------------------*/
/* map width */
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

void resize(int w, int h)
{
	/* screen window rescaled, snap back */
	glutReshapeWindow(960, 640);
}
