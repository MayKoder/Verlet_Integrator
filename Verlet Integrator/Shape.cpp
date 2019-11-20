#include"Shape.h"

Circle::Circle(Point* s_point, VerletIntegrator* s_integrator, Application* app)
{
	App = app;
	type = CIRCLE;
	integrator = s_integrator;
	point = s_point;

	App->verlet->world_points.add(point);
	integrator->InitPoint(point, { (float)App->input->GetMouseX(), (float)App->input->GetMouseY() });
}
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
void Line::Draw() 
{
	App->renderer->DrawLine((int)vertexA->x, (int)vertexA->y, (int)vertexB->x, (int)vertexB->y, 0, 255, 0, 255);
}

void Circle::UpdateShape()
{
	integrator->updatePoints(point);
}
void Circle::Draw() 
{
	App->renderer->DrawCircle((int)point->x, (int)point->y, point->radius, 255, 255, 255, 255);
}