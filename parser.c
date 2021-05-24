#include <string.h>

#include "parser.h"

#define PEAK_NEXT (entry->next->token)
#define NEXT ((entry = entry->next)->token)
#define CURR (entry->token)
#define PREV ((entry = entry->prev)->token)
#define PEAK_PREV (entry->prev->token)

PTokenListEntry entry;

PDeclaration parseDeclaration() {
	PDeclaration declaration = malloc(sizeof(Declaration));
	switch (CURR.type) {
	case KEYWORD:
		if (strcmp(CURR.text, "float")) {
			declaration->arithmaticType = FLOAT;
		}
		else if (strcmp(CURR.text, "int")) {
			declaration->arithmaticType = FLOAT;
		}
		else return NULL;
		if (NEXT.type == COLON && NEXT.type == INT_LITERAL) {
			declaration->size = CURR.value.u;
			if (NEXT.type == COLON && NEXT.type == IDENTIFIER) {
				declaration->name = CURR.text;
				switch (NEXT.type) {
				case SEMI_COLON:
					return declaration;
				default:
					break;
				}
			}
			else return NULL;
		}
		else return NULL;
	case IDENTIFIER:
		declaration->name = CURR.text;
		if (NEXT.type == COLON && NEXT.type == KEYWORD) {
			if (strcmp(CURR.text, "float")) {
				declaration->arithmaticType = FLOAT;
			}
			else if (strcmp(CURR.text, "int")) {
				declaration->arithmaticType = FLOAT;
			}
			else return NULL;
			return declaration;
		}
		else return NULL;
	default:
		return NULL;
	}
}

PAssignment parseAsignment() {
	PAssignment asignment = malloc(sizeof(asignment));
	if (PEAK_PREV.type == IDENTIFIER) {
		asignment->name = PEAK_PREV.text;
		asignment->expression = parseExpression(NEXT);
		if (asignment->expression == NULL) {
			return NULL;
		}
		else return asignment;
	}
	return NULL;
}

PExpression parseExpression() {
	PExpression expression = malloc(sizeof(Expression));
	switch (CURR.type) {
	case INT_LITERAL:
	case FLOAT_LITERAL:
	case STRING_LITERAL:
		switch (NEXT.type) {
		case SEMI_COLON:
			PREV;
			expression->type = LITERAL;
			expression->expression.literal = parseLiteral();
			return expression;
		case EQUALS:
			expression->type = ASSIGNMENT;
			expression->expression.asignment = parseAsignment();
		case IDENTIFIER:
			expression->type = OPERATION;
			expression->expression.operation = parseOperation();
		}
	case IDENTIFIER:
		switch (NEXT.type) {
		case SEMI_COLON:
			PREV;
			expression->type = VARIABLE;
			expression->expression.literal = parseVariable();
			return expression;
		case EQUALS:
			expression->type = ASSIGNMENT;
			expression->expression.asignment = parseAsignment();
		case IDENTIFIER:
			expression->type = OPERATION;
			expression->expression.operation = parseOperation();
		}
	default:
		return NULL;
	}
}

PLiteral parseLiteral() {
	PLiteral literal = malloc(sizeof(Literal));
	switch (CURR.type) {
	case INT_LITERAL:
		if (NEXT.type == IDENTIFIER) {
			if (strcmp(CURR.text, "i1") == 0) {
				literal->arithmaticType = INT;
				literal->size = 1;
				literal->value.i = CURR.value.i;
			}
			else if (strcmp(CURR.text, "i2") == 0) {
				literal->arithmaticType = INT;
				literal->size = 2;
				literal->value.i = CURR.value.i;
			}
			else if (strcmp(CURR.text, "i4") == 0) {
				literal->arithmaticType = INT;
				literal->size = 4;
				literal->value.i = CURR.value.i;
			}
			else if (strcmp(CURR.text, "i8") == 0) {
				literal->arithmaticType = INT;
				literal->size = 8;
				literal->value.i = CURR.value.i;
			}
			else if (strcmp(CURR.text, "u1") == 0) {
				literal->arithmaticType = UINT;
				literal->size = 1;
				literal->value.i = CURR.value.i;
			}
			else if (strcmp(CURR.text, "u2") == 0) {
				literal->arithmaticType = UINT;
				literal->size = 2;
				literal->value.i = CURR.value.i;
			}
			else if (strcmp(CURR.text, "u4") == 0) {
				literal->arithmaticType = UINT;
				literal->size = 4;
				literal->value.i = CURR.value.i;
			}
			else if (strcmp(CURR.text, "u8") == 0) {
				literal->arithmaticType = UINT;
				literal->size = 8;
				literal->value.i = CURR.value.i;
			}
		}
		else {
			literal->arithmaticType = UINT;
			literal->size = 8;
			literal->value.u = CURR.value.u;
		}
		return literal;
	case FLOAT_LITERAL:
		if (NEXT.type == IDENTIFIER) {
			if (strcmp(CURR.text, "f4") == 0) {
				literal->arithmaticType = FLOAT;
				literal->size = 4;
				literal->value.f = CURR.value.f;
			}
			else if (strcmp(CURR.text, "f8") == 0) {
				literal->arithmaticType = FLOAT;
				literal->size = 8;
				literal->value.f = CURR.value.f;
			}
		}
		else {
			literal->arithmaticType = FLOAT;
			literal->size = 8;
			literal->value.f = CURR.value.f;
		}
		return literal;
	case STRING_LITERAL:
		literal->arithmaticType = UINT;
		literal->size = 8;
		literal->value.u = NEXT.value.u;
		return literal;
	default:
		return NULL;
	}
}

PVariable parseVariable() {
	PVariable variable = malloc(sizeof(Variable));
	switch (CURR.type) {
	case IDENTIFIER:
		variable->name = CURR.text;
		return variable;
	default:
		return NULL;
	}
}

POperation parseOperation() {
	POperation operation = malloc(sizeof(Operation));

}



int parse(PTokenList list) {

	entry = list->head;

	return 0;
}

//int parse(PTokenList list) {
//	for (PTokenListEntry entry = list->head; entry != NULL; entry = entry->next) {
//		switch (entry->token.type) {
//		case WHITE_SPACE:
//			break;
//		case KEYWORD:
//			if (strcmp(entry->token.text, "float") == 0 || strcmp(entry->token.text, "int") == 0) {
//				if (entry->next->token.type == COLON && entry->next->next->token.type == INT_LITERAL) {
//					puts("type declaration");
//					entry = entry->next->next;
//				}
//			}
//			break;
//		case INT_LITERAL:
//			if (entry->next->token.type == IDENTIFIER) {
//				if (strcmp(entry->next->token.text, "i1") == 0) {
//					puts("byte literal");
//					entry = entry->next;
//				}
//				else if (strcmp(entry->next->token.text, "i2") == 0) {
//					puts("short literal");
//					entry = entry->next;
//				}
//				else if (strcmp(entry->next->token.text, "i4") == 0) {
//					puts("int literal");
//					entry = entry->next;
//				}
//				else if (strcmp(entry->next->token.text, "i8") == 0) {
//					puts("long literal");
//					entry = entry->next;
//				}
//				else if (strcmp(entry->next->token.text, "u1") == 0) {
//					puts("ubyte literal");
//					entry = entry->next;
//				}
//				else if (strcmp(entry->next->token.text, "u2") == 0) {
//					puts("ushort literal");
//					entry = entry->next;
//				}
//				else if (strcmp(entry->next->token.text, "u4") == 0) {
//					puts("uint literal");
//					entry = entry->next;
//				}
//				else if (strcmp(entry->next->token.text, "u8") == 0) {
//					puts("ulong literal");
//					entry = entry->next;
//				}
//			}
//			puts("INT literal");
//			break;
//		case FLOAT_LITERAL:
//			if (entry->next->token.type == IDENTIFIER) {
//				if (strcmp(entry->next->token.text, "f4") == 0) {
//					puts("float literal");
//					entry = entry->next;
//				}
//				else if (strcmp(entry->next->token.text, "f8") == 0) {
//					puts("double literal");
//					entry = entry->next;
//				}
//			}
//			puts("FLOAT literal");
//			break;
//		case STRING_LITERAL:
//			break;
//		case IDENTIFIER:
//			if (entry->next->token.type == COLON && (strcmp(entry->next->token.text, "float") == 0 || strcmp(entry->next->token.text, "int")) == 0 && entry->next->next->token.type == COLON && entry->next->next->next->token.type == INT_LITERAL) {
//				puts("name type declaration");
//				entry = entry->next->next->next;
//			}
//			break;
//		case COLON:
//			puts("syntax error");
//			break;
//		case SEMI_COLON:
//			puts("end of statement");
//			break;
//		case EQUALS:
//			if (entry->next->token.type == EQUALS) {
//				puts("equality");
//			}
//			else {
//				puts("assignment");
//			}
//			break;
//		case STAR:
//			if (entry->next->token.type == EQUALS) {
//				puts("mul assignment");
//				entry = entry->next;
//			}
//			else {
//				puts("multiplication");
//			}
//			break;
//		case PLUS:
//			if (entry->next->token.type == EQUALS) {
//				puts("add assignment");
//				entry = entry->next;
//			}
//			else {
//				puts("addition");
//			}
//			break;
//		case MINUS:
//			if (entry->next->token.type == EQUALS) {
//				puts("sub assignment");
//				entry = entry->next;
//			}
//			else {
//				puts("subtraction");
//			}
//			break;
//		case CAROT:
//			if (entry->next->token.type == EQUALS) {
//				puts("bit xor assignment");
//				entry = entry->next;
//			}
//			else {
//				puts("bitwise xor");
//			}
//			break;
//		case AND:
//			if (entry->next->token.type == AND) {
//				puts("boolean and");
//				entry = entry->next;
//			}
//			else {
//				puts("bitwise and");
//			}
//			break;
//		case OR:
//			if (entry->next->token.type == OR) {
//				puts("boolean or");
//				entry = entry->next;
//			}
//			else {
//				puts("bitwise or");
//			}
//			break;
//		case PERCENT:
//			break;
//		case DOUBLE_QUOTE:
//			break;
//		case SINGLE_QUOTE:
//			break;
//		case FORWARD_SLASH:
//			break;
//		case BACK_SLASH:
//			break;
//		case QUESTION:
//			break;
//		case BANG:
//			break;
//		case OPEN_BRACE:
//			break;
//		case CLOSE_BRACE:
//			break;
//		case OPEN_BRACKET:
//			break;
//		case CLOSE_BRACKET:
//			break;
//		case OPEN_PARENTHESES:
//			break;
//		case CLOSE_PARENTHESES:
//			break;
//		case OPEN_CAROT:
//			break;
//		case CLOSE_CAROT:
//			break;
//		default:
//			break;
//		}
//	}
//}
