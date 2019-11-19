#include "IntegratorFunctions.h"
#include"ModuleVerlet.h"

VerletIntegrator::VerletIntegrator()
{}

VerletIntegrator::VerletIntegrator(Application* app)
{
	App = app;
}

void VerletIntegrator::InitPoint(Point* p, vector2 pos)
{
	p->x = pos.x;
	p->y = pos.y;
	p->old_x = pos.x;
	p->old_y = pos.y;
	p->vx =	0.f;
	p->vy = 0.f;
	p->dt = (1.f/ 60.f);

	//p->color.r = (Uint8)rand() % 255;
	//p->color.g = (Uint8)rand() % 255;
	//p->color.b = (Uint8)rand() % 255;
	p->color.r = (Uint8)rand() % 255;
	p->color.g = (Uint8)rand() % 255;
	p->color.b = (Uint8)rand() % 255;
	p->color.a = 80;

	p->selector_rect = { (int)pos.x, (int)pos.y, p->radius * 2, p->radius * 2};
}

void VerletIntegrator::AddForce(Point* p, vector2 force) 
{
	p->vx += force.x;
	p->vy += force.y;
}

void VerletIntegrator::updatePoints(Point* p)
{

	//p->vx = (p->x - p->old_x) /** friction*/;
	//p->vy = (p->y - p->old_y) /** friction*/;

	//p->old_x = p->x;
	//p->old_y = p->y;
	//p->x += p->vx;
	//p->y += p->vy;
	//p->y += gravity;
	//LOG("POINT X: %.2f, POINT Y: %.2f", p->x, p->y);

	////RIGHT LIMIT
	//if (p->x > floor_Limit_X) //SHOULD BE CHANGED, INCLUDING SDL AND SO SCREEN WIDTH INSTEAD OF 200
	//{
	//	p->x = (float)floor_Limit_X;
	//	p->old_x = p->x + p->vx * bounce; //p.old_y should remain the same	
	//}
	////LEFT LIMIT
	//else if (p->x < 0 + p->radius)
	//{
	//	p->x = 0 + (float)p->radius;
	//	p->old_x = p->x + p->vx * bounce;
	//}
	////TOP LIMIT
	//if (p->y > floor_Limit_Y) //SHOULD BE CHANGED, INCLUDING SDL AND SO SCREEN HEIGHT INSTEAD OF 200
	//{
	//	p->y = (float)floor_Limit_Y;
	//	p->old_y = p->y + p->vy * bounce; //p.old_x should remain the same	
	//}
	////BOTTOM LIMIT
	//else if (p->y < 0 + p->radius)
	//{
	//	p->y = 0 + (float)p->radius;
	//	p->old_y = p->y + p->vy * bounce;
	//}

	double incrementX = fabs(p->x);
	double incrementY = fabs(p->y);

	//Update particle position
	p->x = p->x + (p->vx * p->dt) + (0.5f * 0.f * (p->dt * p->dt));
	p->y = p->y + (p->vy * p->dt) + (0.5f * gravity * (p->dt * p->dt));

	incrementX -= fabs(p->x);
	incrementY -= fabs(p->y);



	//BOTTOM LIMIT
	if (p->y > (float)floor_Limit_Y)
	{
		p->y = (float)floor_Limit_Y;
		p->vy *= -1.f * bounce;
	}
	else if(p->y <= (float)p->radius)
	{
		p->y = (float)p->radius;
		p->vy *= -1 * bounce;
	}

	if (p->x >= (float)floor_Limit_X) 
	{
		p->x = (float)floor_Limit_X;
		p->vx *= -1 * bounce;
	}
	else if(p->x <= (float)p->radius)
	{
		p->x = (float)p->radius;
		p->vx *= -1 * bounce;
	}

	//Collision detection between particles (not lines)
	for (unsigned int j = 0; j < App->verlet->world_points.count(); j++)
	{
		Point* check_Point = App->verlet->world_points[j];
		if (App->verlet->world_points[j] != p)
		{
			if (pow((check_Point->x - p->x), 2) + pow((p->y - check_Point->y), 2) <= pow((p->radius + check_Point->radius), 2))
			{
				p->vx *= -1 * bounce;
				p->vy *= -1 * bounce;

				//Ugly way to do collision correction, needs an update
				p->x += incrementX;
				p->y += incrementY;


				check_Point->vx = p->vx;
				check_Point->vx *= -1 * bounce;

				check_Point->vy = p->vy;
				check_Point->vy *= -1 * bounce;
			}
		}
	}

	//Velocity update for the next frame (and next position calculation)
	p->vx = p->vx + (0.f * p->dt);
	p->vy = p->vy + (gravity * p->dt);

	LOG("%f, %f", incrementX, incrementY);


}

//void VerletIntegrator::OnCollision(vector2 point, Point* p) 
//{
//
//}

