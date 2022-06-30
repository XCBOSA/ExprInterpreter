// Code file created by C Code Develop

#include "stdio.h"
#include "stdlib.h"
#include "expr.h"

int getOpLevel(TokenType op) {
    switch (op) {
        case TokenPlus: return 1;
        case TokenMinus: return 1;
        case TokenMult: return 2;
        case TokenDiv: return 2;
        default: return 0;
    }
}

double ParseInfix(LexState &lex) {
    Token infix[128];
    int infixId = 0;
    int deep = 0;
    
    while (!LexEOF(lex)) {
        if (LexPeek(lex) .type == TokenOpenBracket) {
            Token tk = LexNext(lex);
            infix[infixId++] = tk;
            deep++;
        }
        else if (LexPeek(lex) .type == TokenCloseBracket) {
            if (--deep < 0) {
                break;
            }
            Token tk = LexNext(lex);
            infix[infixId++] = tk;
        }
        else if (LexPeek(lex) .type == TokenComma) {
            break;
        }
        else if (LexPeek(lex) .type == TokenIdentifier) {
            double funcReturn = ParseFuncCall(lex);
            Token tk = { TokenNumber, "", funcReturn };
            itoa(tk.number, tk.identifier, 10);
            infix[infixId++] = tk;
        }
        else {
            infix[infixId++] = LexNext(lex);
        }
    }
    
    Token opStack[128];
    Token postfix[128];
    int opStackId = 0, postfixId = 0;
    for (int i = 0; i < infixId; i++) {
        Token token = infix[i];
        if (token.type == TokenNumber) {
            postfix[postfixId++] = token;
        }
        else if (token.type == TokenOpenBracket) {
            opStack[opStackId++] = token;
        }
        else if (token.type == TokenCloseBracket) {
            _Bool meetOpenBracket = FALSE;
            while (opStackId > 0) {
                int id = --opStackId;
                Token op = opStack[id];
                if (op.type == TokenOpenBracket) {
                    meetOpenBracket = TRUE;
                    break;
                } else {
                    postfix[postfixId++] = op;
                }
            }
            if (!meetOpenBracket) {
                printf("Infix: Invaild ), no ( matching\n");
                LexPush(lex, SharedTokenEOF);
                return 0;
            }
        }
        else {
            int level = getOpLevel(token.type);
            if (level == 0) {
                char typeName[128];
                TokenTypeName(token.type, typeName, sizeof(typeName));
                printf("Infix: Invaild token %s in infix statement\n", typeName);
                return 0;
            }
            while (opStackId > 0) {
                int id = --opStackId;
                Token op = opStack[id];
                if (op.type == TokenOpenBracket || getOpLevel(op.type) < level) {
                    opStack[opStackId++] = op;
                    break;
                } else {
                    postfix[postfixId++] = op;
                }
            }
            opStack[opStackId++] = token;
        }
    }
    while (opStackId > 0) {
        int id = --opStackId;
        Token op = opStack[id];
        postfix[postfixId++] = op;
    }
    
    Token valStack[128];
    int valStackId = 0;
    for (int i = 0; i < postfixId; i++) {
        Token tk = postfix[i];
        if (tk.type == TokenNumber) {
            valStack[valStackId++] = tk;
        }
        else if (tk.type >= TokenPlus && tk.type <= TokenDiv) {
            if (valStackId < 2) {
                printf("Infix: Postfix evaluate error, should be 2 number before op\n");
                LexPush(lex, SharedTokenEOF);
                return 0;
            }
            Token rhs = valStack[--valStackId];
            Token lhs = valStack[--valStackId];
            if (lhs.type != TokenNumber || rhs.type != TokenNumber) {
                printf("Infix: Postfix evaluate error, number is not number\n");
                LexPush(lex, SharedTokenEOF);
                return 0;
            }
            Token result = { TokenNumber, "", 0 };
            switch (tk.type) {
                case TokenPlus:
                result.number = lhs.number + rhs.number;
                break;
                case TokenMinus:
                result.number = lhs.number - rhs.number;
                break;
                case TokenMult:
                result.number = lhs.number * rhs.number;
                break;
                case TokenDiv:
                result.number = lhs.number / rhs.number;
                break;
            }
            valStack[valStackId++] = result;
        }
        else {
            char typeName[128];
            TokenTypeName(tk.type, typeName, sizeof(typeName));
            printf("Infix: Postfix evaluate error, unknown token %s\n", typeName);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
    }
    
    return valStack[--valStackId].number;
}
