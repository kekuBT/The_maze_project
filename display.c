#include "main.h"

void display(void)
{
	/* frames per second */
	frame2 = glutGet(GLUT_ELAPSED_TIME);
	fps = (frame2 - frame1);
	frame1 = glutGet(GLUT_ELAPSED_TIME);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* init game */
	if (gameState == 0)
	{
		init();
		fade = 0;
		timer = 0;
		gameState = 1;
	}
	/* start screen */
	if (gameState == 1)
	{
		screen(1);
		timer += 1 * fps;
		if (timer > 3500)
		{
			fade = 0;
			timer = 0;
			gameState = 2;
		}
	}
	/* The main game loop */
	if (gameState == 2)
	{
		/* buttons */
		if (Keys.a == 1)
		{
			pa += 0.2 * fps;
			pa = FixAng(pa);
			pdx = cos(degToRad(pa));
			pdy = -sin(degToRad(pa));
		}
		if (Keys.d == 1)
		{
			pa -= 0.2 * fps;
			pa = FixAng(pa);
			pdx = cos(degToRad(pa));
			pdy = -sin(degToRad(pa));
		}
		/* x offset to check map */
		int xo = 0;

		if (pdx < 0)
		{
			xo = -20;
		}
		else
		{
			xo = 20;
		}
		/* y offset to check map */
		int yo = 0;

		if (pdy < 0)
		{
			yo = -20;
		}
		else
		{
			yo = 20;
		}
		/* // x position and offset  */
		int ipx = plx / 64.0, ipx_add_xo = (plx + xo) / 64.0, ipx_sub_xo = (plx - xo) / 64.0;
		/* y position and offset */
		int ipy = py / 64.0, ipy_add_yo = (py + yo) / 64.0, ipy_sub_yo = (py - yo) / 64.0;
		/* move forward */
		if (Keys.w == 1)
		{
			if (mapW[ipy * mapX + ipx_add_xo] == 0)
			{
				plx += pdx * 0.2 * fps;
			}
			if (mapW[ipy_add_yo * mapX + ipx] == 0)
			{
				py += pdy * 0.2 * fps;
			}
		}
		/* move backward */
		if (Keys.s == 1)
		{
			if (mapW[ipy * mapX + ipx_sub_xo] == 0)
			{
				plx -= pdx * 0.2 * fps;
			}
			if (mapW[ipy_sub_yo * mapX + ipx] == 0)
			{
				py -= pdy * 0.2 * fps;
			}
		}
		drawRays2D();
		drawSprite();
		/* Winning block */
		if ((int)plx >> 6 == 1 && (int)py >> 6 == 1)
		{
			fade = 0;
			timer = 0;
			gameState = 3;
		}
	}
	/* won screen */
	if (gameState == 3)
	{
		screen(2);
		timer += 1 * fps;
		if (timer > 2000)
		{
			fade = 0;
			timer = 0;
			gameState = 0;
		}
	}
	/* lost screen */
	if (gameState == 4)
	{
		screen(3);
		timer += 1 * fps;
		if (timer > 2000)
		{
			fade = 0;
			timer = 0;
			gameState = 0;
		}
	}

	glutPostRedisplay();
	glutSwapBuffers();
}
