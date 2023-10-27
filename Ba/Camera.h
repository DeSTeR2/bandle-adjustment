#pragma once
#include "Point3D.h"

class Camera
{
private:
	float  f, k1, k2;
	Point3D* position;
	Point3D* rotation;
public:
	Camera(Point3D* rotation, Point3D* position, float f, float k1, float k2);

	float getF();
	float getK1();
	float getK2();
	Point3D getPosition();
	Point3D getRotation();
};

