#ifndef _SYNTAX
#define _SYNTAX

#include "token.h"

typedef enum _ARITHMATIC_TYPE {
	FLOAT,
	INT,
	UINT,
	BOOL,
} ARITHMATIC_TYPE;

typedef enum _EXPRESSION_TYPE {
	LITERAL,
	VARIABLE,
	OPERATION,
	ASSIGNMENT,
} EXPRESSION_TYPE;

typedef struct _Declaration Declaration, *PDeclaration;

typedef struct _Assignment Assignment, *PAssignment;

typedef struct _Operation Operation, *POperation;

typedef struct _Literal Literal, *PLiteral;

typedef struct _Variable Variable, *PVariable;

typedef struct _Expression Expression, *PExpression;

struct _Declaration {
	ARITHMATIC_TYPE arithmaticType;
	size_t size;
	char* name;
};

struct _Assignment {
	char* name;
	PExpression expression;
};

struct _Operation {
	PExpression left;
	PExpression right;
	char* name;
};

struct _Literal {
	ARITHMATIC_TYPE arithmaticType;
	size_t size;
	union {
		double f;
		long long i;
		unsigned long long u;
	} value;
};

struct _Variable {
	char* name;
};

struct _Expression {
	EXPRESSION_TYPE type;
	union {
		PAssignment asignment;
		POperation operation;
		PLiteral literal;
	} expression;
};

#endif