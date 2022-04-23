#pragma once
#ifndef RectangularBox_h
#define RectangularBox_h
#include "GeometricalShape.h"
using namespace std;

class RectangularBox : public GeometricalShape
{
private:
	double height, length, width;
public:
	RectangularBox();
	RectangularBox(double, double, double, int, int, int);
	double getHeight();
	double getLength();
	double getWidth();
	void BoxVolume();
};

RectangularBox::RectangularBox() : GeometricalShape()
{
	height = 0;
	length = 0;
	width = 0;
}

RectangularBox::RectangularBox(double h, double l, double w, int x, int y, int z) : GeometricalShape(x, y, z)
{
	height = h;
	length = l;
	width = w;
}

double RectangularBox::getHeight()
{
	return height;
}

double RectangularBox::getLength()
{
	return length;
}

double RectangularBox::getWidth()
{
	return width;
}

void RectangularBox::BoxVolume()
{
	volume = height * length * width;
}

#endif
