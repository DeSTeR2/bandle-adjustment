#pragma once
#include <iostream>

class Point3D
{
private:
	float x, y, z;
	int num;
public: 
	Point3D();
	Point3D(float x, float y, float z);
	Point3D(float x, float y, float z, int num);

	float getX();
	float getY();
	float getZ();
	int getNum();

	void setX(float x);
	void setY(float y);
	void setZ(float z);

	Point3D operator+(Point3D obj);
	Point3D operator*(Point3D obj);

	Point3D operator+(float X);
	Point3D operator*(float X);
	Point3D operator/(float X);

	float euclidianNorm();
};

