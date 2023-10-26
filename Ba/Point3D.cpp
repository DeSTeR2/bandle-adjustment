#include "Point3D.h"

Point3D::Point3D(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Point3D::Point3D(float x, float y, float z, int num) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->num = num;
}

float Point3D::getX() {
	return this->x;
}
float Point3D::getY() {
	return this->y;
}
float Point3D::getZ() {
	return this->z;
}
int Point3D::getNum() { 
	return this->num;
}