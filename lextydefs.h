/*
Code file created by C Code Develop
filesummary.CH: 定义词法单词类型
filesummary.EN: Declare token type for lex
*/

#ifndef LEXTYDEFS_H
#define LEXTYDEFS_H

#include "stdio.h"
#include "stdlib.h"

/*
CH: 表示单词类型
EN: Indicate token type
*/
typedef int TokenType;

/*
CH: 左小括号
EN: Left bracket token
*/
const TokenType TokenOpenBracket = 0;

/*
CH: 右小括号
EN: Right bracket token
*/
const TokenType TokenCloseBracket = 1;

/*
CH: 数字
EN: Number
*/
const TokenType TokenNumber = 2;

/*
CH: 结尾符
EN: End of file
*/
const TokenType TokenEOF = 3;

/*
CH: 加号
EN: Plus
*/
const TokenType TokenPlus = 4;

/*
CH: 减号
EN: Minus
*/
const TokenType TokenMinus = 5;

/*
CH: 乘号
EN: Multipy
*/
const TokenType TokenMult = 6;

/*
CH: 除号
EN: Divide
*/
const TokenType TokenDiv = 7;

/*
CH: 字符串
EN: String literial
*/
const TokenType TokenIdentifier = 8;

/*
CH: 逗号
EN: Comma
*/
const TokenType TokenComma = 9;

void TokenTypeName(TokenType type, char *name, size_t size);

#endif
