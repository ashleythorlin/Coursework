#pragma once
#ifndef GeometricalShape_h
#define GeometricalShape_h
using namespace std;

class GeometricalShape
{
protected:
	int xPosition, yPosition, zPosition;
	double volume;
public:
	GeometricalShape();
	GeometricalShape(int, int, int);
	int getX();
	int getY();
	int getZ();
	void setVolume(double);
	double getVolume();
};

GeometricalShape::GeometricalShape()
{
	xPosition = 0;
	yPosition = 0;
	zPosition = 0;
	volume = 0.0;
}

GeometricalShape::GeometricalShape(int x, int y, int z)
{
	xPosition = x;
	yPosition = y;
	zPosition = z;
	volume = 0.0;
}

int GeometricalShape::getX()
{
	return xPosition;
}

int GeometricalShape::getY()
{
	return yPosition;
}

int GeometricalShape::getZ()
{
	return zPosition;
}

void GeometricalShape::setVolume(double v)
{
	volume = v;
}

double GeometricalShape::getVolume()
{
	return volume;
}

#endif
