#define _USE_MATH_DEFINES

#include <string>
#include <cmath>
#include <iostream>

#include "Player.h"


using namespace std;

bool jumping = false;
float framesSinceJump = 0;

//Location
float playerX = 300;
float playerY = 400;

//Movement
bool Left = false; //Capital L due to ambiguity.
float walkingSpeed = 250;
float startY;
float jumpHeight = 100;
bool onFloor = false;

void ReversePlayerDirection(bool overrule) {
	if ((!jumping) && (onFloor)) {
		Left = !Left;
	}
	else if (overrule) {
		Left = !Left;
	}
}

//Update player position.
void updatePlayerPosition(int dT) {
	if (Left) {
		playerX = playerX - (walkingSpeed * dT / 1000);
	}
	if (!Left) {
		playerX = playerX + (walkingSpeed * dT / 1000);
	}
	if (jumping) {
		playerY = startY + (sinf((framesSinceJump / 60) * M_PI) * jumpHeight);
		framesSinceJump++;
		if (framesSinceJump == 60) {
			playerY = startY;
			jumping = false;
			framesSinceJump = 0;
		}
	}
	//Gravity
	if (!onFloor) {
		playerY -= 3;
	}
}

float getPlayerX() {
	return playerX;
}

float getPlayerY() {
	return playerY;
}

void setPlayerX(float x) {
	playerX = x;
}

void setPlayerY(float y) {
	playerY = y;
}

void setColliding(bool t) {
	onFloor = t;
}

bool isPlayerJumping() {
	return jumping;
}

void setPlayerJumping() {
	jumping = true;
	startY = playerY;
}
