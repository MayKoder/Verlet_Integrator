#ifndef __ModuleDebug_H__
#define __ModuleDebug_H__

#include "Module.h"
#include "SDL\include\SDL_pixels.h"
#include "Globals.h"

class ModuleDebug :public Module {

public:
	ModuleDebug(Application* app, bool start_enabled = true);
	~ModuleDebug();
	bool Awake();
	bool Start();
	update_status Update();
};

#endif