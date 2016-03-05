#ifndef GUTTURAL_LEXER_H
#define GUTTURAL_LEXER_H

enum TokenType {
    NUMBER,
    PLUS,
    MINUS,
    FUNCTION
};

typedef struct Token {
    TokenType type;
    int start;
} Token;

void set_input (char * input);
Token lex (void);

#endif
