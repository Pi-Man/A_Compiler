#include <malloc.h>

#include "token.h"

const char* __keywords[] = {
	"int",
	"float",
	"ptr",
	"return",
	"void",
	"operator",
	""
};

PTokenList newTokenList() {
	PTokenList list = (PTokenList)malloc(sizeof(TokenList));
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return list;
}

int appendToList(PTokenList list, Token token) {

	PTokenListEntry newEntry = (PTokenListEntry)malloc(sizeof(TokenListEntry));

	if (newEntry == NULL) {
		return -1;
	}

	newEntry->next = NULL;
	newEntry->prev = list->tail;
	newEntry->token = token;

	if (list->head == NULL) {
		list->head = newEntry;
	}

	if (list->tail != NULL) {
		list->tail->next = newEntry;
	}
	list->tail = newEntry;

	list->size++;

	return 0;
}