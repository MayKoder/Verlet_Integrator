#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include "Module.h"
#include"p2List_Extended.h"
#include "Shape.h"

enum ShapeType;
struct UI_Button {
	bool enabled = true;
	SDL_Rect rect;
	ShapeType type;
	SDL_Color color;

	ShapeType OnClick() 
	{
		return type;
	}

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

	void SetButton(UI_Button* button, SDL_Rect pos_size, bool enabled, ShapeType creation_type, SDL_Color color);

public:

	UI_Button menu_button;
	UI_Button selection_screen;

	//Selection buttons
	UI_Button selectors[3];


	p2List_Extended<UI_Button*> ui_elements;


};

#endif // __ModuleUI_H__