%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Counters for each required character type
int lowercase = 0, uppercase = 0, digit = 0, symbol = 0;
int length = 0;

// Allowed symbols set
char allowed_symbols[] = "*;,#$@";

%}

%%
[a-z]       { lowercase++; length++; }
[A-Z]       { uppercase++; length++; }
[0-9]       { digit++; length++; }
[*;,#$@]    { symbol++; length++; }
\n          { return 0; }  // End of input
.           { length++; }  // Other characters count toward length
%%

int main() {
    yylex();

    if (length >= 9 && length <= 15 &&
        lowercase >= 1 &&
        uppercase >= 1 &&
        digit >= 1 &&
        symbol >= 1) {
        printf("Valid password\n");
    } else {
        printf("Invalid password\n");
    }

    return 0;
}

// This fixes your error
int yywrap() {
    return 1;  // Signals end of input
}