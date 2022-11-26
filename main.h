#ifndef MAIN_H
#define MAIN_H

#include "Textures/All_Textures.ppm"
#include "Textures/sky.ppm"
#include "Textures/title.ppm"
#include "Textures/won.ppm"
#include "Textures/lost.ppm"
#include "Textures/sprites.ppm"
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

float degToRad(float a)
float FixAng(float a)
float distance(float ax, float ay, float bx, float by, float ang)
void drawSprite(void)
void drawRays2D(void)
void screen(int v)
void init(void)
void display(void)
void ButtonUp(unsigned char key, int x, int y)
void resize(int w, int h)
int main(int argc, char *argv[])
#endif
