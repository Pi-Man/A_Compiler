#include <stdbool.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#include "lexer.h"

inline char* readLine(FILE *file) {
	fpos_t pos;
	fgetpos(file, &pos);
}

inline bool isWhiteSpace(char c) {
	return c == ' ' || c == '\r' || c == '\n' || c == '\t';
}

inline bool isCharacter(char c, bool firstChar) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || (c == '-' && !firstChar);
}

inline bool isNumeric(char c, bool decimal) {
	return (c >= '0' && c <= '9') || (c == '.' && decimal);
}

inline char* isNumber(PFileReader file, fpos_t pos) {
	if (!isNumeric(frread(file, pos), false)) {
		return NULL;
	}
	char* word;
	fpos_t i = 0;
	bool decimal = true;
	while (isNumeric(frread(file, pos + i), decimal)) {
		if (frread(file, pos + i) == '.') decimal = false;
		i++;
	}
	word = calloc(i + 1, sizeof(char));
	for (fpos_t j = 0; j < i; j++) {
		word[j] = frread(file, pos + j);
	}
	return word;
}

inline char* isWord(PFileReader file, fpos_t pos) {
	if (!isCharacter(frread(file, pos), true)) {
		return NULL;
	}
	char* word;
	fpos_t i = 0;
	while (isCharacter(frread(file, pos + i), i == 0)) i++;
	word = calloc(i + 1, sizeof(char));
	for (fpos_t j = 0; j < i; j++) {
		word[j] = frread(file, pos + j);
	}
	return word;
}

inline bool isKeyword(const char* word) {
	for (int i = 0; __keywords[i][0] != '\0'; i++) {
		if (strcmp(word, __keywords[i]) == 0) return true;
	}
	return false;
}

int lex(PTokenList list, PFileReader file) {
	char* word;
	fpos_t pos = 0;
	while (frread(file, pos) != EOF) {
		Token token;
		token.position = pos;
		if (isWhiteSpace(frread(file, pos))) {
			token.text = calloc(2, sizeof(char));
			token.text[0] = token.value.i = frread(file, pos);
			token.type = WHITE_SPACE;
			pos++;
		}
		else if (word = isNumber(file, pos)) {
			token.text = word;
			if (strchr(word, '.')) {
				token.value.f = atof(word);
			}
			else {
				token.value.u = atoll(word);
			}
			pos += strlen(word);
		}
		else if (word = isWord(file, pos)) {
			token.text = word;
			if (isKeyword(word)) {
				token.type = KEYWORD;
			}
			else {
				token.type = IDENTIFIER;
			}
			pos += token.value.u = strlen(word);
		}
		else {
			char c = frread(file, pos);
			token.text = calloc(2, sizeof(char));
			token.text[0] = token.value.i = c;
			if (isWhiteSpace(c)) {
				token.type = WHITE_SPACE;
			}
			else {
				token.type = (TOKEN_TYPE)c;
			}
			pos++;
		}
		appendToList(list, token);
	}

	return 0;
}