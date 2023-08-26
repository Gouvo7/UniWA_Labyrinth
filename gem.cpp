#include <map>
#include "gem.h"
#include <ncurses.h>

gem::gem(){
}
gem::~gem(){
}

gem::gem(int x,int y){
    setMaxX(x);
    setMaxY(y);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
}

void gem::rngMove(map<pair<int, int>, char>& myMap){
    int startX, startY;
    int max_x = getMaxX();
    int max_y = getMaxY();

    // Δημιουργία ενός τυχαίου αριθμού Χ και Y, στις οποίες
    // συντεταγμένες αυτές να βρίσκεται έγκυρο σημείο ('.')
    do {
    	startX =(rand() % (max_x - 1 + 1)) + 1;
        startY = (rand() % (max_y - 1 + 1)) + 1;
    } while (myMap[{startX, startY}] != '.');
    
    attron(COLOR_PAIR(3));
    mvaddch(startY, startX, 'G');
    attroff(COLOR_PAIR(3));
    mvaddch(getY(),getX() , '.');
    setX(startX);
    setY(startY);
    refresh();
}