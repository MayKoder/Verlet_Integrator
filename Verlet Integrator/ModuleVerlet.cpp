#include "Globals.h"
#include "Application.h"
#include "ModuleVerlet.h"
#include"IntegratorFunctions.h"


ModuleVerlet::ModuleVerlet(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	integrator = new VerletIntegrator();
}

// Destructor
ModuleVerlet::~ModuleVerlet()
{}

// Called before render is available
bool ModuleVerlet::Init()
{


	shapes.add(new Circle());
	shapes.add(new Circle());

	float offset = 0;
	p2List_item<Circle*>* tmp_shape = shapes.getFirst();
	while (tmp_shape)
	{

		integrator->InitPoint(tmp_shape->data, {50.f + offset, 50.f});
		offset += 40.f;

		tmp_shape = tmp_shape->next;
	}

	return true;
}

// PreUpdate: clear buffer
update_status ModuleVerlet::PreUpdate()
{
	//App->renderer->DrawLine(App->input->GetMouseX(), App->input->GetMouseY(), p.x, p.y, 255, 0, 0);
	//if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	//{

	//	//int x = App->input->GetMouseX() - p.old_x;
	//	//int y = App->input->GetMouseY() - p.old_y;		
	//	int x = App->input->GetMouseX() - p.old_x;
	//	int y = App->input->GetMouseY() - p.old_y;




	//	if (App->input->GetMouseY() < p.old_y)
	//	{
	//		p.y += y / 10;
	//	}
	//	else
	//	{
	//		p.y += y / 10;
	//	}

	//	if (App->input->GetMouseX() < p.old_x)
	//	{
	//		p.x += x / 10;
	//	}
	//	else
	//	{
	//		p.x += x / 10;
	//	}

	//}

	//TODO: add lists with [] operator
	p2List_item<Circle*>* tmp_shape = shapes.getFirst();
	while (tmp_shape)
	{

		integrator->updatePoints(tmp_shape->data);

		tmp_shape = tmp_shape->next;
	}

	return UPDATE_CONTINUE;
}

// Update: debug camera
update_status ModuleVerlet::Update()
{

	p2List_item<Circle*>* tmp_shape = shapes.getFirst();
	while (tmp_shape)
	{

		App->renderer->DrawCircle((int)tmp_shape->data->old_x, (int)tmp_shape->data->old_y, tmp_shape->data->radius, 255, 255, 255, 255);

		tmp_shape = tmp_shape->next;
	}


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

	p2List_item<Circle*>* tmp_shape = shapes.getFirst();
	while (tmp_shape)
	{

		delete tmp_shape->data;

		tmp_shape = tmp_shape->next;
	}
	shapes.clear();

	return true;
}