#pragma once
#include <string>

float getPlayerX();
float getPlayerY();
void ReversePlayerDirection();
void updatePlayerPosition(int dT);
bool isPlayerJumping();
void setPlayerJumping();