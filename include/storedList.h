#ifndef STOREDLIST_H_
#define STOREDLIST_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "token.h"
#include "storedList.h"

/* A generic linked list library with seperate structs and function for */
/* storing information on functions, structs and variables because I was */
/* too busy hacking away at code to figure out function pointers */

struct localVar{

  char varName[510];
  char varType[510];
  char value[500]; /* used exclusivally for initialized class variables */
  int stars;

  struct localVar *next;
};
typedef struct localVar localVar;

struct localFun{

  char funName[510];
  char returnType[510];
  char *code;
  char *newName;

  int star;

  localVar *parameterList;
  localVar *localVariables;

  struct localFun *next;
};
typedef struct localFun localFun;

struct structInfo{

  char structName[510];
  localVar *varList;
  localFun *funList;

  struct structInfo *next;
};
typedef struct structInfo structInfo;

localFun *createFunction(char funName[510], char returnType[510], int star);
localVar *createVariable(char varName[510], char varType[510], int starCount);
structInfo *createStruct(char structName[510]);

void destroyVarList(localVar *theList);
void destroyFunList(localFun *theList);
void destroyStructList(structInfo *theList);

localVar * addToVarList(localVar * theList, localVar * toBeAdded);
localFun * addToFunList(localFun * theList, localFun * toBeAdded);
structInfo * addToStructList(structInfo * theList, structInfo * toBeAdded);

#endif
