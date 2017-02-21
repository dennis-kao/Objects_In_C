#ifndef DYNAMICSTRINGLIB_H_
#define DYNAMICSTRINGLIB_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "token.h"
#include "storedList.h"

struct textInfo {

  int numLines;
  char **theText;
};
typedef struct textInfo textInfo;

/* appends a string to dynamically allocated string */
/* RETURNS: a pointer to the dynamically allocated string */
char *smartAppend(char *appendToThis, char *addThis);

/* stores all text in the input file to the 2d array in code */
void storeText(FILE *input, textInfo *code);

/* frees the 2d array and the struct */
void freeStoredText(textInfo *code);

/* takes a string and runs it through a tokenizer */
/* RETURNS: a string containing all the toknized code */
char *changeToTokenizedFormat(char *formatMe);

/* inserts a string into a 2d array */
void insertText(char *insertMe, textInfo *code, int insertHereIndex);

/* deletes the line specified by the int*/
void deleteText(textInfo *code, int deleteHereIndex);

/* returns a string containg all text information from start to end */
/* RETURNS: a string containg all text information */
char *saveCode(textInfo *code, int start, int end);

/* determines the position of a corresponding closing bracket, given the position of the opening bracket */
/* RETURNS: the index of the closing bracket */
int indexOfClosingBracket(textInfo *code, int openBracketIndex);

/* prints out all code from a 2d array into an open writable file */
void printToFile(textInfo *code, FILE *output);

/* tokenizes, then inserts a string into the 2d array */
void insertFormatted (char *insertMe, textInfo *code, int insertHereIndex);

/* inserts a string into the 2d array */
void insert (char *insertMe, textInfo *code, int insertHereIndex);

/* gets the next non whitespace non comment keyword */
int nextKeyword(int i, textInfo *code);

/* gets the position of the next open curly bracket */
int openBracketIndex (int i, textInfo *code);

/* i must be pointed to the first word of the (potentially 2 word) data type*/
/* can also detect stars */
/* RETURNS: the index to the next keyword */
int parseDataType(int i, char type[510], textInfo *code);

/* i must be pointed to a star*/
/* RETURNS: the number of stars */
int starCounter(int *i, textInfo *code);

/* deletes lines from a 2d array as specified by the indexes*/
void deleteLines(textInfo *code, int start, int end);

/* appends the first letter of each parameter data type to the string function pointer*/
void appendParameters(localFun *newFun, char *functionPointer);

/* generates and copies the modified function name to the string funName */
void functionName(localFun *newFun, char *funName, structInfo *newStruct);

/* copies all text required for a function pointer in a class to the string functionPointer*/
void createFunctionPointer(localFun *newFun, char functionPointer[510], structInfo *newStruct);

/* generates a constructor based on information from the struct */
char *constructor (structInfo *newstruct);

/*  adds information to the appropriate data structures*/
/*  replaces functions with function pointers*/
/*  renames functions*/
void parseStruct(textInfo *code, int openBracket, int closingBracket, structInfo *newStruct);

/* replaces all class variable references in a function with the appropriate C code */
void addClassScopeToFun(structInfo *parentStruct);

/* inserts the constructor to a object at the specified location*/
int insertCon(textInfo *code, structInfo *newStruct, int insertHere, structInfo *structList);

/* stores all local variables in a function in a linked list*/
void storeLocalVariablesInFun(localFun *fun);

/* stores all local variables in a class in the linked list*/
void parseLocalVariables(structInfo *structList);

/* a big piece of code which is responsible for: */
/* storing all variable information */
/* moving functions out of a class */
/* inserting constructor functions */
/* changing all instances of class to struct */
/* RETURNS: the head of the linked list containing all struct information */
structInfo *classToStruct(textInfo *code, structInfo *structList);

int isInParamList(localFun *fun, char *potentialIdentifier);
int isLocalToFun(localFun *fun, char *potentialIdentifier);
int isClassVariable(structInfo *theStruct, char *potentialIdentifier);

int isAMethod(char *methodName, char *objectName, structInfo *structList, localVar *classInMain);
int isADeclaredClass(char *compareMe, localVar *list);

/* generates the constructor call for each class declaration in the main function */
void generateConstructorCall(char *storage, char *classType, char *name, structInfo *structList);

/* finds the appropriate modified method name for a declared class and stores it in the string "stroage" */
void findAndCopyFunction(char *storage, char *methodName, char *objectName, structInfo *structList, localVar *classInMain);

/* handles all the logic for the main function */
/* inserts constructor function calls */
/* modifies method calls so they always include a reference to the struct */
void mainParser(textInfo *code, structInfo *structList);

/* modifies method code to enable the use of internal classes */
void modifyFunCodeForClasses(textInfo *code, structInfo *structList);

#endif
