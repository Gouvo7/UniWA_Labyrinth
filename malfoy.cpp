#include "malfoy.h"
#include <ncurses.h>
#include <iostream> 

// Αρχικοποίηση των ορίων του χάρτη και του χρώματος του χαρακτήρα
malfoy::malfoy(int x,int y){
    setMaxX(x);
    setMaxY(y);
    init_pair(1, COLOR_RED, COLOR_BLACK);
}

malfoy::~malfoy(){ 
}

void malfoy::makeMove(int ch, bool &m,map<pair<int, int>, char>& myMap){
    int startX = getX();
    int startY = getY();
    int max_x = getMaxX();
    int max_y = getMaxY();

    // Έλεγχος εντολής χρήστη, για κίνηση με τα βελάκια του πληκτρολογίου και το space
    // για την παράλειψη του γύρου. Με το Q θα τερματίζεται το παιχνίδι, και πατήματα διαφόρων
    // πλήκτρων θα αγνοούνται
    switch (ch) {
        case KEY_UP:
        	if (startY > 0 && myMap[{startX, startY - 1}] == '.') {
            	mvaddch(startY, startX, '.');
                startY--;
                m = true;
            }
            break;
        case KEY_DOWN:
            if (startY < max_y - 1 && myMap[{startX, startY + 1}] == '.') {
            	mvaddch(startY, startX, '.');
                startY++;
                m = true;
            }
            break;
        case KEY_LEFT:
        	if (startX > 0 && myMap[{startX - 1, startY}] == '.') {
            	mvaddch(startY, startX, '.');
                startX--;
                m = true;
            }
            break;
        case KEY_RIGHT:
        	if (startX < max_x - 1 && myMap[{startX + 1, startY}] == '.') {
            	mvaddch(startY, startX, '.');
                startX++;
                m = true;
            }
            break;
        case ' ':
            m = true;
            break;
        case 'q':
        case 'Q':
            endwin();
        	exit(1);
            break;
    }
    attron(COLOR_PAIR(1));
    mvaddch(startY, startX, 'L');
    attroff(COLOR_PAIR(1));
    setX(startX);
    setY(startY);
    refresh();
}
