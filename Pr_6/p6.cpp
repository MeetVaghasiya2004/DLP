#include <iostream>
#include <string>

using namespace std;

class RecursiveDescentParser {
private:
    string input;
    int index; // Current position in the string

public:
    RecursiveDescentParser(string str) {
        input = str;
        index = 0;
    }

    // Function to check if the current character matches expected character
    bool match(char expected) {
        if (index < input.length() && input[index] == expected) {
            index++;
            return true;
        }
        return false;
    }

    // Parse S → ( L ) | a
    bool parse_S() {
        if (match('a')) { // S → a
            return true;
        } else if (match('(')) { // S → ( L )
            if (parse_L() && match(')')) {
                return true;
            }
        }
        return false;
    }

    // Parse L → S L'
    bool parse_L() {
        if (!parse_S()) {
            return false;
        }
        return parse_L_prime();
    }

    // Parse L' → , S L' | ε
    bool parse_L_prime() {
        if (match(',')) { // If there is a comma, expect S again
            if (parse_S()) {
                return parse_L_prime(); // Continue checking for more elements
            }
            return false; // Invalid case if S does not follow ','
        }
        return true; // ε (empty string case)
    }

    // Check if the input string is valid according to the grammar
    bool is_valid() {
        return parse_S() && index == input.length();
    }
};

int main() {
    string test_cases[] = {
        "(a)", "a", "(a,a)", "(a,(a,a),a)", "(a,a),(a,a)",  
        "a)", "(a a,a", "a a,", "(a,a),a" 
    };

    for (const string &test : test_cases) {
        RecursiveDescentParser parser(test);
        cout << "Input: " << test << "  →  Output: " 
             << (parser.is_valid() ? "Valid string" : "Invalid string") << endl;
    }

    return 0;
}
