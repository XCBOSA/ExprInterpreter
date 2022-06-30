// Code file created by C Code Develop

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "expr.h"

const size_t CodeSize = 1024 * 1024;

int main(int argc, char **argv)
{
    printf("Expression Calculator (Interpreter)\n");
    printf("Expression Like: -1 + round(sin(3.14 - asin(1) / 2)) * 2\n");
    while (true) {
        char *code = malloc(CodeSize);
        memset(code, 0, CodeSize);
        printf("Please input expression: ");
        gets(code);
        
        // 初始化词法分析器
        LexState lex;
        LexInitialize(lex, code);
        
        printf("-------- Lex --------\n");
        char type[128];
        while (!LexEOF(lex)) {
            Token tk = LexNext(lex);
            TokenTypeName(tk.type, type, sizeof(type));
            printf("%s %s\n", type, tk.identifier);
        }
        
        printf("-------- Parser --------\n");
        LexInitialize(lex, code);
        double result = ParseInfix(lex);
        printf("Result = %lf\n", result);
        
        free(code);
    }
    return 0;
}
