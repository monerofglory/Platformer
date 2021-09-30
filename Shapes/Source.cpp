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

//Function for drawing the platform.
//Takes in the current co-ordinates, and a width and height of the rectangle.
void drawPlatform(float xpos, float ypos, float width, float height) {
	glColor3ub(255, 0.0, 0.0); //Set colour
	glBegin(GL_QUADS);
	//Set vertices
	glVertex2i(xpos, ypos);
	glVertex2i(xpos + width, ypos);
	glVertex2i(xpos + width, ypos + height);
	glVertex2i(xpos, ypos + height);
	//Flush to screen.
	glEnd();
	glFlush();
}

//Function for drawing the player.
//Takes in the co-ordinates of their location.
void drawPlayer(float playerX, float playerY) {
	glColor3ub(0, 0, 255); //Set player colour.
	glBegin(GL_QUADS);
	//Set vertices. Where added numbers indicate player size.
	glVertex2i(playerX, playerY);
	glVertex2i(playerX + 10, playerY);
	glVertex2i(playerX + 10, playerY + 20);
	glVertex2i(playerX, playerY + 20);
	//Flush to screen.
	glEnd();
	glFlush();
}

void display()
{
	//Clear Screen
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2.0);
	//Draw platform and player.
	drawPlatform(300, 300, 200, 100);
	drawPlayer(getPlayerX(), getPlayerY());
	//Flush to screen.
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
