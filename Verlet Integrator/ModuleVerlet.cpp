#include "Globals.h"
#include "Application.h"
#include "ModuleVerlet.h"

ModuleVerlet::ModuleVerlet(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleVerlet::~ModuleVerlet()
{}

// Called before render is available
bool ModuleVerlet::Init()
{

	return true;
}

// PreUpdate: clear buffer
update_status ModuleVerlet::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Update: debug camera
update_status ModuleVerlet::Update()
{
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