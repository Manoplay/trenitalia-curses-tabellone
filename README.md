# trenitalia-curses-tabellone
Tabellone Trenitalia fatto in C++ visualizzato in interfaccia curses.

# Compilazione
    mkdir build
    cd build
    cmake ..
    make

# Esecuzione
    $ ./trenitab
    Inserire codice della stazione: [STAZIONE]

# Licenza
Per la licenza di questo software vedi **LICENSE**.
Per la realizzazione è stata usata la single-header library "json" di nlohmann (https://github.com/nlohmann/json), anch'essa sotto licenza MIT.
Le librerie utilizzate da questo programma sono *libcurl* per le richieste web e *ncurses* per l'interfaccia.
