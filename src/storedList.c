#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storedList.h"

localFun *createFunction(char funName[510], char returnType[510], int star) {

  localFun *newFun = malloc(sizeof(localFun));

  if (newFun == NULL) {
    printf("Couldn't allocate space for local function\n");
    exit(1);
  }

  strcpy(newFun->funName, funName);
  strcpy(newFun->returnType, returnType);

  newFun->code = NULL;
  newFun->parameterList = NULL;
  newFun->localVariables = NULL;
  newFun->star = star;

  newFun->next = NULL;

  return newFun;
}

localVar *createVariable(char varName[510], char varType[510], int starCount) {

  localVar *newVar = malloc(sizeof(localVar));

  if (newVar == NULL) {
    printf("Couldn't allocate space for local variable\n");
    exit(1);
  }

  strcpy(newVar->varName, varName);
  strcpy(newVar->varType, varType);
  newVar->stars = starCount;
  newVar->value[0] = '\0';

  newVar->next = NULL;

  return newVar;
}

structInfo *createStruct(char structName[510]) {

  structInfo *newStruct = malloc(sizeof(structInfo));

  if (newStruct == NULL) {
    printf("Couldn't allocate space for new struct\n");
    exit(1);
  }

  strcpy(newStruct->structName, structName);

  newStruct->varList = NULL;
  newStruct->funList = NULL;
  newStruct->next = NULL;

  return newStruct;
}

void destroyVarList(localVar *theList) {

  while (1) {

    if (theList == NULL) break;
    else {

      localVar * temp = theList->next;

      free(theList);

      theList = temp;
    }
  }
}

void destroyFunList(localFun *theList) {

  while (1) {

    if (theList == NULL) break;
    else {
      
      if (theList->code != NULL) free(theList->code);
      destroyVarList(theList->parameterList);
      destroyVarList(theList->localVariables);

      localFun * temp = theList->next;

      free(theList);

      theList = temp;
    }
  }
}

void destroyStructList(structInfo *theList) {

  while (1) {

    if (theList == NULL) break;
    else {

      structInfo * temp = theList->next;

      destroyVarList(theList->varList);
      destroyFunList(theList->funList);
      free(theList);

      theList = temp;
    }
  }
}

localVar * addToVarList(localVar * theList, localVar * toBeAdded) {

  if (toBeAdded == NULL) {

    printf("Node to be added is NULL!");
    exit (1);
  }

  else if (theList == NULL) {

      toBeAdded->next = NULL;
      return toBeAdded;
  }

  else {

    /* Stores theList (which is the head of the list) before it is modified
    by the while loop */
    localVar * head = theList;

    /* Sets theList to be the last node in the list */
    while (1) {

      if (theList->next == NULL) break;
      else theList = theList->next;
    }

    theList->next = toBeAdded;
    toBeAdded->next = NULL;

    return head;
  }
}

localFun * addToFunList(localFun * theList, localFun * toBeAdded) {

  if (toBeAdded == NULL) {

    printf("Node to be added is NULL!");
    exit (1);
  }

  else if (theList == NULL) {

      toBeAdded->next = NULL;
      return toBeAdded;
  }

  else {

    /* Stores theList (which is the head of the list) before it is modified
    by the while loop */
    localFun * head = theList;

    /* Sets theList to be the last node in the list */
    while (1) {

      if (theList->next == NULL) break;
      else theList = theList->next;
    }

    theList->next = toBeAdded;
    toBeAdded->next = NULL;

    return head;
  }
}

structInfo * addToStructList(structInfo * theList, structInfo * toBeAdded) {

  if (toBeAdded == NULL) {

    printf("Node to be added is NULL!");
    exit (1);
  }

  else if (theList == NULL) {

      toBeAdded->next = NULL;
      return toBeAdded;
  }

  else {

    /* Stores theList (which is the head of the list) before it is modified
    by the while loop */
    structInfo * head = theList;

    /* Sets theList to be the last node in the list */
    while (1) {

      if (theList->next == NULL) break;
      else theList = theList->next;
    }

    theList->next = toBeAdded;
    toBeAdded->next = NULL;

    return head;
  }
}
