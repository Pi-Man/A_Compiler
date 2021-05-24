#ifndef _PARSER
#define _PARSER

#include "token.h"
#include "syntax.h"

PDeclaration parseDeclaration();

PAssignment parseAsignment();

PExpression parseExpression();

PLiteral parseLiteral();

PVariable parseVariable();

POperation parseOperation();

int parse(PTokenList list);

#endif