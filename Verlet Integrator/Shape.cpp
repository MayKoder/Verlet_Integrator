#include"Shape.h"

Circle::Circle(Point* s_point, VerletIntegrator* s_integrator, Application* app)
{
	App = app;
	type = CIRCLE;
	integrator = s_integrator;
	point = s_point;

	App->verlet->integrator->world_points.add(point);
	integrator->InitPoint(point, { (float)App->input->GetMouseX(), (float)App->input->GetMouseY() });
}
void Line::UpdateShape() 
{

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
	//integrator->updatePoints();
}
void Circle::Draw() 
{
	App->renderer->DrawCircle((int)point->x, (int)point->y, point->radius, 255, 255, 255, 255);
}

Box::Box(VerletIntegrator* s_integrator, Application* app)
{
	App = app;
	type = BOX;
	integrator = s_integrator;

	for (int i = 0; i < 4; i++)
	{
		box_points[i] = integrator->world_points.add(new Point())->data;
	}

	vector2 pos = { (float)App->input->GetMouseX(), (float)App->input->GetMouseY() };
	integrator->InitPoint(box_points[0], pos);
	integrator->InitPoint(box_points[1], { pos.x + long_line_length, pos.y });
	integrator->InitPoint(box_points[2], { pos.x, pos.y + short_line_length });
	integrator->InitPoint(box_points[3], { pos.x + long_line_length, pos.y + short_line_length });


	//Lines* lines[5];
}

void Box::UpdateShape() {}
void Box::Draw() {}