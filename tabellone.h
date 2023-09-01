//
// Created by Alessandro Mascolo on 30/08/23.
//

#ifndef TRENITAB_TABELLONE_H
#define TRENITAB_TABELLONE_H

#include <ncurses.h>
#include <cstring>
#include <ctime>
#include <string>
#include <utility>
#include <curl/curl.h>

using std::string;

class Tabellone {
public:
    void render();
    explicit Tabellone(string stazione = "S09103"): stazione(std::move(stazione)) {};
private:
    string stazione;
    static void draw_time();
    void draw_trains();
    string get_partenze();
};

void initialize();


#endif //TRENITAB_TABELLONE_H
