#include <string>
#include <iostream>
#include <ncurses.h>
#include <random>
#include <map>
#include <cstdlib>
#include <time.h>
#include "game.h"
#include "mpampis.h"
#include "malfoy.h"

using namespace std;

// Αρχικοποίηση των ορίων του χάρτη, τον χάρτη και του ncurses 
game::game(map<pair<int, int>, char> m, int x, int y){
    max_x = x;
    max_y = y;
    myMap = m;
    srand(time(0));
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
}


bool game::play(){

    // Εμφάνιση του χάρτη-λαβύρινθου
    for (int y = 0; y < max_y; y++) {
    	for (int x = 0; x < max_x; x++) {
        	pair<int, int> pos{x, y};
            if (myMap.find(pos) != myMap.end()) {
            	mvaddch(y, x, myMap[pos]);
            } else {
            	mvaddch(y, x, ' ');
			}
        }
    }

    // Αρχικοποίηση αντικειμένων 2 παικτών και του διαμαντιού
    // και εμφάνισή τους στην οθόνη με τα κατάλληλα χρώματα
    malfoy lucas(max_x,max_y);
    lucas.spawn(myMap);
    attron(COLOR_PAIR(1));
    mvaddch(lucas.getY(), lucas.getX(), 'L');
    attroff(COLOR_PAIR(1));

    mpampis potter(max_x,max_y);
    potter.spawn(myMap);
    attron(COLOR_PAIR(2));
    mvaddch(potter.getY(), potter.getX(), 'M');
    attroff(COLOR_PAIR(2));

    gem g(max_x,max_y);
    g.spawn(myMap);
    attron(COLOR_PAIR(3));
    mvaddch(g.getY(), g.getX(), 'G');
    attroff(COLOR_PAIR(3));
    refresh();

    
    // Δημιουργία τυχαίου αριθμού (10-20) για την κίνηση του διαμαντιού 
    int turnsForChange = (rand() % 11) + 10;
    bool repeat = false; // Μεταβλητή ελέγχου επανάληψης παιχνιδιού
    bool running = true; // Μεταβλητή ελέγχου ροής του παιχνιδιού
    int ch;              // Πλήκτρο που πατήθηκε από τον χρήστη
    bool moved;          // Μεταβλητή ελέγχου κίνησης του Μάλφοϋ
    int times = 0;
    
    while (running) {
        moved = false;
        ch = getch();
        
        // Έλεγχος εγκυρότητας και πραγματοποίηση επόμενης 
        // κίνησης, εφόσον είναι έγκυρη
    	lucas.makeMove(ch, moved,myMap); 
        if (moved){
            times++;

            // Εύρεση της επόμενης καλύτερης κίνησης για τον Μπάμπη
            // και εκτέλεση αυτής
            potter.moveTowardsGem(g,myMap); 

            // Εάν παιχτούν ο προκαθορισμένος αριθμός γύρων μέχρι την αλλαγή
            // της θέσης του διαμαντιού, τότε άλλαξε ξανά την θέση του
            if (turnsForChange == times){
                g.rngMove(myMap);
                times = 0;
            }
        }

        // Έλεγχοι για τον τερματισμό του παιχνιδιού
        // (εάν κάποιος παίκτης ή και οι 2 βρίσκονται στην ίδια θέση με το διαμάντι)
        if (lucas.getX() == g.getX() && lucas.getY() == g.getY()){
            if (potter.getX() == g.getX() && potter.getY() == g.getY()){
                mvprintw(max_y+1,0,"Draw!\nDo you want to play again?\nY for yes, N for no");
                running = false;
            }else{
                mvprintw(max_y+1,0,"Malfoy wins!\nDo you want to play again?\n"
                    "Y for yes, N for no");
                running = false;
            }
        }
        if (potter.getX() == g.getX() && potter.getY() == g.getY() && running){
            mvprintw(max_y+1,0,"Mpampis wins!\nDo you want to play again?\n"
                    "Y for yes, N for no.");
            running = false;
        }
    }
    refresh();
    int z = 1;
    // Έλεγχος για το πάτημα του κατάλληλου πλήκτρου ύστερα από
    // την ολοκλήρωση του παιχνιδιού
    while (z){
        ch = getch();
        if (ch == 'Y' || ch == 'y'){
            repeat = true;
            z = 0;
        }
        if (ch == 'N' || ch == 'n'){
            repeat = false;
            z = 0;
        }
    }
    clear();
    endwin();
    return repeat;
}
