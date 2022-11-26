#include "header.h"

void drawRays2D(void)
{
	int r, mx, my, mp, dof, side;
	float vx, vy, rx, ry, ra, xo, yo, disV, disH;

	/* ray set back 30 degrees */
	ra = FixAng(pa + 30);

	for (r = 0; r < 120; r++)
	{
		/* vertical and horizontal map texture number */
		int vmt = 0, hmt = 0;
		/* Vertical */
		dof = 0;
		side = 0;
		disV = 100000;
		float Tan = tan(degToRad(ra));

		if (cos(degToRad(ra)) > 0.001)
		{
			rx = (((int)plx >> 6) << 6) + 64;
			ry = (plx - rx) * Tan + py;
			xo = 64;
			yo = -xo * Tan;
		}
		/* looking left */
		else if (cos(degToRad(ra)) < -0.001)
		{
			rx = (((int)plx >> 6) << 6) - 0.0001;
			ry = (plx - rx) * Tan + py;
			xo = -64;
			yo = -xo * Tan;
		}
		/* looking right */
		else
		{
			rx = plx;
			ry = py;
			dof = 8;
		}
		/* / looking up or down. no hit */
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && mapW[mp] > 0)
			{
				vmt = mapW[mp] - 1;
				dof = 8;
				disV = cos(degToRad(ra)) * (rx - plx) - sin(degToRad(ra)) * (ry - py);
			}
			/* hit */
			else
			{
				rx += xo;
				ry += yo;
				/* check next horizontal*/
				dof += 1;
			}

		}
		vx = rx;
		vy = ry;

		/* Horizontal */
		dof = 0;
		disH = 100000;
		Tan = 1.0 / Tan;
		/* looking up */
		if (sin(degToRad(ra)) > 0.001)
		{
			ry = (((int)py >> 6) << 6) - 0.0001;
			rx = (py - ry) * Tan + plx;
			yo = -64;
			xo = -yo * Tan;
		}
		/* looking down */
		else if (sin(degToRad(ra)) < -0.001)
		{
			ry = (((int)py >> 6) << 6) + 64;
			rx = (py - ry) * Tan + plx;
			yo = 64;
			xo = -yo * Tan;
		}
		else
		/* looking straight left or right */
		{
			rx = plx;
			ry = py;
			dof = 8;
		}

		while (dof < 8)
		{
			/* hit*/
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && mapW[mp] > 0)
			{
				hmt = mapW[mp] - 1;
				dof = 8;
				disH = cos(degToRad(ra)) * (rx - plx) - sin(degToRad(ra)) * (ry - py);
			}
			else
			/* check next horizontal */
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		/* horizontal hit first */
		float shade = 1;

		glColor3f(0, 0.8, 0);
		if (disV < disH)
		{
			hmt = vmt;
			shade = 0.5;
			rx = vx;
			ry = vy;
			disH = disV;
			glColor3f(0, 0.6, 0);
		}

		int ca = FixAng(pa - ra);
		/* fix fisheye */
		disH = disH * cos(degToRad(ca));
		int lineH = (mapS * 640) / (disH);
		float ty_step = 32.0 / (float)lineH;
		float ty_off = 0;
		/* line height and limit */
		if (lineH > 640)
		{
			ty_off = (lineH - 640) / 2.0;
			lineH = 640;
		}
		/* line offset */
		int lineOff = 320 - (lineH >> 1);
		/* save this line's depth */
		depth[r] = disH;
		/* draw walls */
		int y;
		/* +hmt*32; */
		float ty = ty_off * ty_step;
		float tx;

		if (shade == 1)
		{
			tx = (int)(rx / 2.0) % 32;
			if (ra > 180)
			{
				tx = 31 - tx;
			}
		}
		else
		{
			tx = (int)(ry / 2.0) % 32;
			if (ra > 90 && ra < 270)
			{
				tx = 31 - tx;
			}
		}
		for (y = 0; y < lineH; y++)
		{
			int pixel = ((int)ty * 32 + (int)tx) * 3 + (hmt * 32 * 32 * 3);
			int red = All_Textures[pixel + 0] * shade;
			int green = All_Textures[pixel + 1] * shade;
			int blue = All_Textures[pixel + 2] * shade;

			glPointSize(8);
			glColor3ub(red, green, blue);
			glBegin(GL_POINTS);
			glVertex2i(r * 8, y + lineOff);
			glEnd();
			ty += ty_step;
		}

		/* draw floors */
		for (y = lineOff + lineH; y < 640; y++)
		{
			float dy = y - (640 / 2.0), deg = degToRad(ra), raFix = cos(degToRad(FixAng(pa - ra)));

			tx = plx / 2 + cos(deg) * 158 * 2 * 32 / dy / raFix;
			ty = py / 2 - sin(deg) * 158 * 2 * 32 / dy / raFix;
			int mp = mapF[(int)(ty / 32.0) * mapX + (int)(tx / 32.0)] * 32 * 32;
			int pixel = (((int)(ty) & 31) * 32 + ((int)(tx) & 31)) * 3 + mp * 3;
			int red = All_Textures[pixel + 0] * 0.7;
			int green = All_Textures[pixel + 1] * 0.7;
			int blue = All_Textures[pixel + 2] * 0.7;

			glPointSize(8);
			glColor3ub(red, green, blue);
			glBegin(GL_POINTS);
			glVertex2i(r * 8, y);
			glEnd();

			/* draw ceiling */
			mp = mapC[(int)(ty / 32.0) * mapX + (int)(tx / 32.0)] * 32 * 32;
			pixel = (((int)(ty) & 31) * 32 + ((int)(tx) & 31)) * 3 + mp * 3;
			red = All_Textures[pixel + 0];
			green = All_Textures[pixel + 1];
			blue = All_Textures[pixel + 2];
			if (mp > 0)
			{
				glPointSize(8);
				glColor3ub(red, green, blue);
				glBegin(GL_POINTS);
				glVertex2i(r * 8, 640 - y);
				glEnd();
			}
		}

		/* go to next ray, 60 total */
		ra = FixAng(ra - 0.5);
	}
}
