//
// Created by wacos on 4/11/2024.
//
#include "window.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <chrono>
#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H
Read p;
struct cell{
    bool hasBomb = false;
    bool beenClicked = false;
    bool beenRClicked = false;
    string mine_nearby = "hello";
    int location = 0;
    int revealCount = 1;
    bool reveal = false;
    bool alrRevealed = false;
    sf::Texture temp_text;
    sf::Sprite temp;
    int flag_mine_count = p.num_mines;
    map<int, string> numbers;
    cell(map<string,string> &files);
    bool getHasBomb();
    void setBomb(map<int,cell*> &cells);
    void setNum(map<int, cell *> &cells);
    void setCorners(map<int,cell*> &cells);
    void setLeftEdge(map<int,cell*> &cells);
    void setTopEdge(map<int,cell*> &cells);
    void setBottomEdge(map<int,cell*> &cells);
    void setRightEdge(map<int,cell*> &cells);
    void setRest(map<int,cell*> &cells);
    void revealNearby(map<int, cell *> &cells);
    void setHasBombT();
    bool inCellBounds(int mousex, int mousey, map<string,string> &files, sf::RenderWindow *window, string side);
    void setSprHid(sf::Sprite spr, sf::Texture txt);
    void setBeenClicked();
    void setBeenRClicked();
    bool getBeenClicked();
    bool getBeenRClicked();
    void setRevealReached();
    void setAlrRevealed();
    bool getReveal();
    bool getAlrRevealed();
    void drawHCells(map<int,cell*> &cells, map<string,string> &files, sf::RenderWindow *window);
    void drawCurrCells(sf::RenderWindow *window, map<string,string> &files, int count, map<int,cell*> &cells, bool paused, bool leaderboard);
};
cell::cell(map<string,string> &files){
    sf::Texture temp_text;
    temp_text.loadFromFile(files["t_hidden"]);
    sf::Sprite temp;
    temp.setTexture(temp_text);
};
void cell::setBomb(map<int,cell*> &cells) {
    vector<int> used_cells;
    map<int, int> used;
    int temp;
    for (int i = 0; i<p.num_mines; i++){
        int random = rand() % (p.col * p.row) - 1;
        if(i > 0) {
            int size_after = used.size() + 1;
            used.emplace(random, random);
            if(used.size() < size_after){
                    while(used.size() < size_after ){
                        random = rand() % (p.col * p.row) - 1;
                        used.emplace(random, random);
                }
            }
        }
        else{
            used.emplace(random, random);
        }
        cells[random]->setHasBombT();
    }
}
void cell::setCorners(map<int, cell *> &cells) {
    int zero_num = 0;
    //cells[0]
    if (cells[1]->getHasBomb()){
        zero_num++;
    }
    if (cells[p.col]->getHasBomb()){
        zero_num++;
    }
    if (cells[p.col + 1]->getHasBomb()){
        zero_num++;
    }
    if (zero_num != 0) {
        numbers[0] = to_string(zero_num);
    }
    else{
        numbers[0] = "zero";
    }
    int t_r = 0;
    if (cells[p.col-2]->getHasBomb()){
        t_r++;
    }
    if (cells[(p.col*2)-1]->getHasBomb()){
        t_r++;
    }
    if (cells[(p.col*2)-2]->getHasBomb()){
        t_r++;
    }
    if (t_r != 0) {
        numbers[p.col - 1] = to_string(t_r);
    }
    else{
        numbers[p.col - 1] = "zero";
    }
    int b_l = 0;
    if (cells[(p.col * (p.row -1)) + 1]->getHasBomb()){
        b_l++;
    }
    if (cells[(p.col * (p.row - 1)) - (p.col)]->getHasBomb()){
        b_l++;
    }
    if (cells[(p.col * (p.row - 1)) - (p.col-1)]->getHasBomb()){
        b_l++;
    }
    if (b_l != 0) {
        numbers[p.col*(p.row-1)] = to_string(b_l);
    }
    else{
        numbers[p.col*(p.row-1)] = "zero";
    }
    int b_r = 0;
    if (cells[(p.col * p.row) - 2]->getHasBomb()){
        b_r++;
    }
    if (cells[(p.col * (p.row -1)) - 1]->getHasBomb()){
        b_r++;
    }
    if (cells[(p.col * (p.row -1)) - 2]->getHasBomb()){
        b_r++;
    }
    if (b_r != 0) {
        numbers[(p.col * p.row) - 1] = to_string(b_r);
    }
    else{
        numbers[(p.col * p.row) - 1] = "zero";
    }
}
//set left edge
void cell::setLeftEdge(map<int, cell *> &cells) {
    for (int i = 1; i< (p.row - 1); i++){
        int num = 0;
        if(cells[(p.col * i) - p.col]->getHasBomb()){
            num++;
        }
        if(cells[(p.col * i) - (p.col - 1)]->getHasBomb()){
            num++;
        }
        if(cells[(p.col * i) + 1]->getHasBomb()){
            num++;
        }
        if(cells[(p.col * i) + p.col]->getHasBomb()){
            num++;
        }
        if(cells[(p.col * i) + (p.col + 1)]->getHasBomb()){
            num++;
        }
        if (num != 0){
            numbers[(p.col * i)] = to_string(num);
        }
        else{
            numbers[(p.col * i)] = "zero";
        }
    }
}
//set top edge
void cell::setTopEdge(map<int, cell *> &cells) {
    for (int i = 1; i< (p.col - 1); i++){
        int num = 0;
        if (cells[i - 1]->getHasBomb()){
            num++;
        }
        if (cells[i + 1]->getHasBomb()){
            num++;
        }
        if (cells[i + (p.col - 1)]->getHasBomb()){
            num++;
        }
        if (cells[i + p.col]->getHasBomb()){
            num++;
        }
        if (cells[i + (p.col + 1)]->getHasBomb()){
            num++;
        }
        if (num != 0){
            numbers[i] = to_string(num);
        }
        else{
            numbers[i] = "zero";
        }
    }
}
//set botton edge
void cell::setBottomEdge(map<int, cell *> &cells) {
    for (int i = ((p.col * p.row) - (p.col - 1)); i < ((p.col * p.row) - 1); i++){
        int num = 0;
        if (cells[i - (p.col + 1)]->getHasBomb()){
            num++;
        }
        if (cells[i - (p.col)]->getHasBomb()){
            num++;
        }
        if (cells[i - (p.col - 1)]->getHasBomb()){
            num++;
        }
        if (cells[i - 1]->getHasBomb()){
            num++;
        }
        if (cells[i + 1]->getHasBomb()){
            num++;
        }
        if (num != 0){
            numbers[i] = to_string(num);
        }
        else{
            numbers[i] = "zero";
        }
    }
}
//set right edge
void cell::setRightEdge(map<int, cell *> &cells) {
    for (int i = 1; i < (p.row - 1); i++){
        int num = 0;
        if (cells[(i * p.col) + (p.col - 2)]->getHasBomb()){
            num++;
        }
        if (cells[(i * p.col) - 1]->getHasBomb()){
            num++;
        }
        if (cells[(i * p.col) - 2]->getHasBomb()){
            num++;
        }
        if (cells[((i+1) * p.col) + (p.col - 2)]->getHasBomb()){
            num++;
        }
        if (cells[((i+1) * p.col) + (p.col - 1)]->getHasBomb()){
            num++;
        }
        if (num != 0){
            numbers[(i * p.col) + (p.col - 1)] = to_string(num);
        }
        else{
            numbers[(i * p.col) + (p.col - 1)] = "zero";
        }
    }
}
void cell::setRest(map<int, cell *> &cells) {
    //(p.col * y) + x
    for (int y = 1; y < (p.row - 1); y++){
        for (int x = 1; x < (p.col - 1); x++){
            int num = 0;
            if (cells[((p.col * y) + x) - (p.col - 1)]->getHasBomb()){
                num++;
            }
            if (cells[((p.col * y) + x) - p.col]->getHasBomb()){
                num++;
            }
            if (cells[((p.col * y) + x) - (p.col + 1)]->getHasBomb()){
                num++;
            }
            if (cells[((p.col * y) + x) - 1]->getHasBomb()){
                num++;
            }
            if (cells[((p.col * y) + x) + 1]->getHasBomb()){
                num++;
            }
            if (cells[((p.col * y) + x) + (p.col - 1)]->getHasBomb()){
                num++;
            }
            if (cells[((p.col * y) + x) + p.col]->getHasBomb()){
                num++;
            }
            if (cells[((p.col * y) + x) + (p.col + 1)]->getHasBomb()){
                num++;
            }
            if (num != 0){
                numbers[((p.col * y) + x)] = to_string(num);
            }
            else{
                numbers[((p.col * y) + x)] = "zero";
            }
        }
    }
}
void cell::setNum(map<int, cell *> &cells) {
    setCorners(cells);
    setLeftEdge(cells);
    setTopEdge(cells);
    setBottomEdge(cells);
    setRightEdge(cells);
    setRest(cells);
    for (auto &iter : numbers){
        cells[iter.first]->mine_nearby = iter.second;
    }
}
void cell::revealNearby(map<int, cell *> &cells) {
    revealCount ++;
    //cout << location << "location"<< endl;
        if ((location < (p.col - 1) && (location > 0)) || (((location % p.col) == 0) && (location != 0) && (location != (p.col*(p.row-1)))) || (((location % p.col) == (p.col - 1)) && (location != p.col - 1) && (location != ((p.col * p.row) -1))) || (location > (p.col * (p.row - 1)) && location < ((p.col * p.row)-1))){
//            cout << "edges" << endl;
//            if ((location < (p.col - 1) && (location > 0))){
//                cout << "op 1" << endl;
//            }
//            else if ((((location % p.col) == 0) && (location != 0) && (location != (p.col*(p.row-1))))){
//                cout << "op 2" << endl;
//            }
//            else if ((((location % p.col) == (p.col - 1)) && (location != p.col - 1) && (location != ((p.col * p.row) -1)))){
//                cout << "op 3" << endl;
//            }
//            else{
//                cout << "op 4" << endl;
//            }
            //edges
            if ((location < (p.col - 1) && location > 0)){
                // << "one" << endl;
                    cells[location - 1]->setBeenClicked();
                    cells[location + 1]->setBeenClicked();
                    cells[location + (p.col - 1)]->setBeenClicked();
                    cells[location + p.col]->setBeenClicked();
                    cells[location + (p.col + 1)]->setBeenClicked();
            }
            else if ((location % p.col) == 0){
                // << "two" << endl;
                    cells[location - p.col]->setBeenClicked();
                    cells[location - (p.col - 1)]->setBeenClicked();
                    cells[location + 1]->setBeenClicked();
                    cells[location + p.col]->setBeenClicked();
                    cells[location + (p.col + 1)]->setBeenClicked();
            }
            else if ((location % p.col) == (p.col - 1)){
                // << "three" << endl;
                    cells[location - p.col]->setBeenClicked();
                    cells[location - 1]->setBeenClicked();
                    cells[location - (p.col + 1)]->setBeenClicked();
                    cells[location + p.col]->setBeenClicked();
                    cells[(location) + (p.col - 1)]->setBeenClicked();
            }
            else{
                // << "four" << endl;
                    cells[location - (p.col + 1)]->setBeenClicked();
                    cells[location - (p.col)]->setBeenClicked();
                    cells[location - (p.col - 1)]->setBeenClicked();
                    cells[location - 1]->setBeenClicked();
                    cells[location + 1]->setBeenClicked();
            }
        }
        //corners
        else if (location == 0 || location == (p.col - 1) || location == p.col*(p.row-1) || location == (p.col * p.row) - 1){ //change back to else if
            // << "corners" << endl;
                if (location == 0) {
                    //<<"daasss" << endl;
                    cells[1]->setBeenClicked();
                    cells[p.col]->setBeenClicked();
                    cells[p.col + 1]->setBeenClicked();
                }
                else if (location == (p.col - 1)) {
                    // << "eidid" << endl;
                    cells[p.col - 2]->setBeenClicked();
                    cells[(p.col * 2) - 1]->setBeenClicked();
                    cells[(p.col * 2) - 2]->setBeenClicked();
                }
                else if (location == p.col*(p.row-1)) {
                    // << "helor dkdsk" << endl;
                    cells[(p.col * (p.row - 1)) + 1]->setBeenClicked();
                    cells[(p.col * (p.row - 1)) - (p.col)]->setBeenClicked();
                    cells[(p.col * (p.row - 1)) - (p.col - 1)]->setBeenClicked();
                }
                else {
                    // << "dkmdf" << endl;
                    cells[(p.col * p.row) - 2]->setBeenClicked();
                    cells[(p.col * (p.row - 1)) - 1]->setBeenClicked();
                    cells[(p.col * (p.row - 1)) - 2]->setBeenClicked();
                }
            }
        else{
            // << "else" << endl;
            cells[(location - (p.col - 1))]->setBeenClicked();
            cells[(location - p.col)]->setBeenClicked();
            cells[(location - (p.col + 1))]->setBeenClicked();
            cells[location - 1]->setBeenClicked();
            cells[(location) + 1]->setBeenClicked();
            cells[location + (p.col - 1)]->setBeenClicked();
            cells[location + p.col]->setBeenClicked();
            cells[location + (p.col + 1)]->setBeenClicked();
        }
}
void cell::setSprHid(sf::Sprite spr, sf::Texture txt) {
    temp = spr;
    temp.setTexture(txt);
}
bool cell::getHasBomb() {
    return hasBomb;
}
void cell::setHasBombT() {
    hasBomb = true;
}
void cell::setBeenClicked() {
    beenClicked = true;
}
void cell::setBeenRClicked() {
    beenRClicked = true;
}
bool cell::getBeenClicked() {
    return beenClicked;
}
bool cell::getBeenRClicked() {
    return beenRClicked;
}
void cell::setRevealReached() {
    reveal = true;
}
void cell::setAlrRevealed() {
    alrRevealed = true;
}
bool cell::getReveal() {
    return reveal;
}
bool cell::getAlrRevealed() {
    return alrRevealed;
}
void cell::drawHCells(map<int,cell*> &cells, map<string,string> &files, sf::RenderWindow *window) {
    int temp_counter =0;
    for (int y = 0; y < p.row; y++) {
        for (int x = 0; x < p.col; x++) {
            sf::Texture hidden;
            hidden.loadFromFile(files["t_hidden"]);
            sf::Sprite hidden_spr;
            hidden_spr.setTexture(hidden);
            hidden_spr.setPosition((x * 32), (y * 32));
            cells[temp_counter]->setSprHid(hidden_spr, hidden);
            cells[temp_counter]->location = temp_counter;
            window->draw(hidden_spr);
            temp_counter++;
        }
    }
}
bool cell::inCellBounds(int mousex, int mousey, map<string,string> &files, sf::RenderWindow *window, string side) {
/*    sf::Texture hidden;
    hidden.loadFromFile(files["t_hidden"]);
    sf::Sprite hidden_spr;
    hidden_spr.setTexture(hidden);*/
    if (temp.getGlobalBounds().contains(mousex, mousey) && side == "left" && !getBeenRClicked()){
        sf::Texture revealed;
        revealed.loadFromFile(files["t_revealed"]);
        sf::Sprite revealed_spr;
        revealed_spr.setTexture(revealed);
        revealed_spr.setPosition(temp.getPosition().x, temp.getPosition().y);
        //temp.setColor(sf::Color(0, 255, 0, 255));
        temp_text = revealed;
        temp = revealed_spr;
        temp.setTexture(temp_text);
        window->draw(revealed_spr);
        setBeenClicked();
        return true;
    }
    else if (temp.getGlobalBounds().contains(mousex, mousey) && side == "right" && !getBeenClicked() && !getBeenRClicked()){
        sf::Texture flag;
        flag.loadFromFile(files["flag"]);
        sf::Sprite flag_spr;
        flag_spr.setTexture(flag);
        flag_spr.setPosition(temp.getPosition().x, temp.getPosition().y);
        //temp.setColor(sf::Color(0, 255, 0, 255));
        temp_text = flag;
        temp = flag_spr;
        temp.setTexture(temp_text);
        window->draw(flag_spr);
        beenRClicked = !beenRClicked;
        if (p.num_flags >= 1 && !p.num_flags_neg) {
            p.num_flags--;
        }
        else if (p.num_flags_neg){
            p.num_flags++;
        }
        if(p.num_flags == 0){
            p.num_flags_neg = !p.num_flags_neg;
        }
/*        else if(p.num_flags_neg && p.num_flags_neg >= 0){
            p.num_flags++;
        }*/
        return true;
    }
    else if (temp.getGlobalBounds().contains(mousex, mousey) && side == "right" && !getBeenClicked() && getBeenRClicked()){
        sf::Texture hidden;
        hidden.loadFromFile(files["t_hidden"]);
        sf::Sprite hidden_spr;
        hidden_spr.setTexture(hidden);
        hidden_spr.setPosition(temp.getPosition().x, temp.getPosition().y);
        //temp.setColor(sf::Color(0, 255, 0, 255));
        temp_text = hidden;
        temp = hidden_spr;
        temp.setTexture(temp_text);
        window->draw(hidden_spr);
        beenRClicked = !beenRClicked;
//        if (p.num_flags >= 1 && !p.num_flags_neg) {
//            p.num_flags++;
//        }
//        else if (p.num_flags_neg && p.num_flags >= 1){
//            p.num_flags--;
//            p.num_flags_neg = !p.num_flags_neg;
//        }
        if(p.num_flags == 0 && p.num_flags_neg){
            p.num_flags_neg = !p.num_flags_neg;
            //cout << p.num_flags_neg;
        }
        if (p.num_flags >= 0 && !p.num_flags_neg) {
            p.num_flags++;
        }
        else if (p.num_flags_neg){
            p.num_flags--;
        }
        if(p.num_flags == 0){
            p.num_flags_neg = !p.num_flags_neg;
        }


            return true;
    }
    else{
        return false;
    }
}
void cell::drawCurrCells(sf::RenderWindow *window, map<string,string> &files, int count, map<int,cell*> &cells, bool paused, bool leaderboard ) {
    if (paused || leaderboard){
        //ccout << "here mr leaderboard" << endl;
        // << "just here paused" << endl;
        sf::Texture revealed;
        revealed.loadFromFile(files["t_revealed"]);
        sf::Sprite revealed_spr;
        revealed_spr.setTexture(revealed);
        revealed_spr.setPosition(temp.getPosition().x, temp.getPosition().y);
        window->draw(revealed_spr);
    }
else if (!getBeenClicked() && !getBeenRClicked()) {
    //cout << "neither" << endl;
    sf::Texture hidden;
    hidden.loadFromFile(files["t_hidden"]);
    sf::Sprite hidden_spr;
    hidden_spr.setTexture(hidden);
    hidden_spr.setPosition(temp.getPosition().x, temp.getPosition().y);
    window->draw(hidden_spr);
}
else if (getBeenClicked() && !getBeenRClicked()){
    //cout << "left click" << endl;
    sf::Texture num;
    sf::Texture click;
    if (mine_nearby == "zero"){
        //<< "also here" << endl;
        click.loadFromFile(files["t_revealed"]);
        sf::Sprite click_spr;
        click_spr.setTexture(click);
        click_spr.setPosition(temp.getPosition().x, temp.getPosition().y);
        //set mines around to been clicked
        setRevealReached();
        // << "its reveal nearby" << endl;
        revealNearby(cells);
        window->draw(click_spr);
    }
    else{
        // << "else" << endl;
        click.loadFromFile(files["t_revealed"]);
        sf::Sprite click_spr;
        click_spr.setTexture(click);
        click_spr.setPosition(temp.getPosition().x, temp.getPosition().y);
        window->draw(click_spr);
        num.loadFromFile(files[mine_nearby]);
        sf::Sprite num_spr;
        num_spr.setTexture(num);
        num_spr.setPosition(temp.getPosition().x, temp.getPosition().y);
        window->draw(num_spr);
    }
/*    visible.loadFromFile(files["t_revealed"]);
    sf::Sprite visible_spr;
    visible_spr.setTexture(visible);
    visible_spr.setPosition(temp.getPosition().x, temp.getPosition().y);
    window->draw(visible_spr);*/
}
else if (!getBeenClicked() && getBeenRClicked()){
    //cout << "right click" << endl;
    sf::Texture hidden;
    hidden.loadFromFile(files["t_hidden"]);
    sf::Sprite hidden_spr;
    hidden_spr.setTexture(hidden);
    hidden_spr.setPosition(temp.getPosition().x, temp.getPosition().y);
    window->draw(hidden_spr);
    sf::Texture flag;
    flag.loadFromFile(files["flag"]);
    sf::Sprite flag_spr;
    flag_spr.setTexture(flag);
    flag_spr.setPosition(temp.getPosition().x, temp.getPosition().y);
    window->draw(flag_spr);
}
/*    cout << temp.getTexture() << endl;
    cout << temp.getPosition().x << "tempx" << endl;
    cout << temp.getPosition().y << "tempy" << endl;*/
}
struct game {
    game(sf::RenderWindow *window);
    int tot_mines = (p.col * p.row) - p.num_mines;
    bool win = false;
    bool lose = false;
    bool happyClicked = false;
    bool debugClicked = false;
    bool leaderboardClicked = false;
    bool pause_playClicked = false;
    sf::Sprite happy;
    sf::Sprite dead;
    sf::Sprite debug;
    sf::Sprite leaderboard;
    sf::Sprite pause_play;
    map<string , bool> clicked;
    map<string, sf::Sprite> spr;
    map<int,cell*> setBoard(sf::RenderWindow *window, map<string, string>& files);
    void reDraw(sf::RenderWindow *window, map<int, cell*>& cells, map<string,string>& files, string arr[]);
    void happyButton(sf::RenderWindow *window, map<string,string>& files);
    void debugButton(sf::RenderWindow *window, map<string,string>& files,  map<int, cell*>& cells);
    void pause_playButton(sf::RenderWindow *window, map<string,string>& files);
    void leaderboardButton(sf::RenderWindow *window, map<string,string>&files);
    void counter(sf::RenderWindow *window, map<string,string>&files);
    void counterChanged(sf::RenderWindow *window, map<std::string, std::string> &files);
    void setTimer(sf::RenderWindow *window, map<string,string>&files);
    void timerChanged(sf::RenderWindow *window, map<std::string, std::string> &files, string m0, string m1, string s0, string s1);
    string inButtonBounds(int mousex, int mousey);
    void debugBombs(sf::RenderWindow *window, map<int,cell*> &cells, map<string,string>& files);
};
game::game(sf::RenderWindow *window) {}
void game::timerChanged(sf::RenderWindow *window, map<std::string, std::string> &files, std::string m0, std::string m1,
                        std::string s0, std::string s1) {
    sf::Texture timer1;
    sf::Texture timer2;
    sf::Texture timer3;
    sf::Texture timer4;
    sf::Sprite pos4;
    sf::Sprite pos3;
    sf::Sprite pos2;
    sf::Sprite pos1;
    timer1.loadFromFile(files["digits"], sf::IntRect(stoi(m0) * 21,0,21,42));
    timer2.loadFromFile(files["digits"], sf::IntRect(stoi(m1) * 21,0,21,42));
    timer3.loadFromFile(files["digits"], sf::IntRect(stoi(s0) * 21,0,21,42));
    timer4.loadFromFile(files["digits"], sf::IntRect(stoi(s1) * 21,0,21,42));
    pos4.setTexture(timer4);
    pos3.setTexture(timer3);
    pos2.setTexture(timer2);
    pos1.setTexture(timer1);
    int temp = 0;
    pos1.setPosition((temp * 21)+((p.col * 32) - 97),32*(p.row+0.5)+16);
    temp++;
    pos2.setPosition((temp * 21)+((p.col * 32) - 97),32*(p.row+0.5)+16);
    temp++;
    pos3.setPosition((temp * 21)+((p.col * 32) - 97),32*(p.row+0.5)+16);
    temp++;
    pos4.setPosition((temp * 21)+((p.col * 32) - 97),32*(p.row+0.5)+16);
    window->draw(pos1);
    window->draw(pos2);
    window->draw(pos3);
    window->draw(pos4);
}
void game::debugBombs(sf::RenderWindow *window, map<int,cell*> &cells, map<string,string>& files) {
    int temp = 1;
    //cout << "debug bombs" << endl;
    for(auto &iter : cells){
        if (iter.second->getHasBomb()){
//            cout << temp << endl;
            sf::Texture bomb;
            bomb.loadFromFile(files["mine"]);
            sf::Sprite bomb_spr;
            bomb_spr.setTexture(bomb);
            bomb_spr.setPosition((iter.first % p.col)*32, (iter.first/ p.col)*32);
            temp++;
            window->draw(bomb_spr);
        }
        else{
            sf::Texture hidden;
            hidden.loadFromFile(files["t_hidden"]);
            sf::Sprite hidden_spr;
            hidden_spr.setTexture(hidden);
            hidden_spr.setPosition((iter.first % p.col)*32, (iter.first/ p.col)*32);
            temp++;
            window->draw(hidden_spr);
        }
    }
}
void game::happyButton(sf::RenderWindow *window, map<std::string, std::string> &files) {
    if (!lose && !win) {
        sf::Texture happy_face;
        happy_face.loadFromFile(files["f_happy"]);
        sf::Sprite happy_spr;
        happy_spr.setTexture(happy_face);
        happy_spr.setPosition(((p.col / 2.0) * 32) - 32, 32 * (p.row + 0.5));
        happy = happy_spr;
        clicked.emplace("happy", happyClicked);
        spr["happy"] = happy_spr;
        window->draw(happy_spr);
    }
    else if (lose){
        sf::Texture dead_f;
        dead_f.loadFromFile(files["f_lose"]);
        sf::Sprite dead_spr;
        dead_spr.setTexture(dead_f);
        dead_spr.setPosition(((p.col / 2.0) * 32) - 32, 32 * (p.row + 0.5));
        dead = dead_spr;
        clicked.emplace("lose", happyClicked);
        spr["lose"] = dead_spr;
        window->draw(dead_spr);
    }
}
void game::debugButton(sf::RenderWindow *window, map<std::string, std::string> &files, map<int, cell*>& cells) {
    if (!clicked["debug"]) {
        sf::Texture debug_txt;
        debug_txt.loadFromFile(files["debug"]);
        sf::Sprite debug_spr;
        debug_spr.setTexture(debug_txt);
        debug_spr.setPosition((p.col * 32) - 304, 32 * (p.row + 0.5));
        debug = debug_spr;
        spr["debug"] = debug_spr;
        debugClicked = false;
        clicked["debug"] = debugClicked;
        window->draw(debug_spr);
    }
    else if (clicked["debug"]){
        // << "here in debug" << endl;
        sf::Texture debug_txt;
        debug_txt.loadFromFile(files["debug"]);
        sf::Sprite debug_spr;
        debug_spr.setTexture(debug_txt);
        debug_spr.setPosition((p.col*32)-304, 32*(p.row + 0.5));
        debug = debug_spr;
        spr["debug"] = debug_spr;
        debugClicked = true;
        clicked["debug"] = debugClicked;
        window->draw(debug_spr);
        debugBombs(window,cells, files);
    }
}
void game::pause_playButton(sf::RenderWindow *window, map<std::string, std::string> &files) {
    if(!clicked["pause"]) {
//        cout << "false" << endl;
        sf::Texture pause;
        pause.loadFromFile(files["pause"]);
        sf::Sprite pause_spr;
        pause_spr.setTexture(pause);
        pause_spr.setPosition((p.col * 32) - 240, 32 * (p.row + 0.5));
        pause_play = pause_spr;
        spr["pause"] = pause_spr;
        pause_playClicked = false;
        clicked["pause"] = pause_playClicked;
        window->draw(pause_spr);
    }
    else{
//        cout << "true" << endl;
        sf::Texture play;
        play.loadFromFile(files["play"]);
        sf::Sprite play_spr;
        play_spr.setTexture(play);
        play_spr.setPosition((p.col * 32) - 240, 32 * (p.row + 0.5));
        pause_play = play_spr;
        spr["pause"] = play_spr;
        pause_playClicked = true;
        //clicked["play"] = pause_playClicked;
        window->draw(play_spr);
    }
}
void game::leaderboardButton(sf::RenderWindow *window, map<std::string, std::string> &files) {
    if (clicked["leaderboard"]) {
        sf::Texture leaderboard;
        leaderboard.loadFromFile(files["leaderboard"]);
        sf::Sprite leaderboard_spr;
        leaderboard_spr.setTexture(leaderboard);
        leaderboard_spr.setPosition((p.col * 32) - 176, 32 * (p.row + 0.5));
        spr["leaderboard"] = leaderboard_spr;
        leaderboardClicked = true;
        window->draw(leaderboard_spr);
    }
    else{
        leaderboardClicked = false;
        sf::Texture leaderboard;
        leaderboard.loadFromFile(files["leaderboard"]);
        sf::Sprite leaderboard_spr;
        leaderboard_spr.setTexture(leaderboard);
        leaderboard_spr.setPosition((p.col * 32) - 176, 32 * (p.row + 0.5));
        spr["leaderboard"] = leaderboard_spr;
        //clicked["leaderboard"] = leaderboardClicked;
        window->draw(leaderboard_spr);
    }
}
void game::counter(sf::RenderWindow *window, map<std::string, std::string> &files) {
    //cout << "here" << endl;
    string mines = to_string(p.num_mines);
    //cout << p.num_mines << endl;
    int x = 0;
    int y = 0;
    int curr_pos = mines.length();
    if (curr_pos == 3){
        curr_pos = 2;
    }
    string three_s;
    try {
        //cout << "before x" << endl;
        three_s = mines.substr(curr_pos, 1);
        if(three_s == ""){
            throw x;
        }
    }
    catch (int x){
        //cout << "x" << endl;
//        cout << "here hr" << endl;
        try {
            three_s = mines.substr((curr_pos - 1, 1));
            curr_pos = 1;
            if (three_s ==""){
                throw y;
            }
        }
        catch (int y){
            // << "y" << endl;
            three_s = mines;
        }
    }
//    cout << curr_pos << "before"<< endl;
    curr_pos -= 1;
//    cout << curr_pos << "after" << endl;
    int three = stoi(three_s);
    sf::Texture counter3;
    counter3.loadFromFile(files["digits"], sf::IntRect(three*21, 0, 21, 42));
    sf::Sprite counter3_spr;
    counter3_spr.setTexture(counter3);
    counter3_spr.setPosition(32+(21*2), (32*(p.row+0.5)+16));
    window->draw(counter3_spr);
    if (mines.length() > 1) {
        string two_s;
        two_s = mines.substr(curr_pos, 1);
//    cout << curr_pos << endl;
//    cout << two_s << endl;
        int two = stoi(two_s);
        sf::Texture counter2;
        counter2.loadFromFile(files["digits"], sf::IntRect(two * 21, 0, 21, 42));
        sf::Sprite counter2_spr;
        counter2_spr.setTexture(counter2);
        counter2_spr.setPosition(32 + 21, (32 * (p.row + 0.5) + 16));
        window->draw(counter2_spr);
        curr_pos -= 1;
        sf::Texture counter1;
        if (curr_pos >= 0) {
            string one_s;
            one_s = mines.substr(curr_pos, 1);
            int one = stoi(one_s);
            counter1.loadFromFile(files["digits"], sf::IntRect(one * 21, 0, 21, 42));
        } else {
            counter1.loadFromFile(files["digits"], sf::IntRect(0, 0, 21, 42));
        }
        sf::Sprite counter1_spr;
        counter1_spr.setTexture(counter1);
        counter1_spr.setPosition(32, (32 * (p.row + 0.5) + 16));
        window->draw(counter1_spr);
    }
    else{
        sf::Texture counter2;
        counter2.loadFromFile(files["digits"], sf::IntRect(0 * 21, 0, 21, 42));
        sf::Sprite counter2_spr;
        counter2_spr.setTexture(counter2);
        counter2_spr.setPosition(32 + 21, (32 * (p.row + 0.5) + 16));
        window->draw(counter2_spr);
        sf::Texture counter1;
        counter1.loadFromFile(files["digits"], sf::IntRect(0, 0, 21, 42));
        sf::Sprite counter1_spr;
        counter1_spr.setTexture(counter1);
        counter1_spr.setPosition(32, (32 * (p.row + 0.5) + 16));
        window->draw(counter1_spr);
    }
} //set for changes, waiting for flag implementation;
void game::counterChanged(sf::RenderWindow *window, map<std::string, std::string> &files) {
    //cout << "here" << endl;
    string mines = to_string(p.num_flags);
    //cout << p.num_flags << endl;
    int x = 0;
    int y = 0;
    int curr_pos = mines.length();
    if (curr_pos == 3){
        curr_pos = 2;
    }
    string three_s;
    try {
        //cout << "before x" << endl;
        three_s = mines.substr(curr_pos, 1);
        if(three_s == ""){
            throw x;
        }
    }
    catch (int x){
        //cout << "x" << endl;
//        cout << "here hr" << endl;
        try {
            three_s = mines.substr((curr_pos - 1, 1));
            curr_pos = 1;
            if (three_s ==""){
                throw y;
            }
        }
        catch (int y){
            // << "y" << endl;
            three_s = mines;
        }
    }
//    cout << curr_pos << "before"<< endl;
    curr_pos -= 1;
//    cout << curr_pos << "after" << endl;
    int three = stoi(three_s);
    sf::Texture counter3;
    counter3.loadFromFile(files["digits"], sf::IntRect(three*21, 0, 21, 42));
    sf::Sprite counter3_spr;
    counter3_spr.setTexture(counter3);
    counter3_spr.setPosition(32+(21*2), (32*(p.row+0.5)+16));
    window->draw(counter3_spr);
    if (mines.length() > 1) {
        string two_s;
        two_s = mines.substr(curr_pos, 1);
//    cout << curr_pos << endl;
//    cout << two_s << endl;
        int two = stoi(two_s);
        sf::Texture counter2;
        counter2.loadFromFile(files["digits"], sf::IntRect(two * 21, 0, 21, 42));
        sf::Sprite counter2_spr;
        counter2_spr.setTexture(counter2);
        counter2_spr.setPosition(32 + 21, (32 * (p.row + 0.5) + 16));
        window->draw(counter2_spr);
        curr_pos -= 1;
        sf::Texture counter1;
        if (curr_pos >= 0) {
            string one_s;
            one_s = mines.substr(curr_pos, 1);
            int one = stoi(one_s);
            counter1.loadFromFile(files["digits"], sf::IntRect(one * 21, 0, 21, 42));
        } else {
            counter1.loadFromFile(files["digits"], sf::IntRect(0, 0, 21, 42));
        }
        sf::Sprite counter1_spr;
        counter1_spr.setTexture(counter1);
        counter1_spr.setPosition(32, (32 * (p.row + 0.5) + 16));
        window->draw(counter1_spr);
    }
    else{
        sf::Texture counter2;
        counter2.loadFromFile(files["digits"], sf::IntRect(0 * 21, 0, 21, 42));
        sf::Sprite counter2_spr;
        counter2_spr.setTexture(counter2);
        counter2_spr.setPosition(32 + 21, (32 * (p.row + 0.5) + 16));
        window->draw(counter2_spr);
        sf::Texture counter1;
        counter1.loadFromFile(files["digits"], sf::IntRect(0, 0, 21, 42));
        sf::Sprite counter1_spr;
        counter1_spr.setTexture(counter1);
        counter1_spr.setPosition(32, (32 * (p.row + 0.5) + 16));
        window->draw(counter1_spr);
    }
    if (p.num_flags_neg && p.num_flags >= 1){
        sf::Texture neg;
        neg.loadFromFile(files["digits"], sf::IntRect(10 * 21, 0, 21, 42));
        sf::Sprite neg_spr;
        neg_spr.setTexture(neg);
        neg_spr.setPosition(11, (32 * (p.row + 0.5) + 16));
        window->draw(neg_spr);
    }
}
void game::setTimer(sf::RenderWindow *window, map<std::string, std::string> &files) {
    sf::Texture timer;
    sf::Sprite pos4;
    sf::Sprite pos3;
    sf::Sprite pos2;
    sf::Sprite pos1;
    timer.loadFromFile(files["digits"], sf::IntRect(0,0,21,42));
    pos4.setTexture(timer);
    pos3.setTexture(timer);
    pos2.setTexture(timer);
    pos1.setTexture(timer);
    int temp = 0;
    pos1.setPosition((temp * 21)+((p.col * 32) - 97),32*(p.row+0.5)+16);
    temp++;
    pos2.setPosition((temp * 21)+((p.col * 32) - 97),32*(p.row+0.5)+16);
    temp++;
    pos3.setPosition((temp * 21)+((p.col * 32) - 97),32*(p.row+0.5)+16);
    temp++;
    pos4.setPosition((temp * 21)+((p.col * 32) - 97),32*(p.row+0.5)+16);
    window->draw(pos1);
    window->draw(pos2);
    window->draw(pos3);
    window->draw(pos4);

}
map<int,cell*> game::setBoard(sf::RenderWindow *window, map<string,string> &files) {
    map<int ,cell*> cells;
    int tile_count = p.row * p.width;
    window->clear(sf::Color::White);
    int pos = 0;
    for (int y = 0; y < p.row; y++){
        for (int x = 0; x < p.col; x++){
            cell* p = new cell(files);
            string x_s = to_string(x);
            string y_s = to_string(y);
            string temp = x_s + y_s;
            int coord = stoi(temp);
            cells[pos] = p;
/*            sf::Texture hidden;
            hidden.loadFromFile(files["t_hidden"]);
            sf::Sprite hidden_spr;
            hidden_spr.setTexture(hidden);
            hidden_spr.setPosition((x*32),(y*32));
            window->draw(hidden_spr);*/
//            cout << cells[pos] << endl;
            pos++;
        }
    }
    happyButton(window, files);
    debugButton(window, files, cells);
    pause_playButton(window, files);
    leaderboardButton(window, files);
    counter(window, files);
    setTimer(window, files);
    return cells;
}
void game::reDraw(sf::RenderWindow *window, map<int, cell*>& cells, map<string,string>& files,  string arr[]) {
    window->clear(sf::Color::White);
    // << leaderboardClicked << endl;
    int temp_count = 0;
    for (int x = 0; x < p.col; x++) {
        for (int y = 0; y < p.row; y++) {
            //cout << temp_count << endl;
            // << pause_playClicked << "pause" << endl;
            cells[temp_count]->drawCurrCells(window, files, temp_count, cells, pause_playClicked, leaderboardClicked);
            temp_count++;
        }
    }
    counterChanged(window, files);
    debugButton(window, files, cells);
    pause_playButton(window, files);
    timerChanged(window, files, arr[0], arr[1], arr[2], arr[3]);
    //setTimer(window, files);
    leaderboardButton(window, files);
    happyButton(window,files);
}
string game::inButtonBounds(int mousex, int mousey) {
    for (auto &iter : spr){
        if (iter.second.getGlobalBounds().contains(mousex,mousey)){
            clicked[iter.first] = !clicked[iter.first];
            // << clicked[iter.first] << endl;
            // << leaderboardClicked << "this one" << endl;
            return iter.first;
        }
    }
    return "skip";
}





#endif //MINESWEEPER_GAME_H
