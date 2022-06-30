/*
Code file created by C Code Develop
filesummary.CH: 表达式解释器
filesummary.EN: Expression Interpreter
*/

#ifndef EXPR_H
#define EXPR_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "ctype.h"
#include "lextydefs.h"

/*
EN: Declare Token for lex
CH: 定义词法分析阶段的单词
*/
typedef struct {
    TokenType type;
    char identifier[128];
    double number;
} Token;

/*
EN: Indicates the end of file, appear only once.
CH: 表示文件末尾的Token，只会出现一次
*/
const Token SharedTokenEOF = {
    TokenEOF, 
    "", 
};

/*
EN: Declare an lex token state machine
CH: 定义一个词法分析状态机
*/
typedef struct {
    char *code;
    int ptr;
    Token back[128];
    int backptr;
    int len;
    _Bool combineMinus;
} LexState;

/*
CH: 初始化词法分析器
EN: Initialize an lex instance
lex.CH: 词法分析实例
lex.EN: Tokenizer Instance
code.CH: 代码
code.EN: Code
*/
void LexInitialize(LexState &lex, char *code);

/*
CH: 获取词法分析器的下一个单词
EN: Get the next token for lex
lex.CH: 词法分析实例
lex.EN: Tokenizer Instance
*/
Token LexNext(LexState &lex);

/*
CH: 将一个已获取的单词返还给词法分析器
EN: Push a token back to lex
lex.CH: 词法分析实例
lex.EN: Tokenizer Instance
token.CH: 单词
token.EN: Word
*/
Token LexPush(LexState &lex, Token token);

/*
CH: 从词法分析器中查看下一个单词，但不提高单词位置
EN: See the next token in lex, but not change cursor for lex
lex.CH: 词法分析实例
lex.EN: Tokenizer Instance
*/
Token LexPeek(LexState &lex);

/*
CH: 获取是否已经分析到文件末尾
EN: Get is lex analyze to the end of file
lex.CH: 词法分析实例
lex.EN: Tokenizer Instance
*/
_Bool LexEOF(LexState &lex);


/*
CH: 语法分析并计算下一个中缀表达式
EN: Calculate next infix expression
lex.CH: 词法分析实例
lex.EN: Tokenizer Instance
*/
double ParseInfix(LexState &lex);

/*
CH: 语法分析并计算下一个函数调用
EN: Calculate next function call
lex.CH: 词法分析实例
lex.EN: Tokenizer Instance
*/
double ParseFuncCall(LexState &lex);

#endif
