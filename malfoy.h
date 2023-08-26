#ifndef MALFOY_H
#define MALFOY_H
#include <string>
#include "unit.h"

using namespace std;

// Παίκτης Μάλφοϋ που κληρονομεί την κλάση unit
class malfoy : public unit{
    public:
        malfoy(int,int);
        ~malfoy();
        void makeMove(int, bool &, map<pair<int, int>, char>&);
};

#endif