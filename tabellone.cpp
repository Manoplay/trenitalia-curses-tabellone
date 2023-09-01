//
// Created by Alessandro Mascolo on 30/08/23.
//

#include <sstream>
#include "json.hpp"
#include "tabellone.h"

struct {
    int w = 0;
    int h = 0;
} sz;

void initialize() {
    initscr();
    noecho();
    start_color();
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    getmaxyx(stdscr, sz.h, sz.w);
}

void Tabellone::render() {
    move(0, 0);
    attron(COLOR_PAIR(2));
    for (int j = 0; j <= 3; j++) {
        hline(' ', sz.w);
        move(j, 0);
    }
    move(1, 0);
    printw("PARTENZE");
    move(2, 0);
    printw("TRENO      DESTINAZIONE");
    move(2, sz.w - strlen("ORARIO   RIT   BIN "));
    printw("ORARIO   RIT   BIN ");
    draw_time();
    attroff(COLOR_PAIR(2));
    move(3, 0);
    attron(COLOR_PAIR(1));
    draw_trains();
    attroff(COLOR_PAIR(1));
    refresh();
}

using nlohmann::json;

void padTo(std::string &str, const size_t num, const char paddingChar = ' ')
{
    if(num > str.size())
        str.insert(str.size(), num - str.size(), paddingChar);
}

void Tabellone::draw_trains() {
    json data = json::parse(get_partenze());
    for (auto & i : data) {
        string numTreno = i["compNumeroTreno"];
        padTo(numTreno, 9);
        printw(numTreno.c_str());
        printw("  ");
        string destinazione = i["destinazione"];
        printw(destinazione.c_str());
        int x, y;
        getyx(stdscr, y, x);
        move(y, sz.w - strlen("ORARIO   RIT   BIN "));
        string orario = i["compOrarioPartenzaZero"];
        printw(orario.c_str());
        printw("    ");
        int ritardo = i["ritardo"];
        if (ritardo) printw(std::to_string(ritardo).append("'    ").c_str()); else printw("      ");
        string binario;
        if (i["binarioProgrammatoPartenzaDescrizione"].is_string())
            binario = (std::string)i["binarioProgrammatoPartenzaDescrizione"];
        printw(binario.c_str());
        printw("\n");
    }
}

void Tabellone::draw_time() {
    move(1, sz.w - 6);
    time_t time1 = time(nullptr);
    struct tm * curt = gmtime(&time1);
    printw("%d:%d", curt->tm_hour, curt->tm_min);
    refresh();
}

size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string *) userp)->append((char *) contents, size * nmemb);
    return size * nmemb;
}

string Tabellone::get_partenze() {
    CURL* curl = curl_easy_init();
    std::stringstream ss;
    time_t current;
    char rfc_2822[40];
    time(&current);
    strftime(
            rfc_2822,
            sizeof(rfc_2822),
            "%a, %d %b %Y %T %z",
            localtime(&current));
    ss << "http://www.viaggiatreno.it/infomobilita/resteasy/viaggiatreno/partenze/" << stazione << '/' << string(curl_easy_escape(nullptr, rfc_2822, 0));
    string url = ss.str();
    url.shrink_to_fit();
    curl_easy_setopt(curl, CURLOPT_URL, ss.str().c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    string response;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_perform(curl);
     return response;
}
