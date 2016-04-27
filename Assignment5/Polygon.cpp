#include <float.h>
#include <cfloat>

#include <limits>
#include "stdafx.h"
#include "Polygon.h"
#include <vector>

std::vector<Polygon> Polygon::existingPolygons = std::vector<Polygon>();

/* Fancy Constructor */
Polygon::Polygon(void)
{
	// Default constructor
}

Polygon::Polygon(float points[][3])
{
	for (int i = 0; i < NUM_VERTICIES; i++)
	{
		for (int j = 0; j < NUM_POINTS; j++)
		{
			verticies[i][j] = points[i][j];
		}
	}
	calculateMinAndMax();
	existingPolygons.push_back(*this);
}

/* sets min and max for x, y, and z verticies */
void Polygon::calculateMinAndMax(void)
{
	// set smallest and largest x value
	compareValues(0);
	// set smallest and largest y value
	compareValues(1);
	// set smallest and largest z value
	compareValues(2);
}

/*
 * @param value		0	compare x values
 *					1	compare y values
 *					2	compare z values
 */
void Polygon::compareValues(int value)
{
	//VS doesn't want to get max and min floats for some reason, these are arbitrary.
	float min = 5000.0;
	float max = -5000.0;
	for (int index = 0; index < NUM_VERTICIES; index++)
	{
		min = (min > verticies[index][value]) ? verticies[index][value] : min;
		max = (max < verticies[index][value]) ? verticies[index][value] : max;
	}

	switch (value)
	{
		case 0:
			xMin = min;
			xMax = max;
			break;
		case 1:
			yMin = min;
			yMax = max;
			break;
		case 2:
			zMin = min;
			zMax = max;
			break;
		default:
			break;
	}

}

bool Polygon::isIntersecting(float objectLocation[])
{
	if (objectLocation[0] >= xMin && objectLocation[0] < xMax)
		if (objectLocation[1] >= yMin && objectLocation[1] < yMax)
			if (objectLocation[2] >= zMin && objectLocation[2] < zMax)
		return true;
	return false;
}