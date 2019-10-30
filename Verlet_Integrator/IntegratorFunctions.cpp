#include "IntegratorFunctions.h"
#include "p2Log.h"

VerletIntegrator::VerletIntegrator()
{}

void VerletIntegrator::updatePoints(){
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
	while (1)
	{
		p.vx = (p.x - p.old_x) /** friction*/;
		p.vy = (p.y - p.old_y) /** friction*/;

		p.old_x = p.x;
		p.old_y = p.y;
		p.x += p.vx;
		p.y += p.vy;
		p.y += gravity;
		LOG("POINT X: %.2f", p.x);
		LOG("POINT Y: %.2f", p.y);

		//RIGHT LIMIT
		if (p.x > 100) //SHOULD BE CHANGED, INCLUDING SDL AND SO SCREEN WIDTH INSTEAD OF 200
		{
			p.x = 100;
			p.old_x = p.x + p.vx * bounce; //p.old_y should remain the same	
		}
		//LEFT LIMIT
		else if (p.x < 0) 
		{
			p.x = 0;
			p.old_x = p.x + p.vx * bounce;
		}
		//TOP LIMIT
		if (p.y > 100) //SHOULD BE CHANGED, INCLUDING SDL AND SO SCREEN HEIGHT INSTEAD OF 200
		{
			p.y = 100;
			p.old_y = p.y + p.vy * bounce; //p.old_x should remain the same	
		}
		//BOTTOM LIMIT
		else if (p.y < 0) 
		{
			p.y = 0;
			p.old_y = p.y + p.vy * bounce;
		}
	}
}

void VerletIntegrator::InitPoint()
{
		p.x = 50.f;
		p.y = 50.f;
		p.old_x = 45.f;
		p.old_y = 45.f;
		p.vx = 0.f;
		p.vy = 0.f;
		//point.add(p);
}


