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
	smallPlanetObject->position = { (SCREEN_WIDTH * 0.5) + 200, SCREEN_HEIGHT * 0.5 };
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
	//new position = raiz cuadrada de (G * masa) entre la distancia hasta el centro del cuerpo que genera la gravedad

	//Moon->position.x += 1.f;
	//Moon->position.y -= 1.f;

	vector2 distanceTo = { 0, 0 };
	distanceTo.x = (Moon->position.x - Earth->position.x) - ((Moon->mass * 0.5) + (Earth->mass * 0.5));
	distanceTo.y = (Moon->position.y - Earth->position.y) - ((Moon->mass * 0.5) + (Earth->mass * 0.5));
	//distanceTo returns distance between a bigPlanet and a smallPlanet

	//no es position, es speed CAMBIAR, MYTODO
	Moon->position.x = sqrt((G * Earth->mass) / ((Earth->mass * 0.5) + (Moon->mass * 0.5) + distanceTo.x));
	Moon->position.y = sqrt((G * Earth->mass) / ((Earth->mass * 0.5) + (Moon->mass * 0.5) + distanceTo.y));

	//Moon->position.x = (Moon->speed.x * Moon->speed.x) / 150;
	//Moon->position.y = (Moon->speed.y * Moon->speed.y) / 150;

	return Moon->position;
}

Planet::Planet()
{}

PlanetObject::PlanetObject()
{}