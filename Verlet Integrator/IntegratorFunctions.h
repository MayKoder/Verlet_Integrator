#ifndef _INTEGRATORFUNCTIONS_H_
#define _INTEGRATORFUNCTIONS_H_

#include "p2List.h"

struct Point {

	float x;
	float y;
	float old_x;
	float old_y;
	float vx;
	float vy;

};

class VerletIntegrator {
public:
	VerletIntegrator();
	void updatePoints();
	void InitPoint();



public:

	//p2List<Point> point;
	Point p;
	float bounce = 0.9f;
	float gravity = 0.6f;
	float friction = 0.3f;
};






#endif // !_INTEGRATORFUNCTIONS_H_
