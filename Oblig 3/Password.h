#pragma once
#include <iostream>
#include <vector>
#include <conio.h>
#include <fstream>
#include <string>

bool correctPassword;

std::string OriginalPassword = "ABCDHLPONM";
std::string buffer1 = "";
std::string buffer2 = "";
char input;
int x;
int y;
bool writeToFile = true;
bool showPassword;

std::vector <std::vector <char>> vPassword(4, std::vector<char>(4));

void ResetPassword() {
    std::string buffer1 = "";
    std::string buffer2 = "";
    std::fstream ResetPassword("PasswordFile.txt", std::ios::out);
    ResetPassword << OriginalPassword;
    ResetPassword.close();
    std::fstream Check("PasswordFile.txt", std::ios::in);
    std::getline(Check, buffer1);
    Check.close();
    std::cout << buffer1 << '\n';
    system("pause");
}
void WriteNewPassword() {
    x = 0;
    y = 0;
    std::string buffer1 = "";
    std::string buffer2 = "";

    std::fstream WriteTo("Buffer.txt", std::ios::out);
    WriteTo.close();

    std::fstream PasswordFile("PasswordFile.txt", std::ios::in);
    std::getline(PasswordFile, buffer1);
    PasswordFile.close();

    std::fstream ClearPassword("PasswordFile.txt", std::ios::out);
    ClearPassword.close();

    writeToFile = true;
    do {
        system("cls");
        std::cout << "WRITE A NEW PASSWORD\nPress E to Confirm the new password\n";
        std::cout << "Current Password: " << buffer1 << "\n\n";
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                vPassword[i].at(j) = char(65 + j + (i * 4));
            }
        }
        if (writeToFile) {
            std::fstream WriteTo("Buffer.txt", std::ios::out | std::ios::app);
            WriteTo << vPassword[y].at(x);
            WriteTo.close();
        }
        writeToFile = false;
        std::fstream WriteTo("Buffer.txt", std::ios::in);
        std::getline(WriteTo, buffer2);

        std::fstream OverWrite("PasswordFile.txt", std::ios::out);
        OverWrite << buffer2;
        OverWrite.close();

        vPassword[y].at(x) = '*';
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << vPassword[i].at(j) << ' ';
            }
            std::cout << '\n';
        }

        std::cout << "New Password: " << buffer2 << '\n';

        input = _getch();

        switch (input)
        {
        case'w':case'W':
            if (y != 0) {
                y--;
                writeToFile = true;
            }
            break;
        case's':case'S':
            if (y != 3) {
                y++;
                writeToFile = true;
            }
            break;
        case'd':case'D':
            if (x != 3) {
                x++;
                writeToFile = true;
            }
            break;
        case'a':case'A':
            if (x != 0) {
                x--;
                writeToFile = true;
            }
            break;
        case'q':case'Q':
            return;
            break;
        case'e':case'E':
            return;
            break;
        default:
            break;
        }
    } while (true);
}
void EnterPassword() {
    showPassword = false;
    x = 0;
    y = 0;
    std::string buffer1 = "";
    std::string buffer2 = "";

    std::fstream WriteTo("Buffer.txt", std::ios::out);
    WriteTo.close();

    std::fstream CurrentPasswordFile("PasswordFile.Txt", std::ios::in);
    std::getline(CurrentPasswordFile, buffer1);
    CurrentPasswordFile.close();

    writeToFile = true;
    do {
        system("cls");
        std::cout << "ENTER PASSWORD\nPress E to confirm\n";
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                vPassword[i].at(j) = char(65 + j + (i * 4));
            }
        }
        if (writeToFile) {
            std::fstream WriteTo("Buffer.txt", std::ios::out | std::ios::app);
            WriteTo << vPassword[y].at(x);
            WriteTo.close();
        }
        writeToFile = false;
        std::fstream WriteTo("Buffer.txt", std::ios::in);
        std::getline(WriteTo, buffer2);

        vPassword[y].at(x) = '*';
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << vPassword[i].at(j) << ' ';
            }
            std::cout << '\n';
        }
        std::cout << buffer2 << '\n';
        if (showPassword) {
            std::cout << buffer1 << '\n';
        }

        if (buffer2 == buffer1) {
            std::cout << "Correct password" << '\n';
            correctPassword = true;
            system("pause");
            return;
        }

        input = _getch();

        switch (input)
        {
        case'w':case'W':
            if (y != 0) {
                y--;
                writeToFile = true;
            }
            break;
        case's':case'S':
            if (y != 3) {
                y++;
                writeToFile = true;
            }
            break;
        case'd':case'D':
            if (x != 3) {
                x++;
                writeToFile = true;
            }
            break;
        case'a':case'A':
            if (x != 0) {
                x--;
                writeToFile = true;
            }
            break;
        case'q':case'Q':
            return;
            break;
        case'f':case'F':
            if (!showPassword) {
                showPassword = true;
                break;
            }
            else {
                showPassword = false;
            }
            break;
        case'e':case'E':
            if (buffer2 == buffer1) {
                std::cout << "Correct password" << '\n';
                system("pause");
                return;
                break;
            }
            else {
                x = 0;
                y = 0;
                writeToFile = true;
                std::cout << "Wrong Password\n";
                std::fstream ResetBuffer("Buffer.txt", std::ios::out);
                ResetBuffer.close();
                system("pause");
            }
            break;
        default:
            break;
        }
    } while (true);
}