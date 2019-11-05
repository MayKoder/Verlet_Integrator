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
	shapes.add(new Circle());
	shapes.add(new Circle());
	shapes.add(new Circle());
	shapes.add(new Circle());
	shapes.add(new Circle());
	shapes.add(new Circle());
	shapes.add(new Circle());
	shapes.add(new Circle());
	shapes.add(new Circle());
	shapes.add(new Circle());
	shapes.add(new Circle());
	shapes.add(new Circle());
	shapes.add(new Circle());

	float offset = 0;
	p2List_item<Circle*>* tmp_shape = shapes.getFirst();
	while (tmp_shape)
	{

		integrator->InitPoint(tmp_shape->data, {50.f + offset, 0});
		offset += 40.f;

		tmp_shape = tmp_shape->next;
	}

	return true;
}

// PreUpdate: clear buffer
update_status ModuleVerlet::PreUpdate()
{
	if(selected_shape)
		App->renderer->DrawLine(App->input->GetMouseX(), App->input->GetMouseY(), selected_shape->x, selected_shape->y, 255, 0, 0);

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

	//Check for selection
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		p2List_item<Circle*>* tmp_shape = shapes.getFirst();
		while (tmp_shape)
		{

			if (CanBeSelected({App->input->GetMouseX(), App->input->GetMouseY(), 0, 0}, tmp_shape->data->selector_rect))
			{
				selected_shape = tmp_shape->data;
			}

			tmp_shape = tmp_shape->next;
		}
	}
	else if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP && selected_shape)
	{

		//int x = App->input->GetMouseX() - p.old_x;
		//int y = App->input->GetMouseY() - p.old_y;		
		int x = App->input->GetMouseX() - selected_shape->old_x;
		int y = App->input->GetMouseY() - selected_shape->old_y;

		if (App->input->GetMouseY() < selected_shape->old_y)
		{
			selected_shape->y += y / 10;
		}
		else
		{
			selected_shape->y += y / 10;
		}

		if (App->input->GetMouseX() < selected_shape->old_x)
		{
			selected_shape->x += x / 10;
		}
		else
		{
			selected_shape->x += x / 10;
		}

		selected_shape = nullptr;

	}


	p2List_item<Circle*>* tmp_shape = shapes.getFirst();
	while (tmp_shape)
	{

		App->renderer->DrawCircle((int)tmp_shape->data->old_x, (int)tmp_shape->data->old_y, tmp_shape->data->radius, 255, 255, 255, 255);
		tmp_shape->data->selector_rect.x = (int)tmp_shape->data->old_x - tmp_shape->data->selector_rect.w / 2;
		tmp_shape->data->selector_rect.y = (int)tmp_shape->data->old_y - tmp_shape->data->selector_rect.h / 2;
		//App->renderer->DrawQuad(tmp_shape->data->selector_rect, 0, 0, 255, 100);

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