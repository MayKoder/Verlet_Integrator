#ifndef _INTEGRATORFUNCTIONS_H_
#define _INTEGRATORFUNCTIONS_H_

#include "p2List.h"
#include"IntegratorFunctions.h"
#include"Shape.h"
#include"Application.h"

struct Point;
class Line;
class Application;
class VerletIntegrator 
{
public:
	VerletIntegrator();
	VerletIntegrator(Application* app);

	void InitPoint(Point* p, vector2 pos);
	void updatePoints(Point* p);
	//void OnCollision();
	Application* App;


public:

	//p2List<Point> point;
	float bounce = 0.9f;
	//float gravity = 9.81f;
	float gravity = 500.f;
	float friction = 0.3f;

	int floor_Limit_Y = SCREEN_HEIGHT - 10;
	int floor_Limit_X = SCREEN_WIDTH-10;

};

#endif // !_INTEGRATORFUNCTIONS_H_
