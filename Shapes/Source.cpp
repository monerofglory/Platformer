#include <GL/glut.h>
#include<iostream>
#include <stdlib.h>
#include <tuple>
#include <list>

using namespace std;
int rx = 100, ry = 125;
int xCenter = 250, yCenter = 250;

void myinit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void setPixel(GLint x, GLint y)
{
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	glEnd();
}

void drawShape(list<float> shape) {
	glColor3ub(rand() % 255, rand() % 255, rand() % 255);
	glBegin(GL_LINE_LOOP);
	while (shape.size() > 0) {
		float x = shape.front();
		shape.pop_front();
		float y = shape.front();
		shape.pop_front();
		glVertex2i(x, y);
	}
	glEnd();
	glFlush();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
	//Shape
	list<float> triangle;
	//Points of triangle
	triangle.push_back(25);
	triangle.push_back(25);
	triangle.push_back(78);
	triangle.push_back(78);
	triangle.push_back(50);
	triangle.push_back(101);
	drawShape(triangle);
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("User_Name");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
