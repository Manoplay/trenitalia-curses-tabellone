#include "tabellone.h"

#include <iostream>

int main() {
    std::string stazione;
    std::cout << "Inserire il numero della stazione: ";
    std::cin >> stazione;
    initialize();
    Tabellone tabellone(stazione);
    tabellone.render();
    while (getch() != 'q');
    endwin();
    return 0;
}
