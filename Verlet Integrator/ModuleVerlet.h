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


	Circle p;
	VerletIntegrator* integrator;

};

#endif // __ModuleVerlet_H__