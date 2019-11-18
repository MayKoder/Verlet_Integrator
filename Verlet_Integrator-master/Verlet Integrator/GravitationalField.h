#ifndef _GRAVITATIONAL_FIELD_H_
#define _GRAVITATIONAL_FIELD_H_

#include "IntegratorFunctions.h"
#include "ModuleVerlet.h"
#include "p2List.h"
#include "IntegratorFunctions.h"
#include "Shape.h"


//calcula nueva po cogiendo actual sumando la velocidad por delta t (increment pos hacia ...)

#define GRAVITATIONAL_CONST 6.67 //blablabla ARREGLAR ^^

struct Point;
class Line;
class VerletIntegrator;

class Planet
{
public:

	float atmosphere = 0;
	float gravity = 0;
	float mass = 0;
	vector2 position = { 0, 0 };
	float speed = 0;

	Planet();
};

class PlanetObject
{
public:

	float speed = 0;
	float mass = 0;
	vector2 position = { 0, 0 };

	PlanetObject();
	void PrintPlanetObject(PlanetObject Moon);
	vector2 Move(Planet Earth, PlanetObject Moon);
	
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

public:
	Planet* bigPlanet;
	PlanetObject* smallPlanetObject;

};


#endif // !_GRAVITATIONAL_FIELD_H_





