#include <map>
#include <random>
#include "unit.h"
#include <ncurses.h>

unit::unit(){
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
}

unit::~unit(){

}

int unit::getX(){
    return x_pos;
}

int unit::getY(){
    return y_pos;
}

void unit::setX(int x){
    x_pos = x;
}

void unit::setY(int y){
    y_pos = y;
}

void unit::spawn(map<pair<int, int>, char> &myMap){
    max_x = getMaxX();
    max_y = getMaxY();
    int startX, startY;

    // Δημιουργία ενός τυχαίου αριθμού Χ και Y, στις οποίες
    // συντεταγμένες αυτές να βρίσκεται έγκυρο σημείο ('.')
    do {
    	startX =(rand() % (max_x - 1 + 1)) + 1;
        startY = (rand() % (max_y - 1 + 1)) + 1;
    } while (myMap[{startX, startY}] != '.');
    setX(startX);
    setY(startY);
    refresh();
}

int unit::getMaxX(){
    return max_x;
}
int unit::getMaxY(){
    return max_y;
}
void unit::setMaxX(int tmp){
    max_x = tmp;
}
void unit::setMaxY(int tmp){
    max_y = tmp;
}