#ifndef TYPES_H
#define TYPES_H
#include <string>
using namespace std;

struct State {
    string name;
    bool starting;
    bool accepting;
};
struct Transition {
    string from;
    string to;
    string input;
};

#endif //TYPES_H
