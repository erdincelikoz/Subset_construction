#include <string>
#include <vector>
#include "NFA.h"
#include <iostream>
#include <fstream>
#include <map>
#include "json.hpp"
#include <iomanip>
using namespace std;
using json = nlohmann::json;
#include "DFA.h"

DFA::DFA(){}

void DFA::print() {

    json j2;
    j2["type"]     = "DFA";
    j2["alphabet"] = getAlphabet();

    j2["states"] = json::array();
    for (State state : getStates()) {
        json s;
        s["name"]     = state.name;
        s["starting"] = state.starting;
        s["accepting"]= state.accepting;
        j2["states"].push_back(s);
    }

    j2["transitions"] = json::array();
    for (Transition transition : getTransitions()) {
        json t;
        t["from"]  = transition.from;
        t["to"]    = transition.to;
        t["input"] = transition.input;
        j2["transitions"].push_back(t);
    }

    cout << setw(4) << j2 << endl;
}


