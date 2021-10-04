#include <GL/glut.h>
#include<iostream>
#include <stdlib.h>
#include <tuple>
#include <list>
#include <vector>
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


bool previousTop = false;

//Platforms and floor
vector<int> gameFloor = { 0, 0, windowX, 8 };
vector<int> platform1 = { 20, 75, 100, 25 };
vector<int> platform2 = { 90, 175, 100, 25 };
vector<int> platform3 = { 500, 355, 100, 25 };

//List of all platforms
vector<vector<int>> platforms = { platform1, platform2, platform3 };

void myinit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, windowX, 0.0, windowY);
}

void setPixel(GLint x, GLint y)
{
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	glEnd();
}

//Function for drawing the platform.
//Takes in the current co-ordinates, and a width and height of the rectangle.
void drawPlatform(vector<int> coords) {
	testCounter++;
	glColor3ub(255, 0.0, 0.0); //Set colour
	glBegin(GL_QUADS);
	//Set vertices
	glVertex2i(coords.at(0), coords.at(1));
	glVertex2i(coords.at(0) + coords.at(2), coords.at(1));
	glVertex2i(coords.at(0) + coords.at(2), coords.at(1) + coords.at(3));
	glVertex2i(coords.at(0), coords.at(1) + coords.at(3));
	//Flush to screen.
	glEnd();
	glFlush();
}

//Function for drawing ALL platforms.
void drawAllPlatforms(vector<vector<int>> platforms) {
	for (int i = 0; i <= platforms.size() - 1; i++) {
		drawPlatform(platforms.at(i));
	}
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
	drawPlayer(getPlayerX(), getPlayerY());
	drawPlatform(gameFloor);
	drawAllPlatforms(platforms);
	//Flush to screen.
	glFlush();
}

void KeyPressed(unsigned char key, int x, int y) {
	if (key == 32) { //Space bar
		previousTop = false;
		ReversePlayerDirection(false);
	}
	if (key == 'w') {
		if ((!isPlayerJumping()) && (isPlayerOnFloor())) {
			previousTop = false;
			setPlayerJumping();
		}
	}
}


bool checkIfPlayerInsideVertical(vector<int> p, vector<int> obj) {
	bool inside = false;

	int lX = obj.at(0); //Left X
	int rX = obj.at(0) + obj.at(2); //Right X
	int bY = obj.at(1); //Bottom Y
	int tY = obj.at(1) + obj.at(3); // Top Y
	//Check x bounds
	inside = ((p.at(0) >= lX) && (p.at(0) <= rX));
	//Check y bounds
	inside = inside & ((p.at(1) >= bY) && (p.at(1) <= tY));
	//If both, then inside
	return inside;
}

bool checkIfPlayerInsideHorizontal(vector<int> p, vector<int> obj) {
	bool inside = false;

	int lX = obj.at(0); //Left X
	int rX = obj.at(0) + obj.at(2); //Right X
	int bY = obj.at(1); //Bottom Y
	int tY = obj.at(1) + obj.at(3); // Top Y
	//Check x bounds
	inside = ((p.at(0) >= lX) && (p.at(0) <= rX));
	//Check y bounds
	inside = inside & ((p.at(1) >= bY) && (p.at(1) <= tY));
	//Check x bounds
	inside = inside & ((p.at(2) >= lX) && (p.at(2) <= rX));
	//Check y bounds
	inside = inside & ((p.at(3) >= bY) && (p.at(3) <= tY));
	//If both, then inside
	return inside;
}

void checkCollisions() {
	//Get player positions
	int px = getPlayerX();
	int py = getPlayerY();
	vector<int> playerTop = { px, py + playerHeight, px + playerWidth, py + playerHeight };
	vector<int> playerBottom = { px, py, px + playerWidth, py};
	vector<int> playerLeft = { px, py, px, py + playerHeight };
	vector<int> playerRight = { px + playerWidth, py, px + playerWidth, py + playerHeight };
	//Default collision to false
	setColliding("none", false);
	//Check collissions with other platforms
	for (int i = 0; i <= platforms.size() - 1; i++) {

		if (checkIfPlayerInsideHorizontal(playerTop, platforms.at(i))) {
			//If player bounces into the bottom of a platform
			setColliding("top", true);
			setPlayerY(platforms.at(i).at(1) - playerHeight);
			previousTop = true;
			printf("TOP\n");
		}
		else if (checkIfPlayerInsideHorizontal(playerBottom, platforms.at(i))) {
			if (!previousTop) {
				setPlayerY(platforms.at(i).at(1) + platforms.at(i).at(3));
				setColliding("bottom", true);
				printf("BOTTOM\n");
			}
		}
		else if ((checkIfPlayerInsideVertical(playerLeft, platforms.at(i))) || (checkIfPlayerInsideVertical(playerRight, platforms.at(i))) ) {
			//Check if still on a platform
			//if (!checkIfPlayerInsideVertical(playerBottom, platforms.at(i))) {
			//	printf("SIDE\n");
			//	setColliding("side", true);
			//}
			if (isPlayerJumping()) {
				setColliding("side", true);
			}
			previousTop = false;
		}
	
	}
	//Check collision with floor
	if (checkIfPlayerInsideVertical(playerBottom, gameFloor)) {
		setColliding("bottom", true);
		setPlayerY(gameFloor.at(1) + gameFloor.at(3));
	}
}


void checkPlayerPositions() {
	if (getPlayerX() >= windowX - playerWidth) {
		ReversePlayerDirection(true);
	}
	if (getPlayerX() <= 0) {
		ReversePlayerDirection(true);
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
		//Check collisions
		if ((getPlayerFramesSinceJump() == 0) || (getPlayerFramesSinceJump() > 10)) {
			checkCollisions();
		}
		startTime = currentTime;
		display();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(windowX, windowY);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("User_Name");
	myinit();
	glutDisplayFunc(display);
	glutIdleFunc(update);
	glutKeyboardFunc(KeyPressed);
	glutMainLoop();
	return 0;
}
