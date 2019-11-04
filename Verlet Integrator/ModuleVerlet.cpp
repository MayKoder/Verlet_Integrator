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
	VerletIntegrator::InitPoint(p);
	return true;
}

// PreUpdate: clear buffer
update_status ModuleVerlet::PreUpdate()
{
	VerletIntegrator::updatePoints(p);
	return UPDATE_CONTINUE;
}

// Update: debug camera
update_status ModuleVerlet::Update()
{


	App->renderer->DrawCircle((int)p.x, (int)p.y, p.radius, 255, 255, 255, 255);

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

	return true;
}