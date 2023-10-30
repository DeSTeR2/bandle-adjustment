#include <iostream>
#include <stdio.h>
#include <Eigen/Dense>
#include <unsupported/Eigen/NumericalDiff>
#include <vector>

#include <GLFW/glfw3.h>

#include "Point2D.h"
#include "Point3D.h"
#include "Camera.h"

using namespace std;
using namespace Eigen;

#define _CRT_SECURE_NO_DEPRECATE
#define pb push_back
#define float double
#define endl '\n'

#pragma warning (disable : 4996)

const int wert = 1900, hor = 1000;

int numCamera, numPoints, numObservations;
vector<Point2D> D2Points, D2ProjectedPoints;
vector<Camera> Cameras;
vector<Point3D> D3Points;

bool inputParam() {
	if (freopen("input.txt", "r", stdin));
	else {
		cout << "ERROR: Cannot read the file" << endl;
		return false;
	}
	cout << "Read started" << endl;

	cin >> numCamera >> numPoints >> numObservations;
	for (int i = 0; i < numObservations; i++) {
		int camer, pointNum;
		float X, Y;
		cin >> camer >> pointNum >> X >> Y;
		Point2D point(camer, pointNum, X, Y);
		D2Points.push_back(point);
	}

	for (int i = 0; i < numCamera; i++) {
		vector<float> buff;
		for (int j = 0; j < 9; j++) {
			float a;
			cin >> a;
			buff.pb(a);
		}
		Point3D rot(buff[0], buff[1], buff[2]), pos(buff[3], buff[4], buff[5]);

		Camera camera(&rot, &pos, buff[6], buff[7], buff[8]);
		Cameras.pb(camera);
	}

	for (int i = 0; i < numPoints; i++) {
		vector<float> a;
		for (int j = 0; j < 3; j++) {
			float x;
			cin >> x;
			a.pb(x);
		}
		Point3D point(a[0], a[1], a[2], i);
		D3Points.pb(point);
	}
	fclose(stdin);
	return true;
}

void project3DPoint() {
	for (int i = 0; i < D2Points.size(); i++) {
		Point3D X = D3Points[D2Points[i].getPointNum()];
		Camera cam = Cameras[D2Points[i].getCamera()];

		Point3D cRotation = cam.getRotation(), cPosition = cam.getPosition();
		float f = cam.getF(), k1 = cam.getK1(), k2 = cam.getK2();

		Point3D P = cRotation * X + cPosition;
		Point3D p = (P * (-1)) / P.getZ();
		
		float rP = 1.0 + k1 * p.euclidianNorm() * p.euclidianNorm() + k2 * p.euclidianNorm() * p.euclidianNorm() * p.euclidianNorm() * p.euclidianNorm();

		Point3D p1 = p * (f * rP);

		D2ProjectedPoints.pb(D2Points[i]);

		D2ProjectedPoints[i].setX(p1.getX());
		D2ProjectedPoints[i].setY(p1.getY());
	}
}

float residual(int i) {
	return (D2ProjectedPoints[i] - D2Points[i]).euclidianNorm() * (D2ProjectedPoints[i] - D2Points[i]).euclidianNorm();
}

VectorXd computeJacError(int i) {
	VectorXd error(2);

	error(0) = D2ProjectedPoints[i].getX() - D2Points[i].getX();
	error(1) = D2ProjectedPoints[i].getY() - D2Points[i].getY();
	
	return error;
}

MatrixXf JacobiansLandmark() {
	float H = 1e-6;
	MatrixXf J(2*D2Points.size(), 3 * D2Points.size());

	for (int k = 0; k < D3Points.size(); k++) {
		for (int i = 0; i < 3; i++) {
			
			Vector3d xPlusH;
			xPlusH(0) = D3Points[k].getX();
			xPlusH(1) = D3Points[k].getX();
			xPlusH(2) = D3Points[k].getX();
			
			xPlusH(i) += H;
			
			VectorXd yPlusH = computeJacError(k);
			J.block<2, 1>(2 * k, 3 * k + i) = (yPlusH - computeJacError(k)) / H;
		}
	}

	return J;
}

MatrixXf JacobianPose() {
	int numPose = D2ProjectedPoints.size();
	int m = 2 * numPose;
	int n = m;
	MatrixXf J = MatrixXf::Identity(m, n);
	return J;
}

vector<MatrixXf> QRDecomposition(MatrixXf A) {
	const float cnt = 1e-6;
	
	HouseholderQR<MatrixXf> qr(A);
	MatrixXf Q = qr.householderQ();
	MatrixXf R = qr.matrixQR().triangularView<Upper>(); 

	Q *= (-1);
	R *= (-1);

	MatrixXf Q1(Q.rows(), Q.cols()), Q2(Q.rows(), Q.cols());
	Q1 *= 0;
	Q2 *= 0;
	
	for (int i = 0; i < A.cols(); i++) {
		for (int j = 0; j < Q.cols(); j++) {
			Q1(j, i) = Q(j, i);
		}
		
	}

	for (int i = A.cols(); i < Q.rows(); i++) {
		for(int j = 0; j<Q.cols();j++) {
			Q2(j, i - A.cols()) = Q(j, i);
		}
	}

	MatrixXf R1 = Q2.transpose() * A;

	for (int i = 0; i < R1.rows(); i++) {
		for (int j = 0; j < R1.cols(); j++) {
			if (R1(i, j) <= cnt) R1(i, j) = 0;
		}
	}

	/*cout << "A:" << endl << A << endl << endl;
	cout << "Q:" << endl << Q << endl << endl;
	cout << "R:" << endl << R << endl << endl;*/

	vector<MatrixXf> v;
	v.pb(Q1); v.pb(Q2); v.pb(R1);

	return v;
}


float toMin(MatrixXf Q2, float r, MatrixXf Jp, float delX) {
	Q2 = Q2.transpose();

	Vector2f A = Q2 * r + Q2 * Jp * delX;
	Point2D point(float(A(0)), float(A(1)));
	return point.euclidianNorm() * point.euclidianNorm();
}

void solver() {
	/*
	
		||Q2(t)r+Q2(t)Jp del(Xp)||^2 - Point2D 
	
	*/

	MatrixXf Jl = JacobiansLandmark();
	vector<MatrixXf> v = QRDecomposition(Jl);
}

int main() {


	if (inputParam() == true) {
		cout << "OK: Seccesfully read the file" << endl;
	}
	project3DPoint();

	GLFWwindow* window;


	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(wert, hor, "Hello World", NULL, NULL);
	if (!window)	
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	float num = 0;
	while (!glfwWindowShouldClose(window)) {
		int width, height;			
		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, width, 0, height, 0, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glPointSize(1); 

		glBegin(GL_POINTS); 

		float param = 100, offsetX = 2, offsetY = 2;
		for (int i = 0; i < D2ProjectedPoints.size(); i++) {
			if (D2ProjectedPoints[i].getCamera() == int(num)) {
					//				float X = ((1.0 / D2Points[i].getX()) + offsetX) * param + 30*(sqrt(abs(D2Points[i].getX()))), Y = ((1.0 / D2Points[i].getY()) + offsetY) * param + 30 * (sqrt(abs(D2Points[i].getY())));
				float X = (D2ProjectedPoints[i].getX()), Y = (D2ProjectedPoints[i].getY());
				X = X + 700;
				Y = Y + 500;
				glVertex2d(X, Y);

				X = (D2Points[i].getX()), Y = (D2Points[i].getY());
				X = X + 700;
				Y = Y + 500;
				glVertex2d(X, Y);


			}
		}

		glEnd(); // End drawing points

		glfwSwapBuffers(window);
		glfwPollEvents();

		num+=0.01;
		if (num >= numCamera) num -= numCamera;

		
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;



}