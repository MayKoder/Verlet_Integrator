#ifndef _SHAPES_H_
#define _SHAPES_H_

#include"IntegratorFunctions.h"
#include"ModuleVerlet.h"
#include"SDL/include/SDL.h"
#include"Application.h"

class Application;
//Struct point declaration
struct Point 
{
	float x;
	float y;
	float old_x;
	float old_y;
	float vx;
	float vy;
	int radius = 10;
	SDL_Color color;

	//This needs to be converted to a real dt
	float dt;

	SDL_Rect selector_rect;
};

//Shape types
enum ShapeType
{
	NO_SHAPE, LINE, CIRCLE, BOX
};


//Shape class
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
//Line class
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

//Circle class
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

//Box class
struct Point;
class Line;
class Box : public Shape
{
public:

	Box(VerletIntegrator* s_integrator, Application* app);
	~Box() {}

	void UpdateShape();
	void Draw();

public:

	//Point
	Point* box_points[4];
	Line* lines[5];
	float long_line_length = 50.f;
	float short_line_length = 50.f;

};

#endif // !_SHAPES_H
