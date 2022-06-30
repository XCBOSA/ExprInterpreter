// Code file created by C Code Develop

#include "stdio.h"
#include "stdlib.h"
#include "expr.h"

void TokenTypeName(TokenType type, char *name, size_t size) {
    switch (type) {
        case TokenOpenBracket:
        char ty[] = "TokenOpenBracket";
        memcpy(name, ty, sizeof(ty));
        break;
        case TokenCloseBracket:
        char ty[] = "TokenCloseBracket";
        memcpy(name, ty, sizeof(ty));
        break;
        case TokenNumber:
        char ty[] = "TokenNumber";
        memcpy(name, ty, sizeof(ty));
        break;
        case TokenEOF:
        char ty[] = "TokenEOF";
        memcpy(name, ty, sizeof(ty));
        break;
        case TokenPlus:
        char ty[] = "TokenPlus";
        memcpy(name, ty, sizeof(ty));
        break;
        case TokenMinus:
        char ty[] = "TokenMinus";
        memcpy(name, ty, sizeof(ty));
        break;
        case TokenMult:
        char ty[] = "TokenMult";
        memcpy(name, ty, sizeof(ty));
        break;
        case TokenDiv:
        char ty[] = "TokenDiv";
        memcpy(name, ty, sizeof(ty));
        break;
        case TokenIdentifier:
        char ty[] = "TokenIdentifier";
        memcpy(name, ty, sizeof(ty));
        break;
        case TokenComma:
        char ty[] = "TokenComma";
        memcpy(name, ty, sizeof(ty));
        break;
        default:
        char ty[] = "TokenUnknown";
        memcpy(name, ty, sizeof(ty));
        break;
    }
}

void LexInitialize(LexState &lex, char *code) {
    lex.code = code;
    lex.ptr = 0;
    lex.backptr = 0;
    lex.len = strlen(code);
    lex.combineMinus = TRUE;
    memset(lex.back, 0, sizeof(lex.back));
}

_Bool LexEOF(LexState &lex) {
    return lex.ptr >= lex.len;
}

char lexNextChar(LexState &lex) {
    if (LexEOF(lex)) {
        return 0;
    }
    return lex.code[lex.ptr++];
}

void lexSkipEmpty(LexState &lex) {
    while (!LexEOF(lex)) {
        char thisCh = lexNextChar(lex);
        if (thisCh == 0) {
            return;
        }
        if (!isspace(thisCh)) {
            lex.ptr--;
            return;
        }
    }
}

_Bool isNumberOrPoint(char ch) {
    return isnumber(ch) || ch == '.';
}

Token LexNext(LexState &lex) {
    if (lex.backptr > 0) {
        Token token = lex.back[0];
        for (int i = 1; i < lex.backptr; i++) {
            lex.back[i - 1] = lex.back[i];
        }
        lex.backptr--;
        return token;
    }
    
    lexSkipEmpty(lex);
    char ch = lexNextChar(lex);
    Token token;
    memset(token.identifier, 0, sizeof(token.identifier));
    
    if (isnumber(ch) || (ch == '-' && lex.combineMinus)) {
        token.identifier[0] = ch;
        token.type = TokenNumber;
        int idIndex = 1;
        int pointNum = 0;
        while (isNumberOrPoint(ch = lexNextChar(lex))) {
            if (ch == '.') {
                pointNum++;
            }
            token.identifier[idIndex++] = ch;
        }
        if (pointNum > 1 || token.identifier[idIndex - 1] == '.') {
            printf("Lex: Invaild number %s\n", token.identifier);
            return SharedTokenEOF;
        }
        if (ch == 0) {
            lex.combineMinus = FALSE;
            token.number = atof(token.identifier);
            return token;
        }
        lex.ptr--;
        lex.combineMinus = FALSE;
        token.number = atof(token.identifier);
        return token;
    }
    
    if (isalpha(ch)) {
        token.identifier[0] = ch;
        token.type = TokenIdentifier;
        int idIndex = 1;
        while (isalpha(ch = lexNextChar(lex))) {
            token.identifier[idIndex++] = ch;
        }
        if (!LexEOF(lex)) {
            lex.ptr--;
        }
        lex.combineMinus = FALSE;
        return token;
    }
    
    switch (ch) {
        case 0: return SharedTokenEOF;
        case '(':
        token.type = TokenOpenBracket;
        lex.combineMinus = TRUE;
        return token;
        case ')':
        token.type = TokenCloseBracket;
        lex.combineMinus = FALSE;
        return token;
        case '+':
        token.type = TokenPlus;
        lex.combineMinus = FALSE;
        return token;
        case '-':
        token.type = TokenMinus;
        lex.combineMinus = FALSE;
        return token;
        case '*':
        token.type = TokenMult;
        lex.combineMinus = FALSE;
        return token;
        case '/':
        token.type = TokenDiv;
        lex.combineMinus = FALSE;
        return token;
        case ',':
        token.type = TokenComma;
        lex.combineMinus = TRUE;
        return token;
    }
    
    printf("Lex: Unknown character %c\n", ch);
    return SharedTokenEOF;
}

void LexPush(LexState &lex, Token token) {
    lex.back[lex.backptr++] = token;
}

Token LexPeek(LexState &lex) {
    Token tk = LexNext(lex);
    LexPush(lex, tk);
    return tk;
}
