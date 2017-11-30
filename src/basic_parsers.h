#ifndef __BASIC_PARSERS_H__
#define __BASIC_PARSERS_H__

#include "ast.h"

void ignoreWhitespace(Context* context);
const char* matchLiterals(Context* context, const char** choices, const int);
bool matchLiteral(Context* context, const char* literal);
bool matchNumber(Context* context, char* token);
int parseIdentifier(Context* context, char* token);
int strToOp(const char* str);
const char* opToStr(int op);

#endif