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

	return true;
}

// PreUpdate: clear buffer
update_status ModuleVerlet::PreUpdate()
{
	if(selected_point)
		App->renderer->DrawLine(App->input->GetMouseX(), App->input->GetMouseY(), (int)selected_point->x, (int)selected_point->y, 255, 0, 0);

	////TODO: add lists with [] operator
	for (int i = 0; i < (int)world_points.count(); i++)
	{
		integrator->updatePoints(world_points[i]);
	}

	return UPDATE_CONTINUE;
}

// Update: debug camera
update_status ModuleVerlet::Update()
{

	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN) 
	{
		integrator->InitPoint(world_points.add(new Point())->data, {(float)App->input->GetMouseX(), (float)App->input->GetMouseY()});
	}


	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN) 
	{
		Point* sel = MouseHoverSelection();
		if (sel) 
		{
			selected_point = sel;
		}
	}

	//Check for selection
	//if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	//{
	//	p2List_item<Point*>* tmp_shape = shapes.getFirst();
	//	while (tmp_shape)
	//	{

	//		if (CanBeSelected({App->input->GetMouseX(), App->input->GetMouseY(), 0, 0}, tmp_shape->data->selector_rect))
	//		{
	//			selected_shape = tmp_shape->data;
	//		}

	//		tmp_shape = tmp_shape->next;
	//	}
	//}
	//else if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP && selected_shape)
	//{

	//	//int x = App->input->GetMouseX() - p.old_x;
	//	//int y = App->input->GetMouseY() - p.old_y;		
	//	int x = App->input->GetMouseX() - selected_shape->old_x;
	//	int y = App->input->GetMouseY() - selected_shape->old_y;

	//	if (App->input->GetMouseY() < selected_shape->old_y)
	//	{
	//		selected_shape->y += y / 10;
	//	}
	//	else
	//	{
	//		selected_shape->y += y / 10;
	//	}

	//	if (App->input->GetMouseX() < selected_shape->old_x)
	//	{
	//		selected_shape->x += x / 10;
	//	}
	//	else
	//	{
	//		selected_shape->x += x / 10;
	//	}

	//	selected_shape = nullptr;

	//}





	//Draw launch line
	for (int i = 0; i < (int)world_points.count(); i++)
	{
		Point* tmp_point = world_points[i];
		App->renderer->DrawCircle((int)tmp_point->old_x, (int)tmp_point->old_y, tmp_point->radius, 255, 255, 255, 255);
		tmp_point->selector_rect.x = (int)tmp_point->old_x - tmp_point->selector_rect.w / 2;
		tmp_point->selector_rect.y = (int)tmp_point->old_y - tmp_point->selector_rect.h / 2;
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

	for (int i = 0; i < (int)world_points.count(); i++)
	{
		delete world_points[i];
	}
	world_points.clear();

	for (int i = 0; i < (int)shapes.count(); i++)
	{
		delete shapes[i];
	}
	shapes.clear();

	return true;
}

Point* ModuleVerlet::MouseHoverSelection() 
{
	for (unsigned int i = 0; i < world_points.count(); i++)
	{
		Point* tmp_shape = world_points[i];
		if (CanBeSelected({ App->input->GetMouseX(), App->input->GetMouseY(), 0, 0 }, tmp_shape->selector_rect))
		{
			return world_points[i];
		}
	}
	return nullptr;
}