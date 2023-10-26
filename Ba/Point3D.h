#pragma once
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
};

