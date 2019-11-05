#ifndef __ModuleVerlet_H__
#define __ModuleVerlet_H__

#include "Globals.h"
#include "Application.h"
#include"Module.h"

struct Circle {

	float x;
	float y;
	float old_x;
	float old_y;
	float vx;
	float vy;
	int radius = 10;

	SDL_Rect selector_rect;

};


class VerletIntegrator;
class ModuleVerlet : public Module
{
public:

	ModuleVerlet(Application* app, bool start_enabled = true);
	~ModuleVerlet();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();


	p2List<Circle*> shapes;
	VerletIntegrator* integrator;

	Circle* selected_shape;

	bool CanBeSelected(const SDL_Rect& rect, const SDL_Rect& r)
	{
		bool detectedX = true;
		bool detectedY = true;

		if ((rect.x + rect.w) < r.x || (r.x + r.w) < rect.x)
		{
			detectedX = false;
		}

		if (rect.y < r.y || (rect.y + rect.h) > r.y + r.h)
		{
			detectedY = false;
		}

		return detectedX && detectedY;
	}

};

#endif // __ModuleVerlet_H__