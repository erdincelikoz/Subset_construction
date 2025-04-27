#ifndef DFA_H
#define DFA_H
#include "Types.h"
#include <vector>
#include <algorithm>
using namespace std;

class DFA {
public:
    DFA();
    void print();

    void setAlphabet(vector<string> newalphabet) {
        alphabet = newalphabet;
    }
    vector<string> getAlphabet() {
        return alphabet;
    }

    void setStates(vector<State> newstates){
        states = newstates;
    }
    vector<State> getStates() {
        return states;
    }


    void setStartstate(State newstartstate) {
        startstate = newstartstate;
    }
    State getStartstate() {
        return startstate;
    }
    //void sortStates() {
    //    sort(states.begin(), states.end());
   // }

    void setEndstates(vector<State> newendstates) {
        endstates = newendstates;
    }
    vector<State> getEndstates() {
        return endstates;
    }



    void setTransitions(vector<Transition> newtransitions) {
        transitions = newtransitions;
    }
    vector<Transition> getTransitions() {
        return transitions;
    }


private:
    vector<string> alphabet;
    vector<State> states;
    State startstate;
    vector<State> endstates;
    vector<Transition> transitions;
};

#endif //DFA_H
