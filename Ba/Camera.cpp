
#include "Camera.h"

Camera::Camera(Point3D* rotation,Point3D* position, float f, float k1, float k2) {
	this->rotation = rotation;
	this->position = position;
	this->f = f;
	this->k1 = k1;
	this->k2 = k2;
}

float Camera::getF() {
	return this->f;
}
float Camera::getK1() {
	return this->k1;
}
float Camera::getK2() {
	return this->k2;
}
Point3D Camera::getPosition() {
	return *this->position;
}
Point3D Camera::getRotation() {
	return *this->rotation;
}