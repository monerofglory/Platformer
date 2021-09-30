#define _USE_MATH_DEFINES

#include <string>
#include <cmath>
#include <iostream>

#include "Player.h"


using namespace std;

bool jumping = false;
float framesSinceJump = 0;

//Location
float playerX = 50;
float playerY = 50;

//Movement
bool Left = false; //Capital L due to ambiguity.
float walkingSpeed = 100;
float startY;
float jumpHeight = 25;

void ReversePlayerDirection() {
	if (!jumping) {
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
			jumping = false;
			framesSinceJump = 0;
		}
	}
}

float getPlayerX() {
	return playerX;
}

float getPlayerY() {
	return playerY;
}

bool isPlayerJumping() {
	return jumping;
}

void setPlayerJumping() {
	jumping = true;
	startY = playerY;
}