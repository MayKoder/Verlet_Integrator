#ifndef _SHAPES_H_
#define _SHAPES_H_

#include"IntegratorFunctions.h"
#include"SDL/include/SDL.h"

struct Point {

	float x;
	float y;
	float old_x;
	float old_y;
	float vx;
	float vy;
	int radius = 10;

	SDL_Rect selector_rect;
};


enum ShapeType
{
	NO_SHAPE, LINE, CIRCLE
};


class Shape
{
public:

	Shape()
	{
		type = NO_SHAPE;
	}

	Shape(ShapeType s_type)
	{
		type = s_type;
	}
	~Shape() {}

public:

	ShapeType type;

};

class Line : public Shape
{
public:

	Line(Point* pointA, Point* pointB)
	{
		type = LINE;
		vertexA = pointA;
		vertexB = pointB;
	}
	~Line(){}

public:

	//Edge
	Point* vertexA;
	Point* vertexB;

	void GetVertexA() {
		
	}

};

#endif // !_SHAPES_H
