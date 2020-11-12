// Oblig 3
#include <iostream>
#include <vector>
#include <conio.h>
#include <string>
#include <random>
#include <ctime>

#include "Password.h"
#include "BattleShip.h"
#include "AiBattleShip.h"

int main()
{
    EnterPassword();
    while (correctPassword) {
        
        system("cls");
        std::cout << "1. Change password\n2. Play Battleship\n3. Quit\n";

        input = _getch();
        switch (input)
        {
        case'1':
            WriteNewPassword();
            EnterPassword();
            break;
        case'2':
            BattleShip();
            break;
        case'3':
            return 0;
            //correctPass = false;
            break;
        default:
            break;
        }
    }
    return 0;
}


