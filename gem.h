#ifndef GEM_H
#define GEM_H
#include <string>
#include "unit.h"

using namespace std;

class gem : public unit{
    public:
        gem();
        ~gem();
        gem(int,int);
        void rngMove(map<pair<int, int>, char>&);
};

#endif