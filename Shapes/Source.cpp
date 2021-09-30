#include <GL/glut.h>
#include<iostream>
#include <stdlib.h>
#include <tuple>
#include <list>
#include "Player.h"

using namespace std;
int rx = 100, ry = 125;
int xCenter = 250, yCenter = 250;

void myinit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
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

void drawPlatform(float xpos, float ypos, float width, float height) {
	glColor3ub(255, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2i(xpos, ypos);
	glVertex2i(xpos + width, ypos);
	glVertex2i(xpos + width, ypos + height);
	glVertex2i(xpos, ypos + height);
	glEnd();
	glFlush();
}

void drawPlayer(float playerX, float playerY) {
	glColor3ub(0, 0, 255);
	glBegin(GL_QUADS);
	glVertex2i(playerX, playerY);
	glVertex2i(playerX + 10, playerY);
	glVertex2i(playerX + 10, playerY + 20);
	glVertex2i(playerX, playerY + 20);
	glEnd();
	glFlush();
}

void drawShape(list<float> shape) {
	glColor3ub(0.0,0.0, 1.0);
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
	drawPlatform(300, 300, 200, 100);
	drawPlayer(getPlayerX(), getPlayerY());
	glFlush();
}

void keyPressed(unsigned char key, int x, int y) {
	if (key == 'a') {
		updatePlayerPosition(getPlayerX() - 3, getPlayerY());
	}
	else if (key == 'd') {
		updatePlayerPosition(getPlayerX() + 3, getPlayerY());
	}
	display();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("User_Name");
	myinit();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPressed);
	glutMainLoop();
	return 0;
}
