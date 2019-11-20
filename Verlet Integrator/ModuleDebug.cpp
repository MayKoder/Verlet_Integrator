#include "ModuleDebug.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"
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

	return ret;
}

update_status ModuleDebug::Update()
{

	return UPDATE_CONTINUE;
}
