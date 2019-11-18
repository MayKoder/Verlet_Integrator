#ifndef _SHAPES_H_
#define _SHAPES_H_

#include"IntegratorFunctions.h"
#include"ModuleVerlet.h"
#include"SDL/include/SDL.h"
#include"Application.h"

class Application;
struct Point {

	float x;
	float y;
	float old_x;
	float old_y;
	float vx;
	float vy;
	int radius = 10;

	//This needs to be converted to a real dt
	float dt;

	/*
	float mass;
	float newVX;
	float newVY;
	float currentVX;
	float currentVY;
	float sum_forcesX;
	float sum_forcesY;
	float acc_x;
	float acc_y;

	currentX = 

	*/

	SDL_Rect selector_rect;
};


enum ShapeType
{
	NO_SHAPE, LINE, CIRCLE, BOX
};


class Shape
{
public:

	Shape()
	{
		type = NO_SHAPE;
	}

	Shape(ShapeType s_type, VerletIntegrator* s_integrator)
	{
		type = s_type;
		integrator = s_integrator;
	}

	virtual void UpdateShape() = 0;
	virtual void Draw() = 0;

	~Shape() {}

public:

	ShapeType type;
	VerletIntegrator* integrator;
	Application* App = nullptr;

};

class VerletIntegrator;
class Line : public Shape
{
public:

	Line(Point* pointA, Point* pointB, VerletIntegrator* s_integrator, Application* app)
	{
		type = LINE;
		App = app;
		integrator = s_integrator;
		vertexA = pointA;
		vertexB = pointB;

		Point* leftPoint;
		Point* rightPoint;

		if (vertexA->old_x > vertexB->old_x)
		{
			rightPoint = vertexA;
			leftPoint = vertexB;
		}
		else
		{
			rightPoint = vertexB;
			leftPoint = vertexA;
		}

		offsetX = (int)(rightPoint->old_x - leftPoint->old_x);
		offsetY = (int)(rightPoint->old_y - leftPoint->old_y);

		lenght = sqrt(pow(offsetX, 2) +
			pow(offsetY, 2) * 1.0f);


	}
	~Line(){}

	void UpdateShape();
	void Draw();

public:

	//Edge
	Point* vertexA;
	Point* vertexB;

	int offsetX, offsetY;

	double lenght;

};

class Circle : public Shape
{
public:

	Circle(Point* s_point, VerletIntegrator* s_integrator, Application* app);
	~Circle() {}

	void UpdateShape();
	void Draw();

public:

	//Point
	Point* point;

};

#endif // !_SHAPES_H
