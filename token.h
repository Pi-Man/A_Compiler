#ifndef _TOKEN
#define _TOKEN

#include <stdio.h>

typedef enum _TOKEN_TYPE {
	WHITE_SPACE,
	KEYWORD,
	INT_LITERAL,
	FLOAT_LITERAL,
	STRING_LITERAL,
	IDENTIFIER,

	COLON = ':',
	SEMI_COLON = ';',
	EQUALS = '=',
	STAR = '*',
	PLUS = '+',
	MINUS = '-',
	CAROT = '^',
	AND = '&',
	OR = '|',
	PERCENT = '%',
	DOUBLE_QUOTE = '"',
	SINGLE_QUOTE = '\'',
	FORWARD_SLASH = '/',
	BACK_SLASH = '\\',
	QUESTION = '?',
	BANG = '!',
	OPEN_BRACE = '{',
	CLOSE_BRACE = '}',
	OPEN_BRACKET = '[',
	CLOSE_BRACKET = ']',
	OPEN_PARENTHESES = '(',
	CLOSE_PARENTHESES = ')',
	OPEN_CAROT = '<',
	CLOSE_CAROT = '>',

} TOKEN_TYPE;

extern const char* __keywords[];

typedef struct _Token {
	fpos_t position;
	char* text;
	union {
		double f;
		long long i;
		unsigned long long u;
	} value;
	TOKEN_TYPE type;
} Token;

typedef struct _TokenListEntry {
	struct _TokenListEntry *prev;
	struct _TokenListEntry *next;
	Token token;
} TokenListEntry, *PTokenListEntry;

typedef struct _TokenList {
	struct _TokenListEntry *head;
	struct _TokenListEntry *tail;
	size_t size;
} TokenList, *PTokenList;

PTokenList newTokenList();

int appendToList(PTokenList list, Token token);

#endif