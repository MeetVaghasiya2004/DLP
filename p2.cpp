#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include <vector>

using namespace std;

// Function to check if the input string is valid for the finite automaton
bool isValid(int noOfSymbol, const string& inputSymbols, int noOfState, int initialState, 
             const set<int>& acceptingStates, const string& inputString) {
    bool checkStringContainInputSymbol = false;

    // Validate if the input string contains only valid input symbols
    for (char c : inputString) {
        checkStringContainInputSymbol = false;
        for (char inputSymbol : inputSymbols) {
            if (c == inputSymbol) {
                checkStringContainInputSymbol = true;
                break;
            }
        }
        if (!checkStringContainInputSymbol) {
            return false;
        }
    }

    // Transition table
    unordered_map<int, unordered_map<char, int>> transitionTable;

    // Input transitions for each state
    for (int i = 0; i < noOfState; i++) {
        cout << "Enter transitions for state " << (i + 1) << ":\n";
        for (char inputSymbol : inputSymbols) {
            cout << "Enter next state if current state is " << (i + 1) 
                 << " and input symbol is " << inputSymbol << ": ";
            int tempState;
            cin >> tempState;
            transitionTable[i + 1][inputSymbol] = tempState;
        }
    }

    // Process the input string
    int currentState = initialState;
    for (char symbol : inputString) {
        // Check if the current state has a valid transition for the given symbol
        if (transitionTable.count(currentState) && 
            transitionTable[currentState].count(symbol)) {
            currentState = transitionTable[currentState][symbol];
        } else {
            // If no valid transition exists, the string is invalid
            return false;
        }
    }

    // Check if the final state is an accepting state
    return acceptingStates.count(currentState) > 0;
}

int main() {
    int noOfSymbol, noOfState, initialState, noOfAcceptingStates;
    string inputSymbols, inputString;
    set<int> acceptingStates;

    // Input details for the finite automaton
    cout << "Enter number of input symbols: ";
    cin >> noOfSymbol;
    cout << "Enter input symbols: ";
    cin >> inputSymbols;

    cout << "Enter number of states: ";
    cin >> noOfState;
    cout << "Enter initial state: ";
    cin >> initialState;

    cout << "Enter number of accepting states: ";
    cin >> noOfAcceptingStates;
    cout << "Enter accepting states:\n";
    for (int i = 0; i < noOfAcceptingStates; i++) {
        int state;
        cin >> state;
        acceptingStates.insert(state);
    }

    cout << "Enter input string: ";
    cin >> inputString;

    // Validate the input string
    if (isValid(noOfSymbol, inputSymbols, noOfState, initialState, acceptingStates, inputString)) {
        cout << "The input string is valid." << endl;
    } else {
        cout << "The input string is invalid." << endl;
    }

    return 0;
}
