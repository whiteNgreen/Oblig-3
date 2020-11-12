#pragma once
#include <conio.h>
#include <string>
#include <random>
#include <ctime>

#include "Password.h"
#include "AiBattleShip.h"

//  Player coordinates for battleship
int bsY;
int bsX;
int ship1Y;
int ship2Y;
int ship1X;
int ship2X;

std::vector <std::vector <char>> Board(6, std::vector<char>(6));
//  Checks state of the current vector
//  0 is Nothing there
//  1 is Hit
//  2 is Miss
//  3 is Ship at current
std::vector <std::vector <int>> BoardShip(6, std::vector<int>(6));
std::vector <char> column(6);
std::vector <int> row(6);
int numberOfHits;
int numberOfShots = 3;


int ShipPlacement(int a, int b) {
    std::uniform_int_distribution<> colRow{ a,b };
    return colRow(randomNumber::mersenne);
}

void HorizontalShip() {
    // X 1-4
    // Y 0-5
    ship1Y = ShipPlacement(0, 5);
    ship1X = ShipPlacement(1, 4);

    BoardShip[ship1Y].at(ship1X) = 3;
    BoardShip[ship1Y].at(ship1X - 1) = 3;
    BoardShip[ship1Y].at(ship1X + 1) = 3;
}
void VerticalShip() {
    // X 1-4
    // Y 0-5
    ship2Y = ShipPlacement(1, 4);
    ship2X = ShipPlacement(0, 5);
    while (!BoardShip[ship2Y].at(ship2X) == 3 && !BoardShip[ship2Y - 1].at(ship2X) == 3 && !BoardShip[ship2Y + 1].at(ship2X) == 3) {
        ship2Y = ShipPlacement(1, 4);
        ship2X = ShipPlacement(0, 5);
    }

    BoardShip[ship2Y].at(ship2X) = 3;
    BoardShip[ship2Y - 1].at(ship2X) = 3;
    BoardShip[ship2Y + 1].at(ship2X) = 3;
}

void BattleShip() {
    //BoardShip[0].at(0) = 3;
    numberOfHits = 0;
    numberOfShots = 3;
    bsY = 0;
    bsX = 0;

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            BoardShip[i].at(j) = 0;
        }
    }

    
    HorizontalShip();
    VerticalShip();

    do {
        system("cls");
        std::cout << "Choose Column(A-F) and Row(1-6)\nPress S to Shoot\n\n";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                Board[i].at(j) = ' ';
            }
            column.at(i) = char(i + 65);
            row.at(i) = 6 - i;
        }
        Board[bsY].at(bsX) = '*';
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                if (BoardShip[i].at(j) == 2) {
                    Board[i].at(j) = 'M';
                }
                else if (BoardShip[i].at(j) == 1) {
                    Board[i].at(j) = 'H';
                }
                
            }
        }


        //  Prints out board
        for (int i = 0; i < 6; i++) {
            std::cout << row.at(i);
            for (int j = 0; j < 6; j++) {
                std::cout << '|' << Board[i].at(j);
            }
            std::cout << "|\n";
        }
        std::cout << " -------------\n ";
        for (int i = 0; i < 6; i++) {
            std::cout << '|' << column.at(i);
        }
        std::cout << '|';
        std::cout << "\n";
        std::cout << "\n";
        //-----------

        std::cout << "Shots left: " << numberOfShots;
        std::cout << "\n";
        std::cout << "Ships Hit: " << numberOfHits;
        std::cout << "\n";
        
        /*std::cout <<char(ship1X + 65) << ' ' << 6 - ship1Y << '\n';
        std::cout <<char(ship2X + 65) << ' ' << 6 - ship2Y << '\n';*/


        if (numberOfShots == 0) {
            std::cout << "No more shots left\n";
            system("pause");
            return;
        }
        //  The Ai is not complete and not properly functioning. I have commented out both functions that use it
        //AiBattleShip();

        input = _getch();

        switch (input)
        {
        case'a':case'A':
            bsX = 0;
            break;
        case'b':case'B':
            bsX = 1;
            break;
        case'c':case'C':
            bsX = 2;
            break;
        case'd':case'D':
            bsX = 3;
            break;
        case'e':case'E':
            bsX = 4;
            break;
        case'f':case'F':
            bsX = 5;
            break;
        case'1':
            bsY = 5;
            break;
        case'2':
            bsY = 4;
            break;
        case'3':
            bsY = 3;
            break;
        case'4':
            bsY = 2;
            break;
        case'5':
            bsY = 1;
            break;
        case'6':
            bsY = 0;
            break;
        case's':case'S':
            if (BoardShip[bsY].at(bsX) == 2 || BoardShip[bsY].at(bsX) == 1) {
                numberOfShots--;
            }
            else if (BoardShip[bsY].at(bsX) == 3) {
                BoardShip[bsY].at(bsX) = 1;
                numberOfHits++;
                numberOfShots--;
            }
            else {
                BoardShip[bsY].at(bsX) = 2;
                numberOfShots--;
            }
            //  Function for AI shooting
            //AiAim();
            break;
        case'q':case'Q':
            return;
            break;
        default:
            break;
        }
    } while (true);
}
