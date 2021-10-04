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

//Platforms and floor
vector<int> gameFloor = { 0, 0, windowX, 5 };
vector<int> platform1 = { 20, 55, 100, 20 };
vector<int> platform2 = { 200, 300, 100, 20 };
vector<int> platform3 = { 500, 355, 100, 20 };

//List of all platforms

vector<vector<int>> platforms = { platform1, platform2, platform3 };

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
	drawPlatform(gameFloor);
	drawAllPlatforms(platforms);
	drawPlayer(getPlayerX(), getPlayerY());
	//Flush to screen.
	glFlush();
}

void KeyPressed(unsigned char key, int x, int y) {
	if (key == 32) { //Space bar
		ReversePlayerDirection(false);
	}
	if (key == 'w') {
		if (!isPlayerJumping()) {
			setPlayerJumping();
		}
	}
}

bool checkIfPlayerUnder2(vector<int> p, vector<int> obj) {
	//First check if in the same x range
	if ((p.at(0) >= obj.at(0)) && (p.at(0) <= (obj.at(0) + obj.at(2)))) {
		//Correct X range
		if ((p.at(1)) <= (obj.at(1) + obj.at(3))) {
			//Player is below object
			if ((p.at(1) + playerHeight) < (obj.at(1))) {
				//But not completely below
				setPlayerY(obj.at(1) + obj.at(3));
				return true;
			}
		}
	}
}

bool checkIfPlayerUnder(vector<int> p, vector<int> obj) {
	bool xInside = false;
	bool yInside = false;

	int lX = obj.at(0); //Left X
	int rX = obj.at(0) + obj.at(2); //Right X
	int bY = obj.at(1); //Bottom Y
	int tY = obj.at(1) + obj.at(3); // Top Y
	//Check x bounds
	if ((p.at(0) >= lX) && (p.at(0) <= rX) ) {
		xInside = true;
		//printf("XTRUE");
	}
	//Check y bounds
	if ((p.at(1) >= bY) && (p.at(1) <= tY)){
		yInside = true;
		//printf("YTRUE");
	}

	//If both, then inside
	return xInside & yInside;

}

void checkCollisions() {
	//Get player positions
	int px = getPlayerX();
	int py = getPlayerY();
	vector<int> playerTop = { px, py + playerHeight, px + playerWidth, py + playerHeight };
	vector<int> playerBottom = { px, py, px + playerWidth, py};
	//Default collision to false
	setColliding(false);
	//Check collissions with other platforms
	for (int i = 0; i <= platforms.size() - 1; i++) {
		if (checkIfPlayerUnder(playerBottom, platforms.at(i))) {
			printf("setting y to %d", platforms.at(i).at(1));
			setPlayerY(platforms.at(i).at(1) + platforms.at(i).at(3));
			setColliding(true);
			printf("ONPLATFORM\n");
		}
	}
	//Check collision with floor
	if (checkIfPlayerUnder(playerBottom, gameFloor)) {
		setColliding(true);
		printf("ON FLOOR\n");
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
