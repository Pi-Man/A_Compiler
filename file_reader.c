#define _CRT_SECURE_NO_WARNINGS

#include <malloc.h>
#include <limits.h>

#include "file_reader.h"

PFileReader fropen(char* fileName, size_t bufferSize) {

	PFileReader file = malloc(sizeof(FileReader));

	if (file == NULL) {
		return NULL;
	}

	file->file = fopen(fileName, "rb");

	if (file->file == NULL) {
		return NULL;
	}

	file->bufferSize = bufferSize;
	file->buffer = malloc(sizeof(char) * file->bufferSize);
	file->pos = 0;

	size_t count = fread(file->buffer, sizeof(char), file->bufferSize, file->file);
	if (feof(file->file)) {
		file->eof = count;
	}
	else {
		file->eof = LLONG_MAX;
	}

	return file;
}

char frread(PFileReader file, const fpos_t pos) {

	if (pos >= file->eof) {
		return EOF;
	}

	fpos_t adjPos = pos - file->pos;

	if (adjPos >= 0 && adjPos < file->bufferSize) {
		return file->buffer[adjPos];
	}
	else {
		fpos_t oldPos = file->pos;
		file->pos = pos / file->bufferSize * file->bufferSize;
		if (fsetpos(file->file, &file->pos)) {
			file->pos = oldPos;
			return EOF;
		}
		size_t count = fread(file->buffer, sizeof(char), file->bufferSize, file->file);
		if (feof(file->file)) {
			file->eof = file->pos + count;
		}
		return frread(file, pos);
	}
}

int frclose(PFileReader file) {
	int i = fclose(file->file);
	free(file);
	return i;
}
