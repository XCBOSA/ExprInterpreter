// Code file created by C Code Develop

#include "stdio.h"
#include "stdlib.h"
#include "debug.h"
#include "math.h"
#include "expr.h"

double ParseFuncCall(LexState &lex) {
    Token funcName = LexNext(lex);
    if (LexNext(lex) .type != TokenOpenBracket) {
        printf("Parse: Invaild ( during function %s call\n", funcName.identifier);
        LexPush(lex, SharedTokenEOF);
        return 0;
    }
    Token argList[128];
    int argId = 0;
    while (TRUE) {
        if (LexEOF(lex)) {
            printf("Parse: Expected ), but got EOF\n");
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        Token numResult;
        numResult.number = ParseValue(lex);
        argList[argId++] = numResult;
        if (LexPeek(lex) .type == TokenComma) {
            LexNext(lex);
            continue;
        } else if (LexPeek(lex) .type == TokenCloseBracket) {
            LexNext(lex);
            break;
        } else {
            printf("Parse: Invaild ) or , during function %s call\n", funcName.identifier);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
    }
    int argLen = argId;
    if (strcmp(funcName.identifier, "pow") == 0) {
        int requireArgCnt = 2;
        if (argLen != requireArgCnt) {
            printf("Parse: %s() need %d argument, but got %d\n", funcName.identifier, requireArgCnt, argLen);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        return pow(argList[0].number, argList[1].number);
    } else if (strcmp(funcName.identifier, "sin") == 0) {
        int requireArgCnt = 1;
        if (argLen != requireArgCnt) {
            printf("Parse: %s() need %d argument, but got %d\n", funcName.identifier, requireArgCnt, argLen);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        return sin(argList[0].number);
    } else if (strcmp(funcName.identifier, "cos") == 0) {
        int requireArgCnt = 1;
        if (argLen != requireArgCnt) {
            printf("Parse: %s() need %d argument, but got %d\n", funcName.identifier, requireArgCnt, argLen);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        return cos(argList[0].number);
    } else if (strcmp(funcName.identifier, "tan") == 0) {
        int requireArgCnt = 1;
        if (argLen != requireArgCnt) {
            printf("Parse: %s() need %d argument, but got %d\n", funcName.identifier, requireArgCnt, argLen);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        return tan(argList[0].number);
    } else if (strcmp(funcName.identifier, "asin") == 0) {
        int requireArgCnt = 1;
        if (argLen != requireArgCnt) {
            printf("Parse: %s() need %d argument, but got %d\n", funcName.identifier, requireArgCnt, argLen);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        return asin(argList[0].number);
    } else if (strcmp(funcName.identifier, "acos") == 0) {
        int requireArgCnt = 1;
        if (argLen != requireArgCnt) {
            printf("Parse: %s() need %d argument, but got %d\n", funcName.identifier, requireArgCnt, argLen);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        return acos(argList[0].number);
    } else if (strcmp(funcName.identifier, "atan") == 0) {
        int requireArgCnt = 1;
        if (argLen != requireArgCnt) {
            printf("Parse: %s() need %d argument, but got %d\n", funcName.identifier, requireArgCnt, argLen);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        return atan(argList[0].number);
    } else if (strcmp(funcName.identifier, "sinh") == 0) {
        int requireArgCnt = 1;
        if (argLen != requireArgCnt) {
            printf("Parse: %s() need %d argument, but got %d\n", funcName.identifier, requireArgCnt, argLen);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        return sinh(argList[0].number);
    } else if (strcmp(funcName.identifier, "cosh") == 0) {
        int requireArgCnt = 1;
        if (argLen != requireArgCnt) {
            printf("Parse: %s() need %d argument, but got %d\n", funcName.identifier, requireArgCnt, argLen);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        return cosh(argList[0].number);
    } else if (strcmp(funcName.identifier, "tanh") == 0) {
        int requireArgCnt = 1;
        if (argLen != requireArgCnt) {
            printf("Parse: %s() need %d argument, but got %d\n", funcName.identifier, requireArgCnt, argLen);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        return tanh(argList[0].number);
    } else if (strcmp(funcName.identifier, "exp") == 0) {
        int requireArgCnt = 1;
        if (argLen != requireArgCnt) {
            printf("Parse: %s() need %d argument, but got %d\n", funcName.identifier, requireArgCnt, argLen);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        return exp(argList[0].number);
    } else if (strcmp(funcName.identifier, "abs") == 0) {
        int requireArgCnt = 1;
        if (argLen != requireArgCnt) {
            printf("Parse: %s() need %d argument, but got %d\n", funcName.identifier, requireArgCnt, argLen);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        return fabs(argList[0].number);
    } else if (strcmp(funcName.identifier, "log") == 0) {
        int requireArgCnt = 2;
        if (argLen != requireArgCnt) {
            printf("Parse: %s() need %d argument, but got %d\n", funcName.identifier, requireArgCnt, argLen);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        return log(argList[0].number) / log(argList[1].number);
    } else if (strcmp(funcName.identifier, "ln") == 0) {
        int requireArgCnt = 1;
        if (argLen != requireArgCnt) {
            printf("Parse: %s() need %d argument, but got %d\n", funcName.identifier, requireArgCnt, argLen);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        return log(argList[0].number);
    } else if (strcmp(funcName.identifier, "lg") == 0) {
        int requireArgCnt = 1;
        if (argLen != requireArgCnt) {
            printf("Parse: %s() need %d argument, but got %d\n", funcName.identifier, requireArgCnt, argLen);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        return log10(argList[0].number);
    } else if (strcmp(funcName.identifier, "sqrt") == 0) {
        int requireArgCnt = 1;
        if (argLen != requireArgCnt) {
            printf("Parse: %s() need %d argument, but got %d\n", funcName.identifier, requireArgCnt, argLen);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        return sqrt(argList[0].number);
    } else if (strcmp(funcName.identifier, "round") == 0) {
        int requireArgCnt = 1;
        if (argLen != requireArgCnt) {
            printf("Parse: %s() need %d argument, but got %d\n", funcName.identifier, requireArgCnt, argLen);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        return round(argList[0].number);
    } else if (strcmp(funcName.identifier, "ceil") == 0) {
        int requireArgCnt = 1;
        if (argLen != requireArgCnt) {
            printf("Parse: %s() need %d argument, but got %d\n", funcName.identifier, requireArgCnt, argLen);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        return ceil(argList[0].number);
    } else if (strcmp(funcName.identifier, "floor") == 0) {
        int requireArgCnt = 1;
        if (argLen != requireArgCnt) {
            printf("Parse: %s() need %d argument, but got %d\n", funcName.identifier, requireArgCnt, argLen);
            LexPush(lex, SharedTokenEOF);
            return 0;
        }
        return floor(argList[0].number);
    }
    else {
        printf("Parse: Unknown function %s, you can declare more function in source %s:%d\n", funcName.identifier, __xdb_current_filename(), __xdb_current_line());
        LexPush(lex, SharedTokenEOF);
        return 0;
    }
}

double ParseValue(LexState &lex) {
    if (LexPeek(lex).type == TokenIdentifier) {
        return ParseFuncCall(lex);
    } else {
        return ParseInfix(lex);
    }
}
