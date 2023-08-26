#ifndef GAME_H
#define GAME_H
#include <string>
#include "unit.h"
#include "gem.h"

using namespace std;

class game{

    private:
        int max_x; // Όρια χάρτη
        int max_y;
        map<pair<int, int>, char> myMap;
    public:
        game(map<pair<int, int>, char> m,int x,int y);
        bool play();
        void makeMove(unit &, int,bool &);
        void spawnGem(gem &);
        void rngMove(unit &);
        void rngMove(gem &);
};

#endif