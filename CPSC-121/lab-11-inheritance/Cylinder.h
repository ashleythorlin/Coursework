#pragma once
#ifndef Cylinder_h
#define Cylinder_h
#include "GeometricalShape.h"
#include <math.h>
using namespace std;

class Cylinder : public GeometricalShape
{
private:
	double radius;
	double height;
public:
	Cylinder();
	Cylinder(double, double, int, int, int);
	double getRadius();
	double getHeight();
	void CylinderVolume();
};

Cylinder::Cylinder() : GeometricalShape()
{
	radius = 0;
	height = 0;
}

Cylinder::Cylinder(double h, double r, int x, int y, int z) : GeometricalShape(x, y, z)
{
	height = h;
	radius = r;
}

double Cylinder::getRadius()
{
	return radius;
}

double Cylinder::getHeight()
{
	return height;
}

void Cylinder::CylinderVolume()
{
	volume = 3.14 * (pow(radius, 2.0)) * height;
}

#endif