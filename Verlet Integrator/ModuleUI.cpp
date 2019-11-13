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

	menu_button.rect = { SCREEN_WIDTH - 40, 20, 20, 20 };

	selection_screen.enabled = false;
	selection_screen.rect = { SCREEN_WIDTH - 200, 0, 200, SCREEN_HEIGHT };

	ui_elements.add(&menu_button);
	ui_elements.add(&selection_screen);


	return ret;
}

update_status ModuleUI::Update()
{

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) 
	{
		if (CanBeSelected({ App->input->GetMouseX(), App->input->GetMouseY(), 0, 0 }, menu_button.rect)
			|| (menu_button.enabled == false && !CanBeSelected({ App->input->GetMouseX(), App->input->GetMouseY(), 0, 0 }, selection_screen.rect)))
		{
			menu_button.enabled = !menu_button.enabled;
			selection_screen.enabled = !selection_screen.enabled;
		}
	}


	for (unsigned int i = 0; i < ui_elements.count(); i++)
	{
		if(ui_elements[i]->enabled)
			App->renderer->DrawQuad(ui_elements[i]->rect, 255, 0, 255, 100);
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