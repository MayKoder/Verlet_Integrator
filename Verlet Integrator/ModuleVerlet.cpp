#include "Globals.h"
#include "Application.h"
#include "ModuleVerlet.h"
#include"IntegratorFunctions.h"


ModuleVerlet::ModuleVerlet(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleVerlet::~ModuleVerlet()
{}

// Called before render is available
bool ModuleVerlet::Init()
{
	integrator = new VerletIntegrator();
	integrator->InitPoint(&p);
	return true;
}

// PreUpdate: clear buffer
update_status ModuleVerlet::PreUpdate()
{
	App->renderer->DrawLine(App->input->GetMouseX(), App->input->GetMouseY(), p.x, p.y, 255, 0, 0);
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{

		//int x = App->input->GetMouseX() - p.old_x;
		//int y = App->input->GetMouseY() - p.old_y;		
		int x = App->input->GetMouseX() - p.old_x;
		int y = App->input->GetMouseY() - p.old_y;




		if (App->input->GetMouseY() < p.old_y)
		{
			p.y += y / 10;
		}
		else
		{
			p.y += y / 10;
		}

		if (App->input->GetMouseX() < p.old_x)
		{
			p.x += x / 10;
		}
		else
		{
			p.x += x / 10;
		}

	}
	integrator->updatePoints(&p);
	return UPDATE_CONTINUE;
}

// Update: debug camera
update_status ModuleVerlet::Update()
{

	App->renderer->DrawCircle((int)p.old_x, (int)p.old_y, p.radius, 255, 255, 255, 255);

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleVerlet::PostUpdate()
{

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleVerlet::CleanUp()
{
	LOG("Destroying Verlet");

	delete integrator;

	return true;
}