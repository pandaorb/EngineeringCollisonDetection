#include "stdafx.h"
#include "shapes.h"
#include "eagle.h"

void drawEagle(void)
{
	glColor3f(139.0 / 256.0, 69.0 / 256.0, 19.0 / 256.0);
	//glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(2.0, -5.0, -5.5);
	glScalef(0.5, 0.5, 0.5);
	drawCube(0, 3, 2, 1);
	drawCube(2, 3, 7, 6);
	drawCube(0, 4, 7, 3);
	drawCube(1, 2, 6, 5);
	drawCube(4, 5, 6, 7);
	drawCube(0, 1, 5, 4);
	glPopMatrix();
}