#ifndef MPAMPIS_H
#define MPAMPIS_H
#include <string>
#include <map>
#include "unit.h"
#include "gem.h"

using namespace std;

// Παίκτης Μπάμπης που κληρονομεί την κλάση unit
class mpampis : public unit{
    public:
        mpampis(int,int);
        ~mpampis();
        void moveTowardsGem(gem&,map<pair<int, int>, char> &);
};

#endif