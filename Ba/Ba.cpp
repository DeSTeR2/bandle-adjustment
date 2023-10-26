#include <iostream>
#include <stdio.h>
#include <Eigen/Dense>
#include <vector>

#include "Point2D.h"
#include "Point3D.h"
#include "Camera.h"

using namespace std;

#define _CRT_SECURE_NO_DEPRECATE
#define pb push_back
#define endl '\n'
#pragma warning (disable : 4996)

int numCamera, numPoints, numObservations;
vector<Point2D> D2Points;
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
	}

	for (int i = 0; i < numPoints; i++) {
		vector<float> a;
		for (int j = 0; j < 3; j++) {
			int x;
			cin >> x;
			a.pb(x);
		}
		Point3D point(a[0], a[1], a[2]);
		D3Points.pb(point);
	}
	fclose(stdin);
	return true;
}

int main() {
	if (inputParam() == true) {
		cout << "OK: Seccesfully read the file" << endl;
	}

}
/*
	49 - cameras  441 - camera parametres 
	7776 - points 

	31845 - st
	55613 - end 

	23768

*/