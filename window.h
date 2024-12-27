//
// Created by wacos on 4/11/2024.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
using namespace std;
#ifndef MINESWEEPER_WELCOMEWINDOW_H
#define MINESWEEPER_WELCOMEWINDOW_H
struct Read {
    Read();
    int row;
    int col;
    int height;
    int width;
    string row_temp;
    string col_temp;
    int num_mines;
    int num_flags;
    bool num_flags_neg;
    int getRow();
    int getCol();
    int getNumMines();
};
Read::Read(){
    ifstream config("files/config.cfg");
    string num_mines_temp;
    getline(config, col_temp);
    col = stoi(col_temp);
    getline(config, row_temp);
    row = stoi(row_temp);
    getline(config, num_mines_temp);
    num_mines = stoi(num_mines_temp);
    num_flags = num_mines;
    bool num_flags_neg = false;
    height = (row * 32) + 100;
    width = col * 32;
}

struct CreateWindow{
    Read p;
    int colCount;
    int rowCount;
    CreateWindow();
    sf::RenderWindow* Create();
};

CreateWindow::CreateWindow() {
}
sf::RenderWindow *CreateWindow::Create() {
      sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(p.width, p.height), "Minesweeper");
      return window;
}


#endif //MINESWEEPER_WELCOMEWINDOW_H
