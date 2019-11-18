#ifndef _GRAVITATIONAL_FIELD_H_
#define _GRAVITATIONAL_FIELD_H_

#include "IntegratorFunctions.h"
#include "ModuleVerlet.h"
#include "p2List.h"
#include "IntegratorFunctions.h"
#include "Shape.h"


//calcula nueva po cogiendo actual sumando la velocidad por delta t (increment pos hacia ...)

#define G 2 //6.67 //blablabla ARREGLAR, MYTODO ^^
#define TIME 0.4

struct Point;
class Line;
class VerletIntegrator;

class Planet
{
public:

	float atmosphere = 0;
	float gravity = 0;
	float mass = 0; //planet radius
	vector2 position = { 0, 0 };
	float speed = 0;

	Planet();
};

class PlanetObject
{
public:

	vector2 speed = { 0, 0 };
	float mass = 0;
	vector2 position = { 0, 0 };

	PlanetObject();	
};

//-----------------------------------------------

class GravitationalField : public Module
{
public:

	GravitationalField(Application* app, bool start_enabled = true);
	~GravitationalField();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void DrawBigPlanet(Planet* Earth);
	void DrawSmallPlanet(PlanetObject* Moon);

public:
	Planet* bigPlanet;
	PlanetObject* smallPlanetObject;
	vector2 Move(Planet* Earth, PlanetObject* Moon);

};


#endif // !_GRAVITATIONAL_FIELD_H_





