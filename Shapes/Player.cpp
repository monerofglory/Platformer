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
float jumpHeight = 150;
bool jumpCollisionChange = false;

bool floorCollide = false;
bool topCollide = false;
bool sideCollide = false;

void ReversePlayerDirection(bool overrule) {
	//if ((!jumping) && (floorCollide)) {
	//	Left = !Left;
	//}
	//else if (overrule) {
	//	Left = !Left;
	//}
	Left = !Left;
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
		if (floorCollide) {
			jumping = false;
			jumpCollisionChange = false;
			framesSinceJump = 0;
		}
		if (framesSinceJump == 60) {
			playerY = startY;
			jumping = false;
			jumpCollisionChange = false;
			framesSinceJump = 0;
		}
		
	}
	//Gravity
	if (!floorCollide) {
		playerY -= 6;
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

void setColliding(string surface, bool t) {
	if (surface == "none") {
		floorCollide = t; 
		topCollide = t;
		sideCollide = t;
	}
	else if (surface == "top") { 
		topCollide = t; 
		if (!jumpCollisionChange) {
			framesSinceJump = 60 - framesSinceJump;
			jumpCollisionChange = true;
		}
	}
	else if (surface == "bottom") { floorCollide = t; }
	else if (surface == "side") { ReversePlayerDirection(true); }
}

bool isPlayerJumping() {
	return jumping;
}

void setPlayerJumping() {
	jumping = true;
	framesSinceJump = 1;
	setColliding("none", false);
	startY = playerY;
}

float getPlayerFramesSinceJump() {
	return framesSinceJump;
}

bool isPlayerOnFloor() {
	return floorCollide;
}
