#include "Point2D.h"
Point2D::Point2D(int camera, int pointNum, float x, float y) {
	this->camera = camera;
	this->pointNum = pointNum;
	this->x = x;
	this->y = y;
}



float Point2D::getX() {
	return this->x;
}
float Point2D::getY() {
	return this->y;
}
int Point2D::getCamera() {
	return this->camera;
}
int Point2D::getPointNum() {
	return this->pointNum;
}
