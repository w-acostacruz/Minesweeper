
#ifndef MINESWEEPER_LEADERBOARD_H
#define MINESWEEPER_LEADERBOARD_H
#include "window.h"
#include <sstream>
#include <fstream>
#include <map>
using namespace std;

struct leaderboard{
    map<int, string> numbers;
    map<int, string> leaders;
    string test;
    string test2;
    leaderboard(sf::RenderWindow *window);
    void readLeader(sf::RenderWindow *window);
    void updateLeaders(sf::RenderWindow *window, int minutes, int seconds);
    void drawWindow(sf::RenderWindow *window);
    void setText(sf::Text &text, float x, float y);
};
leaderboard::leaderboard(sf::RenderWindow *window){}
void leaderboard::readLeader(sf::RenderWindow *window) {
    ifstream file("files/leaderboard.txt");
    int position= 1;
    string temp;
    string name;
    string line;
    while(getline(file, line)){
        stringstream ss(line);
        getline(ss, temp, ',');
        getline(ss, name, ',');
        test = to_string(position) +'.' + "\t" + temp + "\t" + name + "\n\n";
        test2 = test2.append(test);
        //cout << stoi(temp) << endl;
        numbers[position] = temp;
        leaders[position] = name;
        position++;
    }

    //cout << test << endl;
}
void leaderboard::drawWindow(sf::RenderWindow *window) {
    window->clear(sf::Color::Blue);
    sf::Font font;
    font.loadFromFile("files/font.ttf");
    sf::Text title;
    title.setFont(font);
    title.setString("LEADERBOARD");
    title.setCharacterSize(20);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(title, p.width/2, (p.height/2) - 120);
    window->draw(title);
    sf::Text content;
    content.setFont(font);
    content.setString(test2);
    content.setCharacterSize(18);
    content.setFillColor(sf::Color::White);
    content.setStyle(sf::Text::Bold);
    setText(content, p.width/2, (p.height/2) + 20);
    window->draw(content);
}
void leaderboard::setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}
void leaderboard::updateLeaders(sf::RenderWindow *window, int minutes, int seconds) {
    int new_postion;
    int distance_to_end;
    string min0 = to_string(minutes / 10 % 10);
//            cout << min0 << endl;
    string min1 = to_string(minutes % 10);
//            cout << min1 << endl;
    string sec0 = to_string(seconds / 10 % 10);
//            cout << sec0 << endl;
    string sec1 = to_string(seconds % 10);
//            cout << sec1 << endl;
    for (auto &iter : numbers){
        int min = stoi(iter.second.substr(0, 2));
        int sec = stoi(iter.second.substr(3, 2));
        if (minutes <= min){
            if (seconds < sec){
                string new_time = min0 + min1 + ':' + sec0 + sec1;
                string prev;
                string prev2;
                prev = numbers[iter.first];
                numbers[iter.first] = new_time;
                if (iter.first != 5) {
                    for (int i = (iter.first + 1); i <= 5; i++){
                        prev2 = numbers[i];
                        numbers[i] = prev;
                        prev = prev2;
                    }
                }
//                new_postion = iter.first;
//                distance_to_end = 6- iter.first;
                break;
            }
        }
    }
    ofstream file("leaderboard.txt", ios::in);
    for (auto& iter : numbers){
        file << iter.second << endl;
    }
}

#endif //MINESWEEPER_LEADERBOARD_H
