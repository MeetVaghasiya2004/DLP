#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <regex>

using namespace std;

// Set of C language keywords
const unordered_set<string> keywords = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
    "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
    "union", "unsigned", "void", "volatile", "while" , "printf" , "scanf"
};

// Operators in C language
const unordered_set<string> operators = {
    "+", "-", "*", "/", "%", "++", "--", "==", "!=", ">", "<", ">=", "<=",
    "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", "=", "+=", "-=", "*=", "/=",
    "%=", "&=", "|=", "^=", "<<=", ">>="
};

// Delimiters and symbols
const unordered_set<char> delimiters = {
    '(', ')', '{', '}', '[', ']', ',', ';', ':', '#'
};

// Function to check if a string is a keyword
bool isKeyword(const string& word) {
    return keywords.find(word) != keywords.end();
}

// Function to check if a string is an operator
bool isOperator(const string& word) {
    return operators.find(word) != operators.end();
}

// Function to perform lexical analysis
void lexicalAnalysis(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    int keywordCount = 0, identifierCount = 0, operatorCount = 0, numberCount = 0, symbolCount = 0;

    regex identifierRegex("[a-zA-Z_][a-zA-Z0-9_]*");
    regex numberRegex("[0-9]+");

    while (getline(file, line)) {
        string word;
        for (size_t i = 0; i < line.size(); ++i) {
            char ch = line[i];

            if (isspace(ch)) {
                if (!word.empty()) {
                    if (isKeyword(word)) {
                        keywordCount++;
                    } else if (regex_match(word, identifierRegex)) {
                        identifierCount++;
                    }
                    word.clear();
                }
            } else if (delimiters.find(ch) != delimiters.end()) {
                if (!word.empty()) {
                    if (isKeyword(word)) {
                        keywordCount++;
                    } else if (regex_match(word, identifierRegex)) {
                        identifierCount++;
                    }
                    word.clear();
                }
                symbolCount++;
            } else if (ispunct(ch) && !isdigit(ch)) {
                if (!word.empty()) {
                    if (isKeyword(word)) {
                        keywordCount++;
                    } else if (regex_match(word, identifierRegex)) {
                        identifierCount++;
                    }
                    word.clear();
                }
                string op;
                op += ch;
                if (i + 1 < line.size() && isOperator(op + line[i + 1])) {
                    op += line[++i];
                }
                if (isOperator(op)) {
                    operatorCount++;
                }
            } else {
                word += ch;
            }
        }
        if (!word.empty()) {
            if (isKeyword(word)) {
                keywordCount++;
            } else if (regex_match(word, identifierRegex)) {
                identifierCount++;
            } else if (regex_match(word, numberRegex)) {
                numberCount++;
            }
        }
    }

    file.close();

    // Calculate total tokens
    int totalTokens = keywordCount + identifierCount + operatorCount + numberCount + symbolCount;

    // Display the results
    cout << "Lexical Analysis Results:\n";
    cout << "Keywords: " << keywordCount << endl;
    cout << "Identifiers: " << identifierCount << endl;
    cout << "Operators: " << operatorCount << endl;
    cout << "Numbers: " << numberCount << endl;
    cout << "Symbols: " << symbolCount << endl;
    cout << "Total Tokens: " << totalTokens << endl;
}

int main() {
    string filename;
    cout << "Enter the filename containing C code: ";
    cin >> filename;

    lexicalAnalysis(filename);

    return 0;
}
