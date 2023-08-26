#ifndef LABYRINTH_H // include guard
#define LABYRINTH_H
#include <string>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

// Κλάση που εθύνεται για το διάβασμα του αρχείου και την επιστροφή του χάρτη
class labyrinth{

    private:
        string file_name;
        map<pair<int, int>, char> myMap;
        int max_x = 0;
        int max_y = 0;

    public:
        labyrinth(string x);
        map<std::pair<int, int>, char> &loadMap();
        int getMaxX();
        int getMaxY();
};

#endif