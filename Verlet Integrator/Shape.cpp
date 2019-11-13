#include"Shape.h"

void Line::UpdateShape() 
{
	integrator->updatePoints(vertexA);
	integrator->updatePoints(vertexB);

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

	int newOffsetX = (int)(rightPoint->old_x - leftPoint->old_x);
	int newOffsetY = (int)(rightPoint->old_y - leftPoint->old_y);

	if (offsetX != newOffsetX)
	{
		if (newOffsetX > offsetX) 
		{
			//La linia es mes llarga
			int correction = newOffsetX - offsetX;

			//Fer dominant el vertex amb la velocitat mes gran
			if (leftPoint->vx < 0) 
			{
				rightPoint->old_x -= correction / 2;
				rightPoint->x -= correction / 2;
			}
			else
			{
				leftPoint->old_x += correction / 2;
				leftPoint->x += correction / 2;
			}
		}
		else
		{
			//La linia es mes llarga
			int correction = newOffsetX - offsetX;

			//Fer dominant el vertex amb la velocitat mes gran
			if (leftPoint->vx > 0)
			{
				rightPoint->old_x -= correction / 2;
				rightPoint->x -= correction / 2;
			}
			else
			{
				leftPoint->old_x += correction / 2;
				leftPoint->x += correction / 2;
			}
		}
	}

}