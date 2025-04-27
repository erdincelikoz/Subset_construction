#include "NFA.h"

using namespace std;

int main() {
    NFA nfa("C:/Users/erdin/CLionProjects/SSC/input.json");
    nfa.toDFA().print();
    return 0;
}
