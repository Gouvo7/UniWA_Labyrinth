#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "labyrinth.h"
#include "game.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2 ){
        cout << "Wrong number of arguments. You must give one parameter. Exiting..." << endl;
        return -1;
    }
    string filename = argv[1];
    labyrinth m(filename);
    
    map<std::pair<int, int>, char> myMap = m.loadMap();
    int max_x = m.getMaxX();
    int max_y = m.getMaxY();
    bool repeat = true;
    game g(myMap,max_x,max_y);
    while(repeat){
        repeat = g.play();
    }
    return 0;
}