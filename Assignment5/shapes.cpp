#include "stdafx.h"
#include "shapes.h"
#include <cstdlib>
#include "Polygon.h"

/*
*	Draws a square.
*/
void drawCube(int a, int b, int c, int d)
{
	GLfloat x1 = 0.0;
	GLfloat x2 = 1.0;
	GLfloat y1 = 0.0;
	GLfloat y2 = 1.0;
	GLfloat z1 = 0.0;
	GLfloat z2 = 1.0;
	float ratio = 1.0;
	tuple points = {
		{ x1, y1, z1 },
		{ x2, y1, z1 },
		{ x2, y2, z1 },
		{ x1, y2, z1 },
		{ x1, y1, x2 },
		{ x2, y1, x2 },
		{ x2, y2, x2 },
		{ x1, y2, x2 }
	};
	drawPolygon(points, ratio, a, b, c, d);

}

/*
*Abstraction of Dr.Chang's polygon function generates a four sided
* polygon based on the coordinates defined in local arrays.
* @args		points - the array of points for the polygon
*			ratio - the number to divide the size of the cube by
*			a - first index of the ordered pair to be accessed
*			b - second index of the ordered pair to be accessed
*			c - third index of the ordered pair to be accessed
*			d - fourth index of the ordered pair to be accessed
* @return void
*/
void drawPolygon(tuple points, float ratio, int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
	glNormal3f(points[a][FIRST_ELEMENT] / ratio, points[a][SECOND_ELEMENT] / ratio, points[a][THIRD_ELEMENT] / ratio);
	glVertex3f(points[a][FIRST_ELEMENT] / ratio, points[a][SECOND_ELEMENT] / ratio, points[a][THIRD_ELEMENT] / ratio);

	glNormal3f(points[b][FIRST_ELEMENT] / ratio, points[b][SECOND_ELEMENT] / ratio, points[b][THIRD_ELEMENT] / ratio);
	glVertex3f(points[b][FIRST_ELEMENT] / ratio, points[b][SECOND_ELEMENT] / ratio, points[b][THIRD_ELEMENT] / ratio);

	glNormal3f(points[c][FIRST_ELEMENT] / ratio, points[c][SECOND_ELEMENT] / ratio, points[c][THIRD_ELEMENT] / ratio);
	glVertex3f(points[c][FIRST_ELEMENT] / ratio, points[c][SECOND_ELEMENT] / ratio, points[c][THIRD_ELEMENT] / ratio);

	glNormal3f(points[d][FIRST_ELEMENT] / ratio, points[d][SECOND_ELEMENT] / ratio, points[d][THIRD_ELEMENT] / ratio);
	glVertex3f(points[d][FIRST_ELEMENT] / ratio, points[d][SECOND_ELEMENT] / ratio, points[d][THIRD_ELEMENT] / ratio);
	glEnd();

	/* Create new polygon and add to list */
	Polygon newPoly = Polygon(points);
}