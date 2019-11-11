#include "IntegratorFunctions.h"
#include"ModuleVerlet.h"

VerletIntegrator::VerletIntegrator()
{}

void VerletIntegrator::InitPoint(Point* p, vector2 pos)
{
	p->x = pos.x;
	p->y = pos.y;
	p->old_x = pos.x;
	p->old_y = pos.y;
	p->vx = 0.f;
	p->vy = 0.f;

	p->selector_rect = { (int)pos.x, (int)pos.y, p->radius * 2, p->radius * 2};

	//point.add(p);
}

void VerletIntegrator::updatePoints(Point* p)
{
	//FOR MORE THAN ONE POINT - NOT COMPLETE
	/*for (int i = 0; i < point.count(); i++)
	{
		Point p = point[i];
		float vx = p.x - p.old_x;
		float vy = p.y - p.old_y;

		p.old_x = p.x;
		p.old_y = p.y;
		p.x += vx;
		p.y += vy;

		point.add(p);

	}*/

	p->vx = (p->x - p->old_x) /** friction*/;
	p->vy = (p->y - p->old_y) /** friction*/;

	p->old_x = p->x;
	p->old_y = p->y;
	p->x += p->vx;
	p->y += p->vy;
	p->y += gravity;
	LOG("POINT X: %.2f, POINT Y: %.2f", p->x, p->y);

	//RIGHT LIMIT
	if (p->x > floor_Limit_X) //SHOULD BE CHANGED, INCLUDING SDL AND SO SCREEN WIDTH INSTEAD OF 200
	{
		p->x = (float)floor_Limit_X;
		p->old_x = p->x + p->vx * bounce; //p.old_y should remain the same	
	}
	//LEFT LIMIT
	else if (p->x < 0 + p->radius)
	{
		p->x = 0 + (float)p->radius;
		p->old_x = p->x + p->vx * bounce;
	}
	//TOP LIMIT
	if (p->y > floor_Limit_Y) //SHOULD BE CHANGED, INCLUDING SDL AND SO SCREEN HEIGHT INSTEAD OF 200
	{
		p->y = (float)floor_Limit_Y;
		p->old_y = p->y + p->vy * bounce; //p.old_x should remain the same	
	}
	//BOTTOM LIMIT
	else if (p->y < 0 + p->radius)
	{
		p->y = 0 + (float)p->radius;
		p->old_y = p->y + p->vy * bounce;
	}
	
}

void VerletIntegrator::updateLine(Line* lne) 
{
	updatePoints(lne->vertexA);
	updatePoints(lne->vertexB);
	//
	//lne->vertexB->old_x = lne->vertexA->old_x;
	////lne->vertexB->old_y = lne->vertexA->old_y;
	//lne->vertexB->vx = lne->vertexA->vx;
	////lne->vertexB->vy = lne->vertexA->vy;
	//lne->vertexB->x = lne->vertexA->x;
	////lne->vertexB->y = lne->vertexA->y;



	//lne->vertexB->old_x += lne->offsetX;
	////lne->vertexB->old_y += lne->offsetY;	
	//lne->vertexB->x = lne->vertexB->old_x;
	////lne->vertexB->y = lne->vertexB->old_y;

	//updatePoints(lne->vertexB);

}

