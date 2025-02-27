%{
#include<stdio.h>
#include<string.h>

void printToken(char *type, char *lexeme) {
    printf("%s: %s\n", type, lexeme);
}
%}

/* Regular Definitions for Lexical Tokens */
whitespace    [ \t\n\r]+
keyword       (int|float|char|double|return|if|else|while|for|break|continue|void|main)
identifier    [a-zA-Z_][a-zA-Z0-9_]*
constant      [0-9]+
string        \"[^\"]*\"
character     \'[^\']\'
operator      [+\-*/=<>!&|]
punctuation   [;,\(\)\{\}]
comment_single \/\/.*
comment_multi  \/\*([^*]|\*+[^*/])*\*+\/
error         .

%%

{whitespace}     {/* ignore */}  
{keyword}        { printToken("Keyword", yytext); }
{identifier}     { printToken("Identifier", yytext); }
{constant}       { printToken("Constant", yytext); }
{string}         { printToken("String", yytext); }
{character}      { printToken("Character", yytext); }
{operator}       { printToken("Operator", yytext); }
{punctuation}    { printToken("Punctuation", yytext); }
{comment_single} {/* ignore single-line comment */}  
{comment_multi}  {/* ignore multi-line comment */}  
{error}          { printToken("Lexical Error", yytext); }

%%

int yywrap() {
    return 1; // No more input to read
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Cannot open file");
            return 1;
        }
        yyin = file;  // Use input file
    }

    yylex();  // Start lexical analysis
    return 0;
}
