#include <iostream>
#include <stdio.h>
#include <Eigen/Dense>
#include <vector>

#include <GLFW/glfw3.h>


#include "Point2D.h"
#include "Point3D.h"
#include "Camera.h"

using namespace std;

#define _CRT_SECURE_NO_DEPRECATE
#define pb push_back
#define float double
#define endl '\n'
#pragma warning (disable : 4996)

const int wert = 1980, hor = 1080;

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
			float x;
			cin >> x;
			a.pb(x);
		}
		Point3D point(a[0], a[1], a[2]);
		D3Points.pb(point);
	}
	fclose(stdin);
	return true;
}

void drawDot(GLFWwindow* window) {
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

		glPointSize(1); // Set the point size

		glBegin(GL_POINTS); // Begin drawing points

		int num = 2;
		float param = 100, offsetX=2, offsetY = 2;
		for (int i = 0; i < D2Points.size(); i++) {
			//if (D2Points[i].getPointNum() == num) {
//				float X = ((1.0 / D2Points[i].getX()) + offsetX) * param + 30*(sqrt(abs(D2Points[i].getX()))), Y = ((1.0 / D2Points[i].getY()) + offsetY) * param + 30 * (sqrt(abs(D2Points[i].getY())));
				float X = (D2Points[i].getX()) + 700, Y = (D2Points[i].getY())+ 500;

				glVertex2d(X, Y);
			//}
		}


		//glVertex2f(width / 2, height / 2); // Set the position of the point at the center of the window
		glEnd(); // End drawing points

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}



int main() {
	if (inputParam() == true) {
		cout << "OK: Seccesfully read the file" << endl;
	}

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(wert, hor, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		drawDot(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;


}