#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "window.h"
#include "game.h"
#include "welcome.h"
#include "leaderboard.h"
#include <chrono>
using namespace std;

/*struct Read {
    Read();
    int row;
    int col;
    string row_temp;
    string col_temp;
    int num_mines;
    int getRow();
    int getCol();
    int getNumMines();
};
    Read::Read(){
        ifstream config("files/config.cfg");
        if(config.is_open()){
            cout << "true" << endl;
        }
        string num_mines_temp;
        getline(config, col_temp);
        col = stoi(col_temp);
        getline(config, row_temp);
        row = stoi(row_temp);
        getline(config, num_mines_temp);
        num_mines = stoi(num_mines_temp);
    }*/
int main() {
/*    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }*/
        map<string, string> file_names;
    file_names = {
            {"mine", "files/images/mine.png"},
            {"t_hidden", "files/images/tile_hidden.png"},
            {"t_revealed", "files/images/tile_revealed.png"},
            {"1", "files/images/number_1.png"},
            {"2", "files/images/number_2.png"},
            {"3", "files/images/number_3.png"},
            {"4", "files/images/number_4.png"},
            {"5", "files/images/number_5.png"},
            {"6", "files/images/number_6.png"},
            {"7", "files/images/number_7.png"},
            {"8", "files/images/number_8.png"},
            {"f_happy", "files/images/face_happy.png"},
            {"f_win", "files/images/face_win.png"},
            {"f_lose", "files/images/face_lose.png"},
            {"digits", "files/images/digits.png"},
            {"debug", "files/images/debug.png"},
            {"pause", "files/images/pause.png"},
            {"play", "files/images/play.png"},
            {"leaderboard", "files/images/leaderboard.png"},
            {"flag", "files/images/flag.png"}
    };
    map<int, cell*> cells;
    Read read;
    CreateWindow inst;
    sf::RenderWindow *welcome_window = inst.Create();
    welcome w_window(welcome_window);
    int screen_num = 0;
    string user_name;
    int x = 0;
    while(welcome_window->isOpen()) {
        sf::Event event;
        while (welcome_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                welcome_window->close();
                return 0;
            }
            else if ((event.key.code == sf::Keyboard::Enter && user_name.length() > 0)) {
                welcome_window->close();
            }
            if (event.type == sf::Event::TextEntered) {
                if ((event.text.unicode >= 65 && event.text.unicode <= 90) ||
                    ((event.text.unicode >= 97 && event.text.unicode <= 122))) {
                    if (user_name.length() < 10) {
                        if (user_name.length() == 0) {
                            char x = (char) event.text.unicode;
                            x = toupper(x);
                            w_window.reDraw(welcome_window);
                            user_name.push_back(x);
                            w_window.userText(welcome_window, '|', user_name);
                            welcome_window->display();
                        } else {
                            char x = (char) event.text.unicode;
                            x = tolower(x);
                            w_window.reDraw(welcome_window);
                            user_name.push_back(x);
                            w_window.userText(welcome_window, '|', user_name);
                            welcome_window->display();
                        }
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if ((event.key.code == sf::Keyboard::BackSpace)) {
                    try {
                        user_name.erase(user_name.length() - 1);
                        w_window.reDraw(welcome_window);
                        w_window.userText(welcome_window, '|', user_name);
                        welcome_window->display();
                    }
                    catch (out_of_range) {
                        w_window.reDraw(welcome_window);
                    }
                }
            }

        }
        if (x == 0) {
            w_window;
            w_window.userText(welcome_window, '|', user_name);
            welcome_window->display();
            x = 1;
        }
    }
sf::RenderWindow *game_window = inst.Create();
game g_window(game_window);
cell make(file_names);
string arr[4];
x = 0;
int j = 0;
int minutes;
int mines_left;
int seconds;
auto start_time = chrono::high_resolution_clock::now();
//may have to go in x = 1 so that reseting can be done
auto pauseTime = chrono::high_resolution_clock::now();
auto elapsed_paused_time = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - pauseTime).count();
bool paused = false;
bool leaderboard_boo = false;
    while(game_window->isOpen()) {
        sf::Event event_game;
        while (game_window->pollEvent(event_game)) {
            if (event_game.type == sf::Event::Closed) {
                game_window->close();
            }
            if (event_game.type == sf::Event::MouseButtonPressed) {
                //cout << "new" << endl;
                sf::Mouse mouse;
                int mousex = mouse.getPosition(*game_window).x;
                int mousey = mouse.getPosition(*game_window).y;
                if (event_game.mouseButton.button == sf::Mouse::Left) {
                    if (mousey <= (read.row * 32) && !g_window.debugClicked && !g_window.pause_playClicked && !g_window.lose && !g_window.win) {
//                            cout << "true" << endl;
                        for (int i = 0; i < 2; i++) {
                            for (auto &iter: cells) {
                                if (iter.second->inCellBounds(mousex, mousey, file_names, game_window, "left") && iter.second->hasBomb){
                                    g_window.lose = true;
                                    //g_window.debugBombs(game_window, cells, file_names);
                                    g_window.clicked["debug"] = true;
                                    cout << "you lose, update here" << endl;
                                }
                                else if (iter.second->inCellBounds(mousex, mousey, file_names, game_window, "left")) {
                                    iter.second->drawCurrCells(game_window, file_names, iter.first, cells, paused, leaderboard_boo);
                                }
                                else {
                                    iter.second->drawCurrCells(game_window, file_names, iter.first, cells, paused, leaderboard_boo);
                                    if (iter.second->getReveal() && !iter.second->getAlrRevealed()) {
                                        i = 0;
                                        iter.second->setAlrRevealed();
                                    }
                                }
                            }
                        }
                        //cout << "hee" << endl;
                            g_window.reDraw(game_window, cells, file_names, arr);
                            game_window->display();

                    }
                    else {
                        if (g_window.inButtonBounds(mousex, mousey) == "happy"){
                            x =0;
                            g_window.clicked["debug"] = false;
                            g_window.lose = false;
                            g_window.win = false;
                            // << "happy" << endl;
                            g_window.clicked["pause"] = false;
                        }
                        else if ((g_window.inButtonBounds(mousex, mousey) == "pause" || g_window.inButtonBounds(mousex, mousey) == "play") && (!g_window.win && !g_window.lose)){
                            g_window.clicked["pause"] = !g_window.clicked["pause"];
                            paused = !paused;
                            //cout << paused << "after" << endl;
                            if (paused){
                                // << "paused" << endl;
                                pauseTime = chrono::high_resolution_clock::now();
                            }
                            else{
                                // << "else" << endl;
                                auto unPausedTime = chrono::high_resolution_clock::now(); //may have to be steady clock
                                elapsed_paused_time += chrono::duration_cast<chrono::seconds>(unPausedTime - pauseTime).count();
                            }
                        }
                        else if (g_window.inButtonBounds(mousex, mousey) == "leaderboard") {
                            leaderboard_boo = !leaderboard_boo;
                            //g_window.clicked["leaderboard"] = !g_window.clicked["leaderboard"];
                            g_window.reDraw(game_window, cells, file_names, arr);
                            game_window->display();
                            // << leaderboard_boo << endl;
                            paused = !paused;
                            if (paused){
                                // << "paused" << endl;
                                pauseTime = chrono::high_resolution_clock::now();
                            }
                            else{
                                // << "else" << endl;
                                auto unPausedTime = chrono::high_resolution_clock::now(); //may have to be steady clock
                                elapsed_paused_time += chrono::duration_cast<chrono::seconds>(unPausedTime - pauseTime).count();
                            }
                            // << "jello " << endl;
                            sf::RenderWindow *leaderboard_w = inst.Create();
                            leaderboard LeaderBoard(leaderboard_w);
                            //add g window and display ebfore
                            LeaderBoard.readLeader(leaderboard_w);
                            //LeaderBoard.updateLeaders(leaderboard_w, minutes, seconds);
                            while (leaderboard_w->isOpen()) {
                                sf::Event event_leaderboard;
                                while (leaderboard_w->pollEvent(event_leaderboard)) {
                                    if (event_leaderboard.type == sf::Event::Closed) {
                                        leaderboard_w->close();
                                        //g_window.clicked["leaderboard"] = !g_window.clicked["leaderboard"];
                                        paused = !paused;
                                        if (paused){
                                            // << "paused" << endl;
                                            pauseTime = chrono::high_resolution_clock::now();
                                        }
                                        else{
                                            // << "else" << endl;
                                            auto unPausedTime = chrono::high_resolution_clock::now(); //may have to be steady clock
                                            elapsed_paused_time += chrono::duration_cast<chrono::seconds>(unPausedTime - pauseTime).count();
                                        }
                                    }
                                }
                                LeaderBoard.drawWindow(leaderboard_w);
                                leaderboard_w->display();
                            }
                        }
                        else if (g_window.inButtonBounds(mousex, mousey) == "debug"){}
                        g_window.reDraw(game_window, cells, file_names, arr);
                        game_window->display();
                    }
                }
                else if (event_game.mouseButton.button == sf::Mouse::Right){
                    if (mousey <= (read.row * 32) && !g_window.debugClicked && !g_window.pause_playClicked && !g_window.win && !g_window.lose) {
                        for (auto &iter: cells) {
                            if (iter.second->inCellBounds(mousex, mousey, file_names, game_window, "right")) {
//                                    cout << "Here" << endl;
                            }  else if (!iter.second->getBeenRClicked()) {
                                iter.second->drawCurrCells(game_window, file_names, iter.first, cells, paused, leaderboard_boo);
                            }
                        }
                        g_window.reDraw(game_window, cells,file_names, arr);
                        game_window->display();
                    }
                }
            }
        }
        if (x == 0) {
            // << "aqui" << endl;
            j = 1;
            if (paused){
                paused = !paused;
            }
            mines_left = p.num_mines;
            start_time = chrono::high_resolution_clock::now();
//may have to go in x = 1 so that reseting can be done
            pauseTime = chrono::high_resolution_clock::now();
            elapsed_paused_time = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - pauseTime).count();
            cells = g_window.setBoard(game_window, file_names);
            make.drawHCells(cells, file_names, game_window);
            make.setBomb(cells);
            make.setNum(cells);
            //g_window.reDraw(game_window, cells,file_names);
            game_window->display();
            x = 1;
        }
        if(!g_window.lose && !g_window.win) {
            auto game_duration = chrono::duration_cast<chrono::seconds>(
                    chrono::high_resolution_clock::now() - start_time);
            int total_time = game_duration.count();
            //cout << paused << endl;
            if (!paused) {
                //cout << "here" << endl;
                total_time = total_time - elapsed_paused_time;
                minutes = total_time / 60;
                seconds = total_time % 60;
                string min0 = to_string(minutes / 10 % 10);
//            cout << min0 << endl;
                arr[0] = min0;
                string min1 = to_string(minutes % 10);
//            cout << min1 << endl;
                arr[1] = min1;
                string sec0 = to_string(seconds / 10 % 10);
//            cout << sec0 << endl;
                arr[2] = sec0;
                string sec1 = to_string(seconds % 10);
//            cout << sec1 << endl;
                arr[3] = sec1;
            }
        }
        g_window.reDraw(game_window, cells,file_names, arr);
        game_window->display();


    }
    return 0;
}