#include "Globals.h"
#include "Application.h"
#include "ModuleVerlet.h"
#include"IntegratorFunctions.h"


ModuleVerlet::ModuleVerlet(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	integrator = new VerletIntegrator(app);
	creation_type = ShapeType::CIRCLE;
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

	////TODO: add lists with [] operator
	for (unsigned int i = 0; i < shapes.count(); i++)
	{
		shapes[i]->UpdateShape();
	}

	if (selected_point)
		App->renderer->DrawLine(App->input->GetMouseX(), App->input->GetMouseY(), (int)selected_point->x, (int)selected_point->y, 255, 0, 0);

	return UPDATE_CONTINUE;
}

// Update: debug camera
update_status ModuleVerlet::Update()
{

	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN) 
	{

		if(App->debug->debugPointNumber == -1)
			App->debug->debugPointNumber = 0;

		switch (creation_type)
		{
		case NO_SHAPE:
			break;
		case LINE:
			//integrator->InitPoint(world_points.add(new Point())->data, { (float)App->input->GetMouseX(), (float)App->input->GetMouseY() });
			break;
		case CIRCLE:

			shapes.add(new Circle(new Point(), integrator, App));
			break;
		case BOX:
			break;
		}

	}

	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		bigPlanetEnabled = true;
	}

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	{
		smallPlanetEnabled = true;
	}


	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN) 
	{
		Point* sel = MouseHoverSelection();
		if (sel) 
		{
			selected_point = sel;
		}
	}
	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP && selected_point)
	{
		Point* sel = MouseHoverSelection();
		if (sel && sel != selected_point)
		{
			shapes.add(new Line(selected_point, sel, integrator, App));
		}
		selected_point = nullptr;
	}

	//Check for selection
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		Point* sel = MouseHoverSelection();
		if (sel)
		{
			selected_point = sel;
		}
	}
	else if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP && selected_point)
	{

		//int x = App->input->GetMouseX() - p.old_x;
		//int y = App->input->GetMouseY() - p.old_y;		
		float x = (float)App->input->GetMouseX() - selected_point->x;
		float y = (float)App->input->GetMouseY() - selected_point->y;

		integrator->AddForce(selected_point, {x * 3, y * 3});

		selected_point = nullptr;

	}





	//Draw launch line
	for (unsigned int i = 0; i < world_points.count(); i++)
	{
		Point* tmp_point = world_points[i];
		App->renderer->DrawCircle((int)tmp_point->x, (int)tmp_point->y, tmp_point->radius, 255, 255, 255, 255);
		tmp_point->selector_rect.x = (int)tmp_point->x - tmp_point->selector_rect.w / 2;
		tmp_point->selector_rect.y = (int)tmp_point->y - tmp_point->selector_rect.h / 2;
		if(tmp_point == world_points[App->debug->debugPointNumber])
			App->renderer->DrawQuad({ (int)tmp_point->selector_rect.x, (int)tmp_point->selector_rect.y, 20, 20}, (int)tmp_point->color.r, (int)tmp_point->color.g, (int)tmp_point->color.b, (int)tmp_point->color.a);
	}
	for (unsigned int i = 0; i < shapes.count(); i++)
	{
		Shape* tmp = shapes[i];
		tmp->Draw();
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
		if (App->UI->CanBeSelected({ App->input->GetMouseX(), App->input->GetMouseY(), 0, 0 }, tmp_shape->selector_rect))
		{
			return world_points[i];
		}
	}
	return nullptr;
}