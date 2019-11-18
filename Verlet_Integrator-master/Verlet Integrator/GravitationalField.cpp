#include "IntegratorFunctions.h"
#include "ModuleVerlet.h"
#include "GravitationalField.h"
#include "Module.h"
#include "Application.h"

GravitationalField::GravitationalField(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	bigPlanet = new Planet();
	smallPlanetObject = new PlanetObject();
}

//destructor
GravitationalField::~GravitationalField()
{}

bool GravitationalField::Init()
{
	//BIG PLANET SETTING VARS
	bigPlanet->atmosphere = 150.f;
	bigPlanet->gravity = 9.806f;
	bigPlanet->mass = 50.f;
	bigPlanet->position = { SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5 };
	///speed and pos = 0

	//SMALL PLANET SETTING VARS
	smallPlanetObject->mass = 10.f;
	smallPlanetObject->position = { (SCREEN_WIDTH * 0.5) - 200, (SCREEN_HEIGHT * 0.5) + 180 };
	smallPlanetObject->speed = { 1.f, 1.f };

	return true;
}

//PreUpdate:
update_status GravitationalField::PreUpdate()
{

	return UPDATE_CONTINUE;
}

//Update: debug Camera
update_status GravitationalField::Update()
{
	if (App->verlet->bigPlanetEnabled == true)
	{
		DrawBigPlanet(bigPlanet);
	}

	if (App->verlet->smallPlanetEnabled == true)
	{
		DrawSmallPlanet(smallPlanetObject);
		Move(bigPlanet, smallPlanetObject);
		//set speed and then update the smallPlanet position: VERLET THKS :D
	}

	return UPDATE_CONTINUE;
}

//PostUpdate
update_status GravitationalField::PostUpdate()
{
	return UPDATE_CONTINUE;
}

//CleanUp
bool GravitationalField::CleanUp()
{
	delete bigPlanet;
	delete smallPlanetObject;

	return true;
}


//----------------------------


void GravitationalField::DrawBigPlanet(Planet* Earth)
{	
	App->renderer->DrawCircle(Earth->position.x, Earth->position.y, Earth->mass, 255, 255, 255, 255);
	App->renderer->DrawCircle(Earth->position.x, Earth->position.y, Earth->atmosphere, 255, 255, 255, 255);
}

void GravitationalField::DrawSmallPlanet(PlanetObject* Moon)
{
	App->renderer->DrawCircle(Moon->position.x, Moon->position.y, Moon->mass, 255, 255, 255, 255);
}

vector2 GravitationalField::Move(Planet* Earth, PlanetObject* Moon)
{
	float distance = Earth->position.x - Moon->position.x;
	float h = (Earth->position.y) - Moon->position.y;

	Moon->position.x = Moon->position.x + (2 * TIME) - (0.5 * (-9.8 - distance) * TIME * TIME);
	Moon->position.y = Moon->position.y + (2 * TIME) - (0.5 * (-9.8 - h) * TIME * TIME);
	LOG("PositionY: %f", Moon->position.y);

	return Moon->position;
}

Planet::Planet()
{}

PlanetObject::PlanetObject()
{}