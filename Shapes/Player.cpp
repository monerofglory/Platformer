#include "Player.h"

float playerX;
float playerY;

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