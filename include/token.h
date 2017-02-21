#ifndef TOKEN_H_
#define TOKEN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* restores the formatting of a tokenized file and places the result in */
/* the same directory as the input file with a .c extension */
void restoreFormatting(FILE *input, char *fileName);

/* tokenizes an input file and places the result in a file called tokenizedCode.c */
void tokenizeFile(FILE *input, FILE *output);

#endif
