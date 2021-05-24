#ifndef _LEXER
#define _LEXER

#include <stdio.h>

#include "token.h"
#include "file_reader.h"

int lex(PTokenList list, PFileReader file);

#endif