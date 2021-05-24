#ifndef _FILE_READER
#define _FILE_READER

#include <stdio.h>

typedef struct _FileReader {
	FILE* file;
	size_t bufferSize;
	fpos_t pos;
	fpos_t eof;
	char* buffer;
} FileReader, *PFileReader;

PFileReader fropen(char* fileName, size_t bufferSize);

char frread(PFileReader file, const fpos_t pos);

int frclose(PFileReader file);

#endif