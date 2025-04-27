#ifndef NFA_H
#define NFA_H
#include <string>
#include <vector>
#include "DFA.h"

#include "Types.h"
using namespace std;



class NFA {

public:
    NFA(string filename);
    DFA toDFA();

    void setAlphabet(const vector<string>& parsedalphabet) {
        alphabet = parsedalphabet;
    }
    vector<string> getAlphabet() const{
        return alphabet;
    }

    void setStates(vector<State> parsedstates){
        states=parsedstates;
    }
    vector<State> getStates() {
        return states;
    }

    void setTransitions(vector<Transition> parsedtransitions) {
        transitions = parsedtransitions;
    }
    vector<Transition> getTransitions() {
        return transitions;
    }

private:
    vector<string> alphabet;
    vector<State> states;
    vector<Transition> transitions;

};

#endif //NFA_H
