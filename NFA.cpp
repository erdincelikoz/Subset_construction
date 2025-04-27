#include <string>
#include <vector>
#include "NFA.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <iomanip>
using namespace std;
using json = nlohmann::json;

int startindex;
vector<int> acceptindex;

NFA::NFA(string filename) {
    ifstream input(filename);
    json j;
    j = json::parse(input);

    setAlphabet(j["alphabet"]);

    vector<json> inputstates = j["states"];
    vector<State> parsedstates;
    for (int i = 0; i < inputstates.size(); i++) {
        State temp;
        parsedstates.push_back(temp);
        parsedstates[i].name = inputstates[i]["name"];
        parsedstates[i].accepting = inputstates[i]["accepting"];
        if (inputstates[i]["accepting"] == true) {
            acceptindex.push_back(i);
        }
        parsedstates[i].starting = inputstates[i]["starting"];
        if (inputstates[i]["starting"] == true) {
            startindex = i;
        }
    }
    setStates(parsedstates);

    vector<json> inputtransitions = j["transitions"];
    vector<Transition> parsedtransitions;
    for (int i = 0; i < inputtransitions.size(); i++) {
        Transition temp;
        parsedtransitions.push_back(temp);
        parsedtransitions[i].from = inputtransitions[i]["from"];
        parsedtransitions[i].input = inputtransitions[i]["input"];
        parsedtransitions[i].to = inputtransitions[i]["to"];
    }
    setTransitions(parsedtransitions);
}

DFA NFA::toDFA() {
    DFA dfa;
    dfa.setAlphabet(getAlphabet());

    string startName = "{" + getStates()[startindex].name + "}";
    vector<string> visited;
    visited.push_back(startName);

    vector<State> newStates;
    vector<Transition> newTransitions;

    State startState;
    startState.name = startName;
    startState.starting = true;
    startState.accepting = false;
    newStates.push_back(startState);

    for (int i = 0; i < visited.size(); i++) {
        string currentGroup = visited[i];
        vector<string> currentStates;
        string name = "";
        for (char c : currentGroup) {
            if (c == ',' || c == '{' || c == '}') {
                if (!name.empty()) {
                    currentStates.push_back(name);
                    name = "";
                }
            } else {
                name += c;
            }
        }
        if (!name.empty()) {
            currentStates.push_back(name);
        }

        for (string symbol : getAlphabet()) {
            vector<string> nextStates;

            for (string stateName : currentStates) {
                for (Transition t : getTransitions()) {
                    if (t.from == stateName && t.input == symbol) {
                        nextStates.push_back(t.to);
                    }
                }
            }

            if (!nextStates.empty()) {
                sort(nextStates.begin(), nextStates.end());
                nextStates.erase(unique(nextStates.begin(), nextStates.end()), nextStates.end());

                string newName = "{";
                for (int j = 0; j < nextStates.size(); j++) {
                    newName += nextStates[j];
                    if (j != nextStates.size() - 1) {
                        newName += ",";
                    }
                }
                newName += "}";

                bool found = false;
                for (string s : visited) {
                    if (s == newName) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    visited.push_back(newName);

                    State newState;
                    newState.name = newName;
                    newState.starting = false;
                    newState.accepting = false;
                    for (int k = 0; k < acceptindex.size(); k++) {
                        if (newName.find(getStates()[acceptindex[k]].name) != string::npos) {
                            newState.accepting = true;
                            break;
                        }
                    }
                    newStates.push_back(newState);
                }

                Transition newT;
                newT.from = currentGroup;
                newT.input = symbol;
                newT.to = newName;
                newTransitions.push_back(newT);
            }
        }
    }

    dfa.setStates(newStates);
    dfa.setTransitions(newTransitions);
    for (State s : newStates) {
        if (s.accepting) {
            dfa.getEndstates().push_back(s);
        }
    }
    dfa.setStartstate(startState);

    return dfa;
}





