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
	//float angle = atan2(vertexB->y - vertexA->y, vertexB->x - vertexA->x);
	//float distanceH = lenght;

	//float newX = distanceH * cosf(angle);
	//float newY = distanceH * sinf(angle);

	//vector2 corA = { vertexB->x - newX , vertexB->y - newY };
	//vector2 corB = { vertexA->x + newX ,  vertexA->y + newY };

	//vertexA->x = vertexB->x - newX;
	//vertexA->y = vertexB->y - newY;
	//vertexB->x = vertexA->x + newX;
	//vertexB->y = vertexA->y + newY;


	float angle = atan2(vertexB->y - vertexA->y, vertexB->x - vertexA->x);
	float distanceH = lenght;

	float newX = distanceH * cosf(angle);
	float newY = distanceH * sinf(angle);

	vector2 midPoint = { (vertexA->x + vertexB->x) / 2, (vertexA->y + vertexB->y) / 2 };
	vector2 corA = { vertexB->x - newX , vertexB->y - newY };
	vector2 corB = { vertexA->x + newX ,  vertexA->y + newY };
	App->renderer->DrawCircle(midPoint.x, midPoint.y, 5, 255, 255, 9, 255);

	vertexA->x = midPoint.x - (newX / 2.f);
	vertexA->y = midPoint.y - (newY / 2.f);
	vertexB->x = midPoint.x + (newX / 2.f);
	vertexB->y = midPoint.y + (newY / 2.f);

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


	lines[0] = (Line*)integrator->shapes.add(new Line(box_points[0], box_points[1], integrator, App))->data;
	lines[1] = (Line*)integrator->shapes.add(new Line(box_points[0], box_points[2], integrator, App))->data;
	lines[2] = (Line*)integrator->shapes.add(new Line(box_points[0], box_points[3], integrator, App))->data;
	lines[3] = (Line*)integrator->shapes.add(new Line(box_points[1], box_points[3], integrator, App))->data;
	lines[4] = (Line*)integrator->shapes.add(new Line(box_points[2], box_points[3], integrator, App))->data;
	lines[5] = (Line*)integrator->shapes.add(new Line(box_points[1], box_points[2], integrator, App))->data;
}

void Box::UpdateShape() {}
void Box::Draw() {}