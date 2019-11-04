#ifndef _INTEGRATORFUNCTIONS_H_
#define _INTEGRATORFUNCTIONS_H_

#include "p2List.h"
#include"IntegratorFunctions.h"

struct Circle;
class VerletIntegrator 
{
public:
	VerletIntegrator();

	void InitPoint(Circle* p);
	void updatePoints(Circle* p);


public:

	//p2List<Point> point;
	float bounce = 0.9f;
	float gravity = 0.6f;
	float friction = 0.3f;

	int floor_Limit_Y = SCREEN_HEIGHT - 10;
	int floor_Limit_X = SCREEN_WIDTH-10;

};

#endif // !_INTEGRATORFUNCTIONS_H_
