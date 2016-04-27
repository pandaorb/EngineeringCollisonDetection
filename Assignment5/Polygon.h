#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

const int NUM_VERTICIES = 4;
const int NUM_POINTS = 3;

/* Four vertexed polygon */
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
	Polygon(float points[][NUM_POINTS]);

private:
	void calculateMinAndMax();
	void compareValues(int value);
	bool isIntersecting(float objectLocation[]);
};

#endif