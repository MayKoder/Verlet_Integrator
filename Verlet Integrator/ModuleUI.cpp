#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

// Destructor
ModuleUI::~ModuleUI()
{
}

// Called before render is available
bool ModuleUI::Init()
{
	bool ret = true;

	SetButton(&menu_button, { SCREEN_WIDTH - 40, 20, 20, 20 }, true, ShapeType::NO_SHAPE, {0, 255, 255, 100});
	SetButton(&selection_screen, { SCREEN_WIDTH - 200, 0, 200, SCREEN_HEIGHT }, false, ShapeType::NO_SHAPE, {0, 255, 255, 100});
	SetButton(&ball_creator, { SCREEN_WIDTH - 167, 30, 140, 140 }, false, ShapeType::CIRCLE, {0, 0, 255, 100});
	SetButton(&line_creator, { SCREEN_WIDTH - 167, 200, 140, 140 }, false, ShapeType::LINE, {0, 0, 255, 100});
	SetButton(&box_creator, { SCREEN_WIDTH - 167, 370, 140, 140 }, false, ShapeType::BOX, {0, 0, 255, 100});



	return ret;
}

update_status ModuleUI::Update()
{

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) 
	{
		if (CanBeSelected({ App->input->GetMouseX(), App->input->GetMouseY(), 0, 0 }, menu_button.rect)
			|| (menu_button.enabled == false && !CanBeSelected({ App->input->GetMouseX(), App->input->GetMouseY(), 0, 0 }, selection_screen.rect)))
		{
			//menu_button.enabled = !menu_button.enabled;
			//selection_screen.enabled = !selection_screen.enabled;

			for (unsigned int i = 0; i < ui_elements.count(); i++)
			{
				ui_elements[i]->enabled = !ui_elements[i]->enabled;
			}


		}
	}


	for (unsigned int i = 0; i < ui_elements.count(); i++)
	{
		if(ui_elements[i]->enabled)
			App->renderer->DrawQuad(ui_elements[i]->rect, ui_elements[i]->color.r, ui_elements[i]->color.g, ui_elements[i]->color.b, ui_elements[i]->color.a);
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleUI::CleanUp()
{
	ui_elements.clear();
	return true;
}


bool ModuleUI::CanBeSelected(const SDL_Rect& rect, const SDL_Rect& r)
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

void ModuleUI::SetButton(UI_Button* button, SDL_Rect pos_size, bool enabled, ShapeType creation_type, SDL_Color color)
{

	button->rect = pos_size;
	button->enabled = enabled;
	button->type = creation_type;
	button->color = color;

	ui_elements.add(button);

}