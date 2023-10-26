#pragma once
class Point2D {
private:
	int camera, pointNum;
	float x, y;

public:
	Point2D(int camera, int pointNum, float x, float y);		
	float getX();
	float getY();
	int getCamera();
	int getPointNum();
};
