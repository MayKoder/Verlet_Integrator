#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include "Module.h"
#include"p2List_Extended.h"

struct UI_Button {
	bool enabled = true;
	SDL_Rect rect;
};



class Application;

class ModuleUI : public Module
{
public:

	ModuleUI(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleUI();

	bool Init();
	update_status Update();
	bool CleanUp();

	bool CanBeSelected(const SDL_Rect& rect, const SDL_Rect& r);

public:

	UI_Button menu_button;
	UI_Button selection_screen;

	p2List_Extended<UI_Button*> ui_elements;


};

#endif // __ModuleUI_H__