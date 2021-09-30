#pragma once
#include <string>

float getPlayerX();
float getPlayerY();
void ReversePlayerDirection(bool overrule);
void updatePlayerPosition(int dT);
void setPlayerX(float x);
void setPlayerY(float y);
void setColliding(bool t);
bool isPlayerJumping();
void setPlayerJumping();