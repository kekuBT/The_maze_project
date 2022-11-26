#include "header.h"

void init(void)
{
	/* init all variables when game starts */
	glClearColor(0.3, 0.3, 0.3, 0);
	plx = 150;
	py = 400;
	pa = 90;
	pdx = cos(degToRad(pa));
	pdy = -sin(degToRad(pa));
	/* close doors */
	mapW[19] = 4;
	mapW[26] = 4
	/* Key*/
	sp[0].type = 1;
	sp[0].state = 1;
	sp[0].map = 0;
	sp[0].x = 6.0 * 64;
	sp[0].y = 1.5 * 64;
	sp[0].z = 20;
	/* light 1 */
	sp[1].type = 2;
	sp[1].state = 1;
	sp[1].map = 1;
	sp[1].x = 1.5 * 64;
	sp[1].y = 4.5 * 64;
	sp[1].z = 0;
	/* light 2 */
	sp[2].type = 2;
	sp[2].state = 1;
	sp[2].map = 1;
	sp[2].x = 3.5 * 64;
	sp[2].y = 4.5 * 64;
	sp[2].z = 0;
	/* enemy */
	sp[3].type = 3;
	sp[3].state = 1;
	sp[3].map = 2;
	sp[3].x = 1.5 * 64;
	sp[3].y = 2 * 64;
	sp[3].z = 20;
}
