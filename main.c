#include "lexer.h"

int main(int argc, char** args) {

	char* fileName = "testFile.a";

	PTokenList list = newTokenList();

	PFileReader file = fropen(fileName, 10);

	lex(list, file);

	frclose(file);
	puts("pos\ttext\ttype");
	for (PTokenListEntry entry = list->head; entry != NULL; entry = entry->next) {
		if (entry->token.type != WHITE_SPACE) {
			printf("%d:\t%s\t(%d)\n", entry->token.position, entry->token.text, entry->token.type);
		}
	}

}