#include "header.h"


/**
 * degToRad - converts degree to radian
 * @a: is an argument
 * Return: returns result
 */
float degToRad(float a)
{
	return (a * M_PI / 180.0);
}

/**
 * FixAng - Fixes the angles
 * @a: is an argument
 * Return: returns result
 */
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

/**
 * distance - calculates the distances
 * @ax: is an argument
 * @ay: is an argument
 * @bx: is an argument
 * @by: is an argument
 * @ang: is an argument
 * Return: returns result
 */
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

/* Map width */
#define mapX 8
/* Map height */
#define mapY 8
/* Map cube size */
#define mapS 64

/* Edit these 3 arrays with values 0-9 to create your own level */

/* walls */
int mapW[] = {
	2, 2, 2, 2, 2, 2, 2, 2,
	6, 0, 0, 9, 4, 0, 0, 2,
	2, 0, 0, 4, 0, 9, 0, 2,
	2, 9, 4, 9, 4, 9, 0, 2,
	2, 0, 0, 0, 0, 0, 0, 2,
	2, 0, 0, 9, 0, 9, 0, 2,
	2, 0, 0, 0, 0, 0, 0, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
};

/* Floor */
int mapF[] = {
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 2, 2, 4, 4, 4, 4, 4,
	4, 2, 2, 2, 4, 4, 4, 4,
	4, 2, 2, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
};

/* Ceiling */
int mapC[] = {
	6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6,
};

/* hold wall line depth to compare for sprite depth */
int depth[120];

/**
 * drawSprite - drawing enemies and keys
 * Return: void
 */
void drawSprite(void)
{
	/* pick up key */
	int x, y, s;

	if (px < sp[0].x + 30 && px > sp[0].x - 30 && py < sp[0].y + 30 && py > sp[0].y - 30)
	{
		sp[0].state = 0;
	}

	/* enemy kills */
	if (px < sp[3].x + 30 && px > sp[3].x - 30 && py < sp[3].y + 30 && py > sp[3].y - 30)
	{
		gameState = 4;
	}

	/* enemy attack */

	/* normal grid position */
	int spx = (int)sp[3].x >> 6, spy = (int)sp[3].y >> 6;
	/* normal grid position plus offset */
	int spx_add = ((int)sp[3].x + 15) >> 6, spy_add = ((int)sp[3].y + 15) >> 6;
	/* normal grid position subtract offset */
	int spx_sub = ((int)sp[3].x - 15) >> 6, spy_sub = ((int)sp[3].y - 15) >> 6;

	if (sp[3].x > px && mapW[spy * 8 + spx_sub] == 0)
	{
		sp[3].x -= 0.04 * fps;
	}
	if (sp[3].x < px && mapW[spy * 8 + spx_add] == 0)
	{
		sp[3].x += 0.05 * fps;
	}
	if (sp[3].y > py && mapW[spy_sub * 8 + spx] == 0)
	{
		sp[3].y -= 0.05 * fps;
	}
	if (sp[3].y < py && mapW[spy_add * 8 + spx] == 0)
	{
		sp[3].y += 0.05 * fps;
	}

	for (s = 0; s < 4; s++)
	{
		/* temp float variables */
		float sx = sp[s].x - px;
		float sy = sp[s].y - py;
		float sz = sp[s].z;

		/* rotate around origin */
		float CS = cos(degToRad(pa)), SN = sin(degToRad(pa));
		float a = sy * CS + sx * SN;
		float b = sx * CS - sy * SN;

		sx = a;
		sy = b;

		/* convert to screen x,y */
		sx = (sx * 108.0 / sy) + (120 / 2);
		sy = (sz * 108.0 / sy) + (80 / 2);

		/* scale sprite based on distance */
		int scale = 32 * 80 / b;

		if (scale < 0)
		{
			scale = 0;
		}
		if (scale > 120)
		{
			scale = 120;
		}

		/* texture */
		float t_x = 0, t_y = 31, t_x_step = 31.5 / (float)scale, t_y_step = 32.0 / (float)scale;

		for (x = sx - scale / 2; x < sx + scale / 2; x++)
		{
			t_y = 31;
			for (y = 0; y < scale; y++)
			{
				if (sp[s].state == 1 && x > 0 && x < 120 && b < depth[x])
				{
					int pixel = ((int)t_y * 32 + (int)t_x) * 3 + (sp[s].map * 32 * 32 * 3);
					int red = sprites[pixel + 0];
					int green = sprites[pixel + 1];
					int blue = sprites[pixel + 2];

					/* dont draw if purple */
					if (red != 255, green != 0, blue != 255)
					{
						glPointSize(8);
						glColor3ub(red, green, blue);
						glBegin(GL_POINTS);
						glVertex2i(x * 8, sy * 8 - y * 8);
						glEnd();
					}
					t_y -= t_y_step;
					if (t_y < 0)
					{
						t_y = 0;
					}
				}
			}
			t_x += t_x_step;
		}
	}
}

/**
 * drawRays2D - drawing raycasting rays
 * Return: void
 */
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

		/* looking left */
		if (cos(degToRad(ra)) > 0.001)
		{
			rx = (((int)px >> 6) << 6) + 64;
			ry = (px - rx) * Tan + py;
			xo = 64;
			yo = -xo * Tan;
		}
		/* looking right */
		else if (cos(degToRad(ra)) < -0.001)
		{
			rx = (((int)px >> 6) << 6) - 0.0001;
			ry = (px - rx) * Tan + py;
			xo = -64;
			yo = -xo * Tan;
		}

		/* looking up or down. no hit */
		else
		{
			rx = px;
			ry = py;
			dof = 8;
		}

		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * mapX + mx;

			/* hit */
			if (mp > 0 && mp < mapX * mapY && mapW[mp] > 0)
			{
				vmt = mapW[mp] - 1;
				dof = 8;
				disV = cos(degToRad(ra)) * (rx - px) - sin(degToRad(ra)) * (ry - py);
			}

			/* check next horizontal*/
			else
			{
				rx += xo;
				ry += yo;
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
			rx = (py - ry) * Tan + px;
			yo = -64;
			xo = -yo * Tan;
		}

		/* looking down */
		else if (sin(degToRad(ra)) < -0.001)
		{
			ry = (((int)py >> 6) << 6) + 64;
			rx = (py - ry) * Tan + px;
			yo = 64;
			xo = -yo * Tan;
		}

		/* looking straight left or right */
		else
		{
			rx = px;
			ry = py;
			dof = 8;
		}

		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * mapX + mx;

			/* hit*/
			if (mp > 0 && mp < mapX * mapY && mapW[mp] > 0)
			{
				hmt = mapW[mp] - 1;
				dof = 8;
				disH = cos(degToRad(ra)) * (rx - px) - sin(degToRad(ra)) * (ry - py);
			}

			/* check next horizontal */
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}

		float shade = 1;

		glColor3f(0, 0.8, 0);

		/* horizontal hit first */
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

			tx = px / 2 + cos(deg) * 158 * 2 * 32 / dy / raFix;
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

/**
 * screen - draw any fullscreen image 120*80 pixels
 * @v: is an argument
 */draw any full screen image. 120x80 pixels */
void screen(int v)
{
	int x, y;
	int *T;

	if (v == 1)
	{
		T = title;
	}
	if (v == 2)
	{
		T = won;
	}
	if (v == 3)
	{
		T = lost;
	}
	for (y = 0; y < 80; y++)
	{
		for (x = 0; x < 120; x++)
		{
			int pixel = (y * 120 + x) * 3;
			int red = T[pixel + 0] * fade;
			int green = T[pixel + 1] * fade;
			int blue = T[pixel + 2] * fade;

			glPointSize(8);
			glColor3ub(red, green, blue);
			glBegin(GL_POINTS);
			glVertex2i(x * 8, y * 8);
			glEnd();
		}
	}
	if (fade < 1)
	{
		fade += 0.001 * fps;
	}
	if (fade > 1)
	{
		fade = 1;
	}
}


/**
 * init - initialize all variables when the game start
 */
void init(void)
{
	glClearColor(0.3, 0.3, 0.3, 0);
	px = 150;
	py = 400;
	pa = 90;

	/* init player */
	pdx = cos(degToRad(pa));
	pdy = -sin(degToRad(pa));

	/* close doors */
	mapW[19] = 4;
	mapW[26] = 4;

	/* Key*/
	sp[0].type = 1;
	sp[0].state = 1;
	sp[0].map = 0;
	sp[0].x = 1.5 * 64;
	sp[0].y = 5 * 64;
	sp[0].z = 20;

	/* enemy */
	sp[3].type = 3;
	sp[3].state = 1;
	sp[3].map = 2;
	sp[3].x = 2.5 * 64;
	sp[3].y = 2 * 64;
	sp[3].z = 20;
}

/**
 * display - displays all functions
 */
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
		if (timer > 2000)
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

		/* x position and offset  */
		int ipx = px / 64.0, ipx_add_xo = (px + xo) / 64.0, ipx_sub_xo = (px - xo) / 64.0;
		/* y position and offset */
		int ipy = py / 64.0, ipy_add_yo = (py + yo) / 64.0, ipy_sub_yo = (py - yo) / 64.0;

		/* move forward */
		if (Keys.w == 1)
		{
			if (mapW[ipy * mapX + ipx_add_xo] == 0)
			{
				px += pdx * 0.2 * fps;
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
				px -= pdx * 0.2 * fps;
			}
			if (mapW[ipy_sub_yo * mapX + ipx] == 0)
			{
				py -= pdy * 0.2 * fps;
			}
		}
		drawRays2D();
		drawSprite();

		/* Winning block */
		if ((int)px >> 6 == 1 && (int)py >> 6 == 1)
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

/**
 * ButtonDown - Keyboard button pressed down
 * @key: is an argument
 * @x: is an argument
 * @y: is an argument
 * Return: returns result
 */
void ButtonDown(unsigned char key, int x, int y)
{
	if (key == 'a')
	{
		Keys.a = 1;
	}
	if (key == 'd')
	{
		Keys.d = 1;
	}
	if (key == 'w')
	{
		Keys.w = 1;
	}
	if (key == 's')
	{
		Keys.s = 1;
	}

	/* open doors */
	if (key == 'o' && sp[0].state == 0)
	{
		int xo = 0;

		if (pdx < 0)
		{
			xo = -25;
		}
		else
		{
			xo = 25;
		}
		int yo = 0;

		if (pdy < 0)
		{
			yo = -25;
		}
		else
		{
			yo = 25;
		}
		int ipx = px / 64.0, ipx_add_xo = (px + xo) / 64.0;
		int ipy = py / 64.0, ipy_add_yo = (py + yo) / 64.0;

		if (mapW[ipy_add_yo * mapX + ipx_add_xo] == 4)
		{
			mapW[ipy_add_yo * mapX + ipx_add_xo] = 0;
		}
	}

	glutPostRedisplay();
}

/**
 * ButtonUp - Keyboard button pressed up
 * @key: is an argument
 * @x: is an argument
 * @y: is an argument
 * Return: returns result
 */
void ButtonUp(unsigned char key, int x, int y)
{
	if (key == 'a')
	{
		Keys.a = 0;
	}
	if (key == 'd')
	{
		Keys.d = 0;
	}
	if (key == 'w')
	{
		Keys.w = 0;
	}
	if (key == 's')
	{
		Keys.s = 0;
	}
	glutPostRedisplay();
}

/**
 * resize - screen window rescaled, snap back
 * @w: is an argument
 * @h: is an argument
 */
void resize(int w, int h)
{
	glutReshapeWindow(960, 640);
}

/**
 * main - openGl glut displays
 * @argc: is an argument
 * @argv: is an argument
 * Return: the display of all function
 */
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(960, 640);
	glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - 960 / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2 - 640 / 2);
	glutCreateWindow("The Maze project");
	gluOrtho2D(0, 960, 640, 0);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(ButtonDown);
	glutKeyboardUpFunc(ButtonUp);
	glutMainLoop();
}
