#include "Player.h"

float playerX;
float playerY;

//Update player position.
void updatePlayerPosition(float x, float y) {
	playerX = x;
	playerY = y;
}

float getPlayerX() {
	return playerX;
}

float getPlayerY() {
	return playerY;
}