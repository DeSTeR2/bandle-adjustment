
#include "Camera.h"

Camera::Camera(Point3D* rotation,Point3D* position, float f, float k1, float k2) {
	this->rotation = rotation;
	this->position = position;
	this->f = f;
	this->k1 = k1;
	this->k2 = k2;
}