#include "Textures/All_Textures.ppm"
#include "Textures/title.ppm"
#include "Textures/won.ppm"
#include "Textures/lost.ppm"
#include "Textures/sprites.ppm"
#include "header.h"

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
