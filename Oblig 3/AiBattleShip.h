#pragma once
#include <conio.h>
#include <string>
#include <random>
#include <ctime>
//#include "BattleShip.h"

int aiY;
int aiX;
int temp;
int aiShip1Y;
int aiShip2Y;
int aiShip1X;
int aiShip2X;

int aiNumberOfShots = 3;
bool aiaHit;
bool aiPrevShotHit;
std::vector <std::vector <char>> AiBoard(6, std::vector<char>(6));
//  Checks state of the current vector
//  0 is Nothing there
//  1 is Hit
//  2 is Miss
//  3 is Ship at current
std::vector <std::vector <int>> AiBoardShip(6, std::vector<int>(6));


namespace randomNumber {
	std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
}
int AiShipPlacement(int a, int b) {
	std::uniform_int_distribution<> colRow{ a,b };
	return colRow(randomNumber::mersenne);
}

void AiHorizontalShip();
void AiHorizontalShip() {
	// X 1-4
	// Y 0-5
	aiShip1Y = AiShipPlacement(0, 5);
	aiShip1X = AiShipPlacement(1, 4);

	AiBoardShip[aiShip1Y].at(aiShip1X) = 3;
	AiBoardShip[aiShip1Y].at(aiShip1X - 1) = 3;
	AiBoardShip[aiShip1Y].at(aiShip1X + 1) = 3;
}
void AiVerticalShip();
void AiVerticalShip() {
	// X 1-4
	// Y 0-5
	aiShip2Y = AiShipPlacement(1, 4);
	aiShip2X = AiShipPlacement(0, 5);
	
	while (aiShip2Y == aiShip1Y || aiShip2Y == (aiShip1Y - 1) || aiShip2Y == (aiShip1Y + 1)){
		aiShip2Y = AiShipPlacement(1, 4);
		aiShip2X = AiShipPlacement(0, 5);
	}

	AiBoardShip[aiShip2Y].at(aiShip2X) = 3;
	AiBoardShip[aiShip2Y - 1].at(aiShip2X) = 3;
	AiBoardShip[aiShip2Y + 1].at(aiShip2X) = 3;
}

void AiAim() {
	if (aiaHit) {
		if (aiPrevShotHit) {
			temp = AiShipPlacement(0, 3);
			if (temp == 0) {
				if (!aiY == 0) { aiY--; }
				else { aiY++; }
			}
			if (temp == 1) {
				if (!aiY == 5) { aiY++; }
				else { aiY--; }
			}
			if (temp == 2) {
				if (!aiX == 0) { aiX--; }
				else { aiX++; }
			}
			if (temp == 3) {
				if (!aiX == 5) { aiX++; }
				else { aiX--; }
			}
		}
		if (!aiPrevShotHit) {
			if (temp == 0) {
				if (!aiY == 5) { 
					aiY++; 
					if (!aiY == 5) { 
						aiY++; 
					}
				}
				else { 
					aiY++;
					if (aiX == 5) {
						aiX--;
					}
					else {
						aiX++;
					}
				}
			}
			if (temp == 1) {
				if (!aiY == 0) { 
					aiY--; 
					if (!aiY == 0) {
						aiY--;
					}
				}
			}
			if (temp == 2) {
				if (!aiX == 0) { aiX--; }
				else { aiX++; }
			}
			if (temp == 3) {
				if (!aiX == 5) { aiX++; }
				else { aiX--; }
			}
		}
	}
	else {
		aiY = AiShipPlacement(0, 5);
		aiX = AiShipPlacement(0, 5);

		while (AiBoardShip[aiY].at(aiX) == 1 || AiBoardShip[aiY].at(aiX) == 2) {
			aiY = AiShipPlacement(0, 5);
			aiX = AiShipPlacement(0, 5);
		}	
	}
	if (AiBoardShip[aiY].at(aiX) == 2 || AiBoardShip[aiY].at(aiX) == 1) {
		aiNumberOfShots--;
	}
	else if (AiBoardShip[aiY].at(aiX) == 3) {
		AiBoardShip[aiY].at(aiX) = 1;
		aiNumberOfShots--;
		aiaHit = true;
		aiPrevShotHit = true;
	}
	else {
		aiPrevShotHit = false;
		AiBoardShip[aiY].at(aiX) = 2;
		aiNumberOfShots--;
	}
}

void AiBattleShip() {
	aiaHit = false;
	aiPrevShotHit = false;
	aiNumberOfShots = 3;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			AiBoardShip[i].at(j) = 0;
		}
	}

	AiHorizontalShip();
	AiVerticalShip();
	do {
		//system("cls");
		std::cout << "\n\nAi Gameplay\n\n";
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				AiBoard[i].at(j) = ' ';
			}
		}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				if (AiBoardShip[i].at(j) == 2) {
					AiBoard[i].at(j) = 'M';
				}
				else if (AiBoardShip[i].at(j) == 1) {
					AiBoard[i].at(j) = 'H';
				}
				
			}
		}
		
		
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				std::cout << '|';
				std::cout << AiBoard[i].at(j) << '|';
			}
			std::cout << '\n';
		}

		std::cout << temp << '\n';
		std::cout << aiPrevShotHit << '\n';

		std::cout << "Ai shots left: " << aiNumberOfShots << '\n';
		//AiAim();
		
		return;
	} while (true);
}