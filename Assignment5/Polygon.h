#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

const int NUM_VERTICIES = 4;
const int NUM_POINTS = 3;

/* A 2D polygon */
class Polygon
{
public:
	static std::vector<Polygon> existingPolygons;

private:
	float verticies[NUM_VERTICIES][NUM_POINTS];
	float xMin;
	float xMax;
	float yMin;
	float yMax;
	float zMin;
	float zMax;

public:
	Polygon();
	Polygon(float points[][NUM_POINTS]);
	bool isIntersecting(float objectLocation[]);

private:
	void calculateMinAndMax();
	void compareValues(int value);
};

#endif