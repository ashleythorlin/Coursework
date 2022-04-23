// lab 11 inheritance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GeometricalShape.h"
#include "Sphere.h"
#include "RectangularBox.h"
#include "Cylinder.h"
using namespace std;

int main()
{
    //default
    cout << "===Creating Objects with default constructors!===" << endl;
    
    //sphere
    shared_ptr<Sphere> sphere1 = make_shared<Sphere>();
    sphere1->SphereVolume();
    cout << "Sphere Info:" << endl;
    cout << "The center coordinate is at X:" << sphere1->getX() << " Y:" << sphere1->getY() << " Z:" << sphere1->getZ() << endl;
    cout << "Dimensions - Radius: " << sphere1->getRadius() << endl;
    cout << "The Volume is " << sphere1->getVolume() << endl;
    
    //box
    shared_ptr<RectangularBox> box1 = make_shared<RectangularBox>();
    box1->BoxVolume();
    cout << "Rectangular Box Info:" << endl;
    cout << "The center coordinate is at X:" << box1->getX() << " Y:" << box1->getY() << " Z:" << box1->getZ() << endl;
    cout << "Dimensions - Height: " << box1->getHeight() << ", Length: " << box1->getLength() <<", Width: "<< box1->getWidth()<< endl;
    cout << "The Volume is " << box1->getVolume() << endl;

    //cylinder
    shared_ptr<Cylinder> cyl1 = make_shared<Cylinder>();
    cyl1->CylinderVolume();
    cout << "Cylinder Info:" << endl;
    cout << "The center coordinate is at X:" << cyl1->getX() << " Y:" << cyl1->getY() << " Z:" << cyl1->getZ() << endl;
    cout << "Dimensions - Height: " << cyl1->getHeight() << ", Radius: " << cyl1->getRadius() <<  endl;
    cout << "The Volume is " << cyl1->getVolume() << endl;
    
    cout << endl;

    //overloaded
    cout << "===Creating Objects with overloaded constructors!===" << endl;

    //sphere
    shared_ptr<Sphere> sphere2 = make_shared<Sphere>(3.5, 2, 2, 5);
    sphere2->SphereVolume();
    cout << "Sphere Info:" << endl;
    cout << "The center coordinate is at X:" << sphere2->getX() << " Y:" << sphere2->getY() << " Z:" << sphere2->getZ() << endl;
    cout << "Dimensions - Radius: " << sphere2->getRadius() << endl;
    cout << "The Volume is " << sphere2->getVolume() << endl;

    //box
    shared_ptr<RectangularBox> box2 = make_shared<RectangularBox>(2.5, 3.2, 1.5, 5, 0, -5);
    box2->BoxVolume();
    cout << "Rectangular Box Info:" << endl;
    cout << "The center coordinate is at X:" << box2->getX() << " Y:" << box2->getY() << " Z:" << box2->getZ() << endl;
    cout << "Dimensions - Height: " << box2->getHeight() << ", Length: " << box2->getLength() << ", Width: " << box2->getWidth() << endl;
    cout << "The Volume is " << box2->getVolume() << endl;

    shared_ptr<Cylinder> cyl2 = make_shared<Cylinder>(4.0, 1.75, 1, 1, 1);
    cyl2->CylinderVolume();
    cout << "Cylinder Info:" << endl;
    cout << "The center coordinate is at X:" << cyl2->getX() << " Y:" << cyl2->getY() << " Z:" << cyl2->getZ() << endl;
    cout << "Dimensions - Height: " << cyl2->getHeight() << ", Radius: " << cyl2->getRadius() << endl;
    cout << "The Volume is " << cyl2->getVolume() << endl;

    return 0;
}
