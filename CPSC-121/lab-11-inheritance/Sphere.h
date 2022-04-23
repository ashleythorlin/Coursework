#pragma once
#ifndef Sphere_h
#define Sphere_h
#include "GeometricalShape.h"
#include <math.h>
using namespace std;

class Sphere : public GeometricalShape
{
private:
	double radius;
public:
	Sphere();
	Sphere(double, int, int, int);
	double getRadius();
	void SphereVolume();
};

Sphere::Sphere() : GeometricalShape()
{
	radius = 0;
}

Sphere::Sphere(double r, int x, int y, int z) : GeometricalShape(x, y, z)
{
	radius = r;
}

double Sphere::getRadius()
{
	return radius;
}

void Sphere::SphereVolume()
{
	volume = (4.0 / 3.0) * 3.14 * (pow(radius, 3.0));
}

#endif
