//
// Created by malan on 6/16/2024.
//

#ifndef NOWCLAIRE_SCAN_H
#define NOWCLAIRE_SCAN_H

enum TokType {
    TOK_GT, TOK_LT,
    TOK_LBRACE, TOK_RBRACE,
    TOK_EQ,
    TOK_DQUOTE, TOK_SQUOTE,
    TOK_SLASH,
    TOK_DOLLAR,

    TOK_ID,
    TOK_STRING,

    TOK_INCLUDE, TOK_MD_INCLUDE,
    TOK_MD,
    TOK_TEMPLATE,
    TOK_BLOCK, TOK_SLOT,

    TOK_EOF,
};

typedef struct {
    enum TokType type;
    char *lexeme;
    char *literal;
    int line;
} Token;

#endif //NOWCLAIRE_SCAN_H
