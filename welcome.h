//
// Created by wacos on 4/11/2024.
//
#include "window.h"
//#include "main.cpp"
#include <SFML/Graphics.hpp>
using namespace std;
#ifndef MINESWEEPER_WELCOME_H
#define MINESWEEPER_WELCOME_H
Read r;
struct welcome{
    welcome(sf::RenderWindow* window);
    void reDraw(sf::RenderWindow* window);
    void setText(sf::Text &text, float x, float y);
    void userText(sf::RenderWindow* window, char x, string name);
};
welcome::welcome(sf::RenderWindow *window) {
//    cout << window << endl;
    window->clear(sf::Color::Blue);
    sf::Font font;
    font.loadFromFile("files/font.ttf");
    sf::Text title;
    title.setFont(font);
    title.setString("WELCOME TO MINESWEEPER!");
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(title, p.width/2, (p.height/2) - 150);
//    text.setPosition(p.width/2,(p.height/2)-150);
    window->draw(title);
    sf::Text subTitle;
    subTitle.setFont(font);
    subTitle.setString("Enter your name:");
    subTitle.setCharacterSize(20);
    subTitle.setFillColor(sf::Color::White);
    subTitle.setStyle(sf::Text::Bold);
    setText(subTitle, p.width/2, (p.height/2)-75);
    window->draw(subTitle);
    //window->display();
}
void welcome::reDraw(sf::RenderWindow *window) {
    window->clear(sf::Color::Blue);
    sf::Font font;
    font.loadFromFile("files/font.ttf");
    sf::Text title;
    title.setFont(font);
    title.setString("WELCOME TO MINESWEEPER!");
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(title, p.width/2, (p.height/2) - 150);
//    text.setPosition(p.width/2,(p.height/2)-150);
    window->draw(title);
    sf::Text subTitle;
    subTitle.setFont(font);
    subTitle.setString("Enter your name:");
    subTitle.setCharacterSize(20);
    subTitle.setFillColor(sf::Color::White);
    subTitle.setStyle(sf::Text::Bold);
    setText(subTitle, p.width/2, (p.height/2)-75);
    window->draw(subTitle);
}
void welcome::setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}
void welcome::userText(sf::RenderWindow* window, char x, string name) {
//    cout << window << endl;
    sf::Text user;
    sf::Font font;
    font.loadFromFile("files/font.ttf");
    user.setFont(font);
    user.setString(name + x);
    user.setCharacterSize(18);
    user.setFillColor(sf::Color::Yellow);
    user.setStyle(sf::Text::Bold);
    setText(user, p.width/2, (p.height/2)-45);
    window->draw(user);
    //window->display();
}
#endif //MINESWEEPER_WELCOME_H
