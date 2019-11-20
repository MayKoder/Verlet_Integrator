#include "ModuleDebug.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"
#include "Module.h"
#include "SDL\include\SDL.h"

ModuleDebug::ModuleDebug(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleDebug::~ModuleDebug()
{}

bool ModuleDebug::Awake()
{
	bool ret = true;
	return ret;
}

bool ModuleDebug::Start()
{
	bool ret = true;
	ret= App->fonts->Load("Fonts/debug_font.png", "APVositncelrya1234567890",1, 26, 38, 24);

	return ret;
}

update_status ModuleDebug::Update()
{
	App->fonts->BlitText(App->renderer->camera.x+20, App->renderer->camera.y+10,1, "Position");
	App->fonts->BlitText(App->renderer->camera.x+20, App->renderer->camera.y+60,1, "Velocity");
	App->fonts->BlitText(App->renderer->camera.x+20, App->renderer->camera.y+110,1, "Acceleration");
	return update_status::UPDATE_CONTINUE;
}

