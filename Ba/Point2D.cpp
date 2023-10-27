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

float Point2D::euclidianNorm() {
	return sqrt(this->x * this->x + this->y * this->y);
}

void Point2D::setX(float x) {
	this->x = x;
}
void Point2D::setY(float y) {
	this->y = y;
}

Point2D Point2D::operator+(Point2D obj) {
	float x = obj.getX() + this->getX();
	float y = obj.getY() + this->getY();

	Point2D res(this->getCamera(), this->getPointNum(), x, y);
	return res;
}

Point2D Point2D::operator-(Point2D obj) {
	float x = this->getX() - obj.getX();
	float y = this->getY() - obj.getY();

	Point2D res(this->getCamera(), this->getPointNum(), x, y);
	return res;
}

Point2D Point2D::operator*(Point2D obj) {
	float x = obj.getX() * this->getX();
	float y = obj.getY() * this->getY();

	Point2D res(this->getCamera(), this->getPointNum(), x, y);
	return res;
}

Point2D Point2D::operator/(Point2D obj) {
	float x = this->getX() / obj.getX();
	float y = this->getY() / obj.getY();

	Point2D res(this->getCamera(), this->getPointNum(), x, y);
	return res;
}

Point2D Point2D::operator+(float X) {
	float x = this->getX() + X;
	float y = this->getY() + X;

	Point2D res(this->getCamera(), this->getPointNum(), x, y);
	return res;
}

Point2D Point2D::operator-(float X) {
	float x = this->getX() - X;
	float y = this->getY() - X;

	Point2D res(this->getCamera(), this->getPointNum(), x, y);
	return res;
}

Point2D Point2D::operator*(float X) {
	float x = X * this->getX();
	float y = X * this->getY();

	Point2D res(this->getCamera(), this->getPointNum(), x, y);
	return res;
}

Point2D Point2D::operator/(float X) {
	float x = this->getX() / X;
	float y = this->getY() / X;

	Point2D res(this->getCamera(), this->getPointNum(), x, y);
	return res;
}