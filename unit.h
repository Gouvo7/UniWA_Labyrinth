#ifndef UNIT_H
#define UNIT_H
#include <string>
#include <map>

using namespace std;

// H κλάση unit αφορά τα αντικείμενα τα οποία θα κινούνται μέσα στο παιχνίδι.
// Αυτά είναι ο χαρακτήρας Μαλφόϋ, Μπάμπης και το διαμάντι.
// Η κλάση αυτή κληρονομείται από τις κλάσεις malfoy, mpampis και gem.
class unit{

    private:
        int x_pos; // Θέση Χ
        int y_pos; // Θέση Y
        int max_x; // Όριο χάρτη για τον άξονα Χ
        int max_y; // Όριο χάρτη για τον άξονα Y
        
    public:
        unit();
        ~unit();
        int getX();
        int getY();
        void setX(int);
        void setY(int);
        int getMaxX();
        int getMaxY();
        void setMaxX(int);
        void setMaxY(int);
        void spawn(map<pair<int, int>, char> &); // Συνάρτηση για την αρχικοποίηση της τυχαίας θέσης
};

#endif