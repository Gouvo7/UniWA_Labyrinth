#include "mpampis.h"
#include <ncurses.h>
#include <queue>
#include <map>

// Αρχικοποίηση των ορίων του χάρτη και του χρώματος του χαρακτήρα
mpampis::mpampis(int x, int y){
    setMaxX(x);
    setMaxY(y);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
}

mpampis::~mpampis(){}

void mpampis::moveTowardsGem(gem& g, map<pair<int, int>, char>& myMap) {
    
    // Τρέχουσα θέση διαμαντιού
    int gemX = g.getX();
    int gemY = g.getY();
    
    // Τρέχουσα θέση του Μπάμπη
    int currentX = getX();
    int currentY = getY();

    // Υλοποίηση BFS αλγορίθμου για την εύρεση της επόμενης καλύτερης κίνησης για τον Μπάμπη.
    // Αρχικοποίηση μιας ουράς queue και ενός χάρτη map για την καταμέτρηση των επισκευθέντων σημείων
    queue<pair<int, int>> q;
    map<pair<int, int>, bool> visited;

    // Η τρέχουσα θέση σημειώνεται πως έχει επισκεπτεί και τοποθετείτε στην ουρά.
    visited[{currentX, currentY}] = true;
    q.push({currentX, currentY});

    // Αρχικοποίηση ενός 2ου χάρτη map parent για την καταγραφή των γονικών θέσεων
    // για κάθε θέση που έχει επισκεφτεί ο BFS αλγόριθμος (Αρχικά προσθέτουμε στο map την τρέχουσα θέση)
    map<pair<int, int>, pair<int, int>> parent;
    parent[{currentX, currentY}] = {currentX, currentY};

    // Αλγόριθμος BFS για την αναζήτηση της πιο σύντομης διαδρομής
    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();

        // Καταχώρηση των δυνατών κινήσεων (πάνω, κάτω, αριστερά, δεξιά)
        int dx[] = {0, 0, -1, 1};
        int dy[] = {-1, 1, 0, 0};

        for (int i = 0; i < 4; i++) {
            int nextX = current.first + dx[i];
            int nextY = current.second + dy[i];

            // Έλεγχος για το εάν η επόμενη κίνηση είναι έγκυρη και
            // δεν ανήκει στο map με τις visited συντεταγμένες. Εάν πληροί τα παραπάνω
            // κριτήρια, θα προστεθεί στην ουρά και στο map με τις θέσεις που έχουμε επισκεφτεί.
            // Η τρέχουσα θέση, θα αποθηκευτεί στο map parent για την καταγραφή του μονοπατιού.
            if (myMap[{nextX, nextY}] == '.' && !visited[{nextX, nextY}]) {
                visited[{nextX, nextY}] = true;
                q.push({nextX, nextY});
                parent[{nextX, nextY}] = {current.first, current.second};
            }
        }
    }
    // Ανακατασκευή του μονοπατιού από την τρέχουσα θέση στην επόμενη
    // θέση πιο κοντά στο διαμάντι.
    // Θέση της τρέχουσας θέσης του διαμαντιού στο ζευγάρι next
    pair<int, int> next = {gemX, gemY};
    while (parent[next] != make_pair(currentX, currentY)) {
        next = parent[next];
    }

    attron(COLOR_PAIR(2));
    mvaddch(next.second, next.first, 'M');
    attroff(COLOR_PAIR(2));
    mvaddch(currentY, currentX, '.');
    refresh();
    setX(next.first);
    setY(next.second);

}
