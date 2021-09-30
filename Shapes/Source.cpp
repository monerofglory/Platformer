#include <GL/glut.h>
#include<iostream>
#include <stdlib.h>
#include <tuple>
#include <list>
#include <string>

#include "Player.h"

using namespace std;
//Graphical variables
int windowX = 640, windowY = 480;
//Player dimensions
int playerWidth = 10;
int playerHeight = 20;

int rx = 100, ry = 125;
int xCenter = 250, yCenter = 250;

float testCounter = 0;

int framerate = 60;
int deltaTime = 0;
int startTime = 0;
int currentTime = 0;

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
	testCounter++;
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
	glVertex2i(playerX + playerWidth, playerY);
	glVertex2i(playerX + playerWidth, playerY + playerHeight);
	glVertex2i(playerX, playerY + playerHeight);
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
	drawPlatform(20, 25 + testCounter, 100, 10);
	drawPlayer(getPlayerX(), getPlayerY());
	//Flush to screen.
	glFlush();
}

void KeyPressed(unsigned char key, int x, int y) {
	if (key == 32) {
		ReversePlayerDirection();
	}
	if (key == 'w') {
		if (!isPlayerJumping()) {
			setPlayerJumping();
		}
	}
}

void checkPlayerPositions() {
	//cout << getPlayerX() << "\n";
	if (getPlayerX() >= windowX - playerWidth) {
		ReversePlayerDirection();
	}
	if (getPlayerX() <= 0) {
		ReversePlayerDirection();
	}
}

void update() {
	//Get timings
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = currentTime - startTime;
	if (deltaTime >= (1000 / framerate)) {
		//1 frame workload
		//Update player position
		updatePlayerPosition(deltaTime);
		//Check player positions
		checkPlayerPositions();
		startTime = currentTime;
		display();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("User_Name");
	myinit();
	glutDisplayFunc(display);
	glutIdleFunc(update);
	glutKeyboardFunc(KeyPressed);
	glutMainLoop();
	return 0;
}
