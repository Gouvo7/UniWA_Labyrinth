#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "labyrinth.h"

using namespace std;

labyrinth::labyrinth(string x){
    file_name = x;
}

map<std::pair<int, int>, char> &labyrinth::loadMap(){
    
    ifstream inputFile(file_name);
    bool hasAsterisk = false;
    bool hasDot = false;
    if (inputFile.is_open()) {
        string line;
        int y = 0;
        while (getline(inputFile, line)) {
            int x = 0;
            for (char c : line) {
                if (c == '*')
                    hasAsterisk = true;
                if (c == '.')
                    hasDot = true;
                if (c == '*' || c == '.' || c == ' ') {
                    myMap[{x, y}] = c;
                    x++;
                }
            }
            y++;
            if (y > max_y)
                max_y = y;
            if (x > max_x)
                max_x = x;
        }
        inputFile.close();
    } else {
        cout << "Failed to open file." << endl;
        exit(-1);  // Exit the program with an error code
    }
    if (hasAsterisk && hasDot)
        return myMap;
    else{
        cout << "File does not meet the requirements. Map should be designed \n"
        "to have '*' for walls and '.' for paths." << endl;
        exit(-2);  // Exit the program with an error code
    }
}

int labyrinth::getMaxX(){
    return max_x;
}
int labyrinth::getMaxY(){
    return max_y;
}
