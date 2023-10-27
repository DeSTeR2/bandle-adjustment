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

void Point3D::setX(float x) {
	this->x = x;
}
void Point3D::setY(float y) {
	this->y = y;
}
void Point3D::setZ(float z) {
	this->z = z;
}

Point3D Point3D::operator+(Point3D obj) {
	float x = obj.getX() + this->getX();
	float y = obj.getY() + this->getY();
	float z = obj.getZ() + this->getZ();
	
	Point3D res(x, y, z, this->getNum());
	return res;
}
Point3D Point3D::operator*(Point3D obj) {
	float x = obj.getX() * this->getX();
	float y = obj.getY() * this->getY();
	float z = obj.getZ() * this->getZ();

	Point3D res(x, y, z, this->getNum());
	return res;
}

Point3D Point3D::operator+(float X) {
	float x = X + this->getX();
	float y = X + this->getY();
	float z = X + this->getZ();

	Point3D res(x, y, z, this->getNum());
	return res;
}


Point3D Point3D::operator*(float X) {
	float x = X * this->getX();
	float y = X * this->getY();
	float z = X * this->getZ();

	Point3D res(x, y, z, this->getNum());
	return res;
}

Point3D Point3D::operator/(float X) {
	float x = this->getX() / X;
	float y = this->getY() / X;
	float z = this->getZ() / X;

	Point3D res(x, y, z, this->getNum());
	return res;
}


float Point3D::euclidianNorm() {
	return sqrt(this->x * this->x + this->y * this->y + this->z*this->z);
}