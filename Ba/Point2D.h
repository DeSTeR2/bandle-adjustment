#pragma once
#include <iostream>

class Point2D {
private:
	int camera, pointNum;
	float x, y;

public:
	Point2D(float x, float y);
	Point2D(int camera, int pointNum, float x, float y);		
	float getX();
	float getY();
	int getCamera();
	int getPointNum();
	
	float euclidianNorm();

	void setX(float x);
	void setY(float y);
	
	Point2D operator+(Point2D obj);
	Point2D operator-(Point2D obj);
	Point2D operator/(Point2D obj);
	Point2D operator*(Point2D obj);

	Point2D operator+(float X);
	Point2D operator-(float X);
	Point2D operator*(float X);
	Point2D operator/(float X);

};
