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

	float angle = atan2(vertexB->y - vertexA->y, vertexB->x - vertexA->x);
	float distanceH = sqrt(pow(vertexB->x - vertexA->x, 2) + pow(vertexB->y - vertexA->y, 2) * 1.0f);


	LOG("Angle %f", angle * 180 / PI);
	LOG("Distance %f", distanceH);

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
}

void Box::UpdateShape() {}
void Box::Draw() {}