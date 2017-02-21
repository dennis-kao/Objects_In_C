/*dynamic string library*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "token.h"
#include "storedList.h"
#include "dynamicStringLib.h"

char *smartAppend(char *appendToThis, char *addThis) {
  
  int a;
  int b;
  
  if (appendToThis == NULL) b = 0;
  else b = strlen(appendToThis);
  
  if (addThis == NULL) a = 0;
  else a = strlen(addThis);
  
  if (addThis == NULL && appendToThis == NULL) return NULL;
  
  if (appendToThis == NULL) {
	  appendToThis = calloc(a+b+1, sizeof(char));
  }

  else appendToThis = realloc(appendToThis, sizeof(char) * (a+b+1) );
  
  if (appendToThis == NULL) {
    printf("Error: Could not append strings\n");
    exit(1);
  }

  strcat(appendToThis, addThis);

  return appendToThis;
}

void storeText(FILE *input, textInfo *code) {

  char line[510];
  char **theText;
  theText = NULL;
  int i;

  if (fgets(line, 509, input) == NULL) return;
  
  /* If there was any previous code, free it */
  if (code->theText != NULL) {
	for (i = 0; i < code->numLines; i++) {
	  if (code->theText[i] != NULL) free(code->theText[i]);
	}
	free(code->theText);
  }
  
  code->numLines = 0;

  for (i= 0; !feof(input); i++) {

	/*we good*/
    theText = realloc(theText, sizeof(char *) * (i+2));

    if (theText == NULL) {
      printf("Could not allocate memory to store text info\n");
      exit(1);
    }
    
    theText[i] = calloc(strlen(line)+1, sizeof(char));

    strcpy(theText[i], line);
    
    code->numLines++;

    fgets(line, 509, input);
  }

  code->theText = theText;
}

void freeStoredText(textInfo *code) {
  
  int i;

  for (i= 0; i < code->numLines; i++) {
    free(code->theText[i]);
  }
    
  free(code->theText);
  
  free(code);
}

char *changeToTokenizedFormat(char *formatMe) {
  
  char line[510];
  char *formatted;
  formatted = NULL;
  FILE *output;
  output = fopen("intermediateFiles/formattedTokenHolder.txt", "w"); /*wipe em clean boys*/
  FILE *input;
  input = fopen("intermediateFiles/tokenHolder.txt", "w");           /*this one too*/
  int i;
  
  if (output == NULL) {
    printf("Could not create formattedTokenHolder file\n");
    exit(1);
  }
  
  if (input == NULL) {
    printf("Could not tokenHolder file\n");
    exit(1);
  }
  
  fputs(formatMe, input); /*populate file with code*/
  
  input = freopen("intermediateFiles/tokenHolder.txt", "r", input); /*read the code*/
  
  if (input == NULL) {
    printf("Could not read tokenHolder file\n");
    exit(1);
  }
  
  tokenizeFile(input, output); /*do the token, do the token dance*/
  
  fclose(input);
  
  output = freopen("intermediateFiles/formattedTokenHolder.txt", "r", output);
  
  if (output == NULL) {
    printf("Could not read formattedTokenHolder file\n");
    exit(1);
  }
  
  fgets(line, 509, output);
  
  formatted = calloc(strlen(line)+1, sizeof(char));
  
  strcpy(formatted, line);
  
  if (fgets(line, 509, output) != NULL) {
	for (i= 0; !feof(output); i++) { /*append all text to formatMe*/
		formatted = smartAppend(formatted, line);
		fgets(line, 509, output);
	}
  }
  
  fclose(output);
  
  return formatted;
}

void insertText(char *insertMe, textInfo *code, int insertHereIndex) {
  
  int i;
  
  code->theText = realloc(code->theText, sizeof(char*) * (code->numLines+1)); /*add one more line*/
  
  if (code->theText == NULL) {
    printf("Error for adding 1 more line for code\n");
    exit(1);
  }
  
  code->theText[code->numLines] = NULL; /*set the newly created pointer to null*/
  code->numLines++;
  
  /* moves text from specified index 1 line down*/
  for (i= code->numLines - 1; i > insertHereIndex; i--) {
	  
	if (code->theText[i] != NULL) free(code->theText[i]);
    
    code->theText[i] = calloc((strlen(code->theText[i-1])+1), sizeof(char));
    
    if (code->theText[i] == NULL) {
      printf("Could not resize chars in string\n");
      exit(1);
    }
    
    strcpy(code->theText[i], code->theText[i-1]);
  }
  
  free(code->theText[insertHereIndex]);
  code->theText[insertHereIndex] = malloc(sizeof(char) * (strlen(insertMe)+1));
  
  if (code->theText[insertHereIndex] == NULL) {
    printf("Could not resize chars in string\n");
    exit(1);
  }
  
  strcpy(code->theText[insertHereIndex], insertMe);
}

void deleteText(textInfo *code, int deleteHereIndex) {
  
  int i;
  
  for (i= deleteHereIndex; i < code->numLines - 1; i++) {
	  
	free(code->theText[i]);
    
    code->theText[i] = malloc(sizeof(char) * (strlen(code->theText[i+1])+1));
    
    if (code->theText[i] == NULL) {
      printf("Could not resize chars in string\n");
      exit(1);
    }
    
    strcpy(code->theText[i], code->theText[i+1]);
  }
  
  free(code->theText[code->numLines-1]);
  
  code->theText = realloc(code->theText, sizeof(char*) * (code->numLines-1));
  
  if (code->theText == NULL) {
    printf("Error removing 1 line of code\n");
    exit(1);
  }
  
  code->numLines--;
}

char *saveCode(textInfo *code, int start, int end) {
  
  char *savedText;
  savedText = NULL;
  int i;
  
  if (start > (code->numLines-1) || end > (code->numLines-1)) {
    printf("Error: Attempting to save code with indexes greater than the number of lines in the text\n");
    exit(1);
  }
  
  for (i= start; i <= end; i++) {
    
    savedText = smartAppend(savedText, code->theText[i]);
  }
  
  return savedText;
}

int indexOfClosingBracket(textInfo *code, int openBracketIndex) {
  
  int bracketCounter;
  bracketCounter = 1;
  int i;
  
  for (i= openBracketIndex+1; i < code->numLines; i++) {
    
    if (code->theText[i][0] == '{') bracketCounter++;
    else if (code->theText[i][0] == '}') bracketCounter--;
    
    if (bracketCounter == 0) return i;
  }
  
  /* return statement in loop did not execute*/
  printf("Could not determine the closing bracket index!\n");
  exit(1);
}

void printToFile(textInfo *code, FILE *output) {
  int i;
  
  for (i= 0; i < code->numLines; i++) {
    
    fputs(code->theText[i], output);
  }
}

void insertFormatted (char *insertMe, textInfo *code, int insertHereIndex) {
  
  FILE *temp;
  temp = fopen("intermediateFiles/insertFormatted.txt", "w");
  char *tokenized;
  tokenized = changeToTokenizedFormat(insertMe);
  
  insertText(tokenized, code, insertHereIndex);
  
  free(tokenized);
  
  printToFile(code, temp);
  
  fclose(temp);
  
  temp = fopen("intermediateFiles/insertFormatted.txt", "r");
  
  storeText(temp, code);
  
  fclose(temp);
}

void insert (char *insertMe, textInfo *code, int insertHereIndex) {
  
  FILE *temp;
  temp = fopen("intermediateFiles/insertFormatted.txt", "w");
  char *tokenized;
  tokenized = insertMe;
  
  insertText(tokenized, code, insertHereIndex);
  
  printToFile(code, temp);
  
  fclose(temp);
  
  temp = fopen("intermediateFiles/insertFormatted.txt", "r");
  
  storeText(temp, code);
  
  fclose(temp);
}

int nextKeyword(int i, textInfo *code) {
  
  do {
    i++;
    if (i >= code->numLines) return code->numLines;
  }while (isspace(code->theText[i][0]) || code->theText[i][0] == '/');
  
  return i;
}

int openBracketIndex (int i, textInfo *code) {
  
  do {
    i++;
    if (i > code->numLines) return code->numLines;
  }while (code->theText[i][0] != '{');
  
  return i;
}

int parseDataType(int i, char type[510], textInfo *code) {
  
  int j;
  
  /*  parses data type*/
  if ( ((strcmp(code->theText[i], "long\n") == 0) && (strcmp(code->theText[nextKeyword(i, code)], "double\n") == 0))
  || ((strcmp(code->theText[i], "long\n") == 0) && (strcmp(code->theText[nextKeyword(i, code)], "long\n") == 0))
  || strcmp(code->theText[i], "struct\n") == 0 
  || strcmp(code->theText[i], "signed\n") == 0 
  || strcmp(code->theText[i], "unsigned\n") == 0) {
    
    strcpy(type, code->theText[i]);
    
    /*  grab the second word for the type*/
    i = nextKeyword(i, code);
    
    strcat(type, code->theText[i]);
    
    i = nextKeyword(i, code);    
  }
  
  else {
    
    strcpy(type, code->theText[i]);
    
    i = nextKeyword(i, code);
  }
  
  type[strlen(type)-1] = '\0'; /*get rid of newline at the end of the string from parsing*/
  
  /* replaces newlines with spaces*/
  for (j = 0; j < strlen(type); j++) {
    if (type[j] == '\0') break;
    if (type[j] == '\n') type[j] = ' ';
  }
  
  return i;
}

int starCounter(int *i, textInfo *code) {
  
  int starCounter;
  starCounter = 0;
  
  while (code->theText[*i][0] == '*') {
    starCounter++;
    *i = nextKeyword(*i, code);
  }
  
  return starCounter;
}

void deleteLines(textInfo *code, int start, int end) {
  
  if (end < start) {
    printf("End is less than start\n");
    exit(1);
  }
  else if (start == end) {
    deleteText(code, start);
  }
  else {
    int i;
    for (i= end; i >= start; i--) {
      
      deleteText(code, i);
    }
  }
}

void appendParameters(localFun *newFun, char *functionPointer) {
  
  localVar *temp;
  temp = newFun->parameterList;
  
  while (temp != NULL) {
    
    char parameterChar[2];
    int i = 0;
    
    parameterChar[0] = temp->varType[0];
    parameterChar[1] = '\0';
    
    strcat(functionPointer, parameterChar);
    
    while (temp->varType[i] != ' ') {
      if (temp->varType[i] == '\0') break;
      i++;
    }
    
    if (temp->varType[i] == ' ') {
      parameterChar[0] = temp->varType[i+1];
      parameterChar[1] = '\0';
      strcat(functionPointer, parameterChar);
    }
    
    temp = temp->next;
  }
}

void functionName(localFun *newFun, char *funName, structInfo *newStruct) {
  
  strcpy(funName, newStruct->structName);
  strcat(funName, newFun->funName);
  appendParameters(newFun, funName);
}

void createFunctionPointer(localFun *newFun, char functionPointer[510], structInfo *newStruct) {
  
  int j;
  
  localVar *tempParam;
  tempParam = newFun->parameterList;
  
  strcpy(functionPointer, newFun->returnType);
  
  for (j = 0; j < newFun->star; j++) {
    strcat(functionPointer, "*");
  }
  
  strcat(functionPointer, " (*");
  
  strcat(functionPointer, newStruct->structName);
  strcat(functionPointer, newFun->funName);
  
  appendParameters(newFun, functionPointer);
  
  strcat(functionPointer, ") (struct ");
  strcat(functionPointer, newStruct->structName);
  strcat(functionPointer, " *");
  
  /*  append data types*/
  while (tempParam != NULL) {
    strcat(functionPointer, ", ");
    strcat(functionPointer, tempParam->varType);
    
    for (j = 0; j < tempParam->stars; j++) {
      strcat(functionPointer, "*");
    }
    
    tempParam = tempParam->next;
  }
  
  strcat(functionPointer, ");");
}

char *constructor (structInfo *newstruct) {
  
  char *newConstruct;
  newConstruct = NULL;
  localFun *tempFun = newstruct->funList;
  
  newConstruct = smartAppend(newConstruct, "void Constructor");
  newConstruct = smartAppend(newConstruct, newstruct->structName);
  newConstruct = smartAppend(newConstruct, " (struct ");
  newConstruct = smartAppend(newConstruct, newstruct->structName);
  newConstruct = smartAppend(newConstruct, "* newStruct) {");
  
  for (; tempFun != NULL; tempFun = tempFun->next) {
    char name[200];
    
    newConstruct = smartAppend(newConstruct, "\n\tnewStruct->");
    
    strcpy(name, newstruct->structName);
    strcat(name, tempFun->funName);
    appendParameters(tempFun, name);
    
    newConstruct = smartAppend(newConstruct, name);
    
    newConstruct = smartAppend(newConstruct, " = &");
    
    newConstruct = smartAppend(newConstruct, name);
    
    newConstruct = smartAppend(newConstruct, ";");
  }
  
  newConstruct = smartAppend(newConstruct, "\n}\n");
    
  return newConstruct;
}

/*  adds information to the appropriate data structures*/
/*  replaces functions with function pointers*/
/*  renames functions*/
void parseStruct(textInfo *code, int openBracket, int closingBracket, structInfo *newStruct) {
  
  char name[510];
  char type[510];
  int i;
  i = openBracket;
  int startOfFunction;
  int endOfFunction;
  
  i = nextKeyword(i, code);
  
  while (code->theText[i][0] != '}') {
    
    int star;
    
    startOfFunction = i;
    
    i = parseDataType(i, type, code);
    
    star = starCounter(&i, code);
    
    /*  i now points to the name*/
    strcpy(name, code->theText[i]);
    name[strlen(name)-1] = '\0';
    
    i = nextKeyword(i, code);
    
    if (code->theText[i][0] == ';') newStruct->varList = addToVarList(newStruct->varList, createVariable(name, type, star));
    
    else if (code->theText[i][0] == ',') {
      
      newStruct->varList = addToVarList(newStruct->varList, createVariable(name, type, star));
      
      i = nextKeyword(i, code);
      
      /*  multiple variable line delcaration*/
      while(code->theText[i][0] != ';') {
        
        star = starCounter(&i, code);
        
        strcpy(name, code->theText[i]);
        name[strlen(name)-1] = '\0';
        
        newStruct->varList = addToVarList(newStruct->varList, createVariable(name, type, star));
        
        i = nextKeyword(i, code);
        if (code->theText[i][0] == ',') i = nextKeyword(i, code);
      }
    }
    
    else if (code->theText[i][0] == '(') {
      
      localFun *newFun = createFunction(name, type, star);
      char functionPointer[510];
      int displacement;
      
      i = nextKeyword(i, code);
      
      while (code->theText[i][0] != ')') {
        
        /*  block below handles all the logic of parsing */
        i = parseDataType(i, type, code);
        
        star = starCounter(&i, code);
        
        strcpy(name, code->theText[i]);
        name[strlen(name)-1] = '\0';
        
        /*  iterator */
        i = nextKeyword(i, code);
        if (code->theText[i][0] == ',') i = nextKeyword(i, code); /*  get next significant keyword */
        
        /*  add to list */
        newFun->parameterList = addToVarList(newFun->parameterList, createVariable(name, type, star));
      }
      
      /*  save the function code */
      i = openBracketIndex(i, code);
      openBracket = i;
      int closingBracketIndex;
      closingBracketIndex = indexOfClosingBracket(code, openBracket);
      endOfFunction = closingBracketIndex;
      
      //~ if (code->theText[nextKeyword(closingBracketIndex, code)][0] == ';') {
        //~ endOfFunction = nextKeyword(closingBracketIndex, code);
      //~ }
            
      newFun->code = saveCode(code, openBracket, closingBracketIndex);
      /* Determines the local variables for scope functions later */
      storeLocalVariablesInFun(newFun);      
      
      newStruct->funList = addToFunList(newStruct->funList, newFun);
      
      deleteLines(code, startOfFunction, endOfFunction);
      
      i = startOfFunction;
      /*  after deleting the lines of code, the index is shifted and startOfFunction now points to the shifted endOfFunction */
      
      /*  write code to insert function pointer here */
      createFunctionPointer(newFun, functionPointer, newStruct);
      
      displacement = code->numLines;
      
      insertFormatted (functionPointer, code, i);
      
      displacement = code->numLines - displacement;
            
      i = startOfFunction + displacement;      
    }
    
    else if (code->theText[i][0] == '=') {

      char value[500];     
      value[0] = '\0'; 
      localVar *tempVariable;
      int semicolon;
      
      code->theText[i][0] = ';';
      
      i = nextKeyword(i, code);
      semicolon = i;
      
      while (code->theText[semicolon][0] != ';') {
        strcat(value, code->theText[semicolon]);
        semicolon = nextKeyword(semicolon, code);
      }
            
      /* copy over the value */
      tempVariable = createVariable(name, type, star);
      strcpy(tempVariable->value, value);
      newStruct->varList = addToVarList(newStruct->varList, tempVariable);
      
      /* delete the required lines */
      deleteLines(code, i, semicolon);
    }
    
    i = nextKeyword(i, code);    
  }
}

void addClassScopeToFun(structInfo *parentStruct) {
	
	int i;
	i = 0;
	
	localFun *fun;
	fun = parentStruct->funList;

	while (fun != NULL) {
		
		FILE *functionCode = fopen("intermediateFiles/functionCode", "w");
		
		textInfo *code;
		code = malloc(sizeof(textInfo));
		code->numLines = 0;
		code->theText = NULL;
	
		fputs(fun->code, functionCode);
		
		functionCode = freopen("intermediateFiles/functionCode", "r", functionCode);
		
		storeText(functionCode, code);
		
		i = nextKeyword(i, code);
		
		while(i < code->numLines) {
			
			char line[510];
			strcpy(line, code->theText[i]);
			if (line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0';
						
			if (strcmp(line, "int") == 0 ||
				strcmp(line, "char") == 0 ||
				strcmp(line, "short") == 0 ||
				strcmp(line, "float") == 0 ||
				strcmp(line, "double") == 0 ||
				strcmp(line, "long") == 0 ||
				strcmp(line, "signed") == 0 ||
				strcmp(line, "unsigned") == 0) {
					
					while(line[0] != ';') {
						i = nextKeyword(i, code);
						strcpy(line, code->theText[i]);
					}
			}
			
			else if (isClassVariable(parentStruct, line)) {
				
									
				if (isInParamList(fun, line) == 1) {
				}
					
				else if (isLocalToFun(fun, line) == 1) {
				}
																
				/*variable name only exists in class */
				else {
										
					char internalReference[510];
					sprintf(internalReference, "object->%s\n", line);
					
					free(code->theText[i]);
					code->theText[i] = malloc(sizeof(char) * (strlen(internalReference) + 1));
					strcpy(code->theText[i], internalReference);
				}
			}
				
			i = nextKeyword(i, code);
		}
		
		
		free(fun->code);
		fun->code = saveCode(code, 0, code->numLines-1);
		
		freeStoredText(code);
				
		fclose(functionCode);
		
		i = 0;
		
		fun = fun->next;
	}
}

int insertCon(textInfo *code, structInfo *newStruct, int insertHere, structInfo *structList) {
  
  int startofconstruct;
  int oldNumLines;
  localFun *temp;
  localVar *tempVar;
  char *constructFun;
  char star[20];
  char functionDec[200];
  char name[50];
  int i;
  
  temp = newStruct->funList;
  startofconstruct = insertHere;
  
  while (temp != NULL) {
	  
	FILE *funCodeInFile = fopen("intermediateFiles/modFunctionCode", "w");
	
	textInfo *funCode;
	funCode = malloc(sizeof(textInfo));
	funCode->numLines = 0;
	funCode->theText = NULL;
	  
	fputs(temp->code, funCodeInFile);
	funCodeInFile = freopen("intermediateFiles/modFunctionCode", "r", funCodeInFile);
	storeText(funCodeInFile, funCode);
	fclose(funCodeInFile);
	
	modifyFunCodeForClasses(funCode, structList);
	free(temp->code);
	temp->code = saveCode(funCode, 0, funCode->numLines-1);
	
	star[0] = '\0';
  
	for (i = 0; i < temp->star; i++) strcat(star, "*");

	functionName(temp, name, newStruct);
	sprintf(functionDec, "\n%s%s %s (", temp->returnType, star, name);
  	
	strcat(functionDec, "struct ");
	strcat(functionDec, newStruct->structName);
	strcat(functionDec, " * object");
	
	tempVar = temp->parameterList;
	while (tempVar != NULL) {
		strcat(functionDec, ", ");
		strcat(functionDec, tempVar->varType);
    
    for (i = 0; i < tempVar->stars; i++) {
      strcat(functionDec, "*");
    }
    
		strcat(functionDec, " ");
		strcat(functionDec, tempVar->varName);
		
		tempVar = tempVar->next;
	}
	
	strcat(functionDec, ") ");
		
	oldNumLines = code->numLines;
	insertFormatted (functionDec, code, startofconstruct);
	startofconstruct = startofconstruct + (code->numLines - oldNumLines);
	
	oldNumLines = code->numLines;
	insert(temp->code, code, startofconstruct);
	startofconstruct = startofconstruct + (code->numLines - oldNumLines);
	
	oldNumLines = code->numLines;
	insertFormatted (" \n", code, startofconstruct);
	startofconstruct = startofconstruct + (code->numLines - oldNumLines);
	
	freeStoredText(funCode);
	temp = temp->next;
  }
  
  oldNumLines = code->numLines;
  insertFormatted ("\n", code, startofconstruct);
  startofconstruct = startofconstruct + (code->numLines - oldNumLines);
  
  constructFun = constructor(newStruct);
  insertFormatted (constructFun, code, startofconstruct);
  free(constructFun);
  
  /* Inserting lines of code will always increase numLines */
  startofconstruct = startofconstruct + (code->numLines - oldNumLines);
  
  return startofconstruct;
}

void storeLocalVariablesInFun(localFun *fun) {
		
	textInfo *code;
	code = calloc(1, sizeof(textInfo));
	code->numLines = 0;
	code->theText = NULL;
	
	int i;
	i = 0;
	
	FILE *functionCode = fopen("intermediateFiles/functionCode", "w");
	
	fputs(fun->code, functionCode);
	
	functionCode = freopen("intermediateFiles/functionCode", "r", functionCode);
	
	storeText(functionCode, code);
	
	i = nextKeyword(i, code);
	
	while(i != code->numLines) {
		
		int star;
		star = 0;

		char type[510];
		char name[510];
		
		if (strcmp(code->theText[i], "int\n") == 0 ||
			strcmp(code->theText[i], "char\n") == 0 ||
			strcmp(code->theText[i], "short\n") == 0 ||
			strcmp(code->theText[i], "float\n") == 0 ||
			strcmp(code->theText[i], "double\n") == 0 ||
			strcmp(code->theText[i], "long\n") == 0 ||
			strcmp(code->theText[i], "signed\n") == 0 ||
			strcmp(code->theText[i], "unsigned\n") == 0) {
				
				i = parseDataType(i, type, code);
				star = starCounter(&i, code);				
				strcpy(name, code->theText[i]);
				
				if (name[strlen(name)-1] == '\n') name[strlen(name)-1] = '\0';
												
				fun->localVariables = addToVarList(fun->localVariables, createVariable(name, type, star));
			}
			
		i = nextKeyword(i, code);
	}
	
	freeStoredText(code);
	fclose(functionCode);
}

structInfo *classToStruct(textInfo *code, structInfo *structList) {
  
  char name[510];
  int closingBracketIndex;
  int i;
  i = 0;
  
  while(i < code->numLines) {
    
    if (strcmp("class\n", code->theText[i]) == 0) {
            
      structInfo *newStruct;
      int openBracket;
      int displacement;
      int pastPosition;
            
      code->theText[i] = realloc(code->theText[i], sizeof(char) * (strlen("struct\n")+1));
      strcpy(code->theText[i], "struct\n");
      
      i = nextKeyword(i, code);
      
      strcpy(name, code->theText[i]);
      name[strlen(name)-1] = '\0';
      
      newStruct = createStruct(name);
      
      pastPosition = i;
      i = nextKeyword(i, code);
      
      if (code->theText[i][0] != '{') {
        while (code->theText[i][0] != ';') i = nextKeyword(i, code);
      }
      
      else {
		  i = pastPosition;
		  
		  /* get the index of the opening bracket and corresponding closing bracket */
		  i = openBracketIndex(i, code);
      openBracket = i;
		  closingBracketIndex = indexOfClosingBracket(code, i);
      
		  parseStruct(code, i, closingBracketIndex, newStruct);
		  addClassScopeToFun(newStruct);
		  
		  structList = addToStructList(structList, newStruct);
		  
		  /*  inserts functions and constructors and updates index i */
		  i = indexOfClosingBracket(code, openBracket);
		  
		  /* now point to keyword after semi colon */
		  i = nextKeyword(i, code); /* semi colon */
      i = nextKeyword(i, code); /* i points to the next keyword */
				
		  displacement = code->numLines;

		  insertCon(code, newStruct, i, structList);
		  		  
		  displacement = code->numLines - displacement;
		  
		  i = i + displacement;
      }
    }
    
    else if (strcmp("main\n", code->theText[i]) == 0) {
		
      return structList;
    }
    
    else i = nextKeyword(i, code);
  }
  
  return structList;
}

int isInParamList(localFun *fun, char *potentialIdentifier) {
	
	if(fun != NULL) {
		
		localVar *tempParam;
		tempParam = fun->parameterList;
		
		while(tempParam != NULL) {
			
			if (strcmp(tempParam->varName, potentialIdentifier) == 0) return 1;
			
			tempParam = tempParam->next;
		}		
	}
	
	return 0;
}

int isLocalToFun(localFun *fun, char *potentialIdentifier) {
		
	if(fun != NULL) {
		
		localVar *tempParam;
		tempParam = fun->localVariables;
		
		while(tempParam != NULL) {
						
			if (strcmp(tempParam->varName, potentialIdentifier) == 0) {
				
				return 1;
			}
			
			tempParam = tempParam->next;
		}		
	}
	
	return 0;
}

int isClassVariable(structInfo *theStruct, char *potentialIdentifier) {
	
	if( potentialIdentifier[strlen(potentialIdentifier)-1] == '\n') potentialIdentifier[strlen(potentialIdentifier)-1] = '\0';
	
	if (theStruct != NULL) {
		
		localVar *tempParam;
		tempParam = theStruct->varList;
		
		while(tempParam != NULL) {
			if (strcmp(tempParam->varName, potentialIdentifier) == 0) return 1;
			
			tempParam = tempParam->next;
		}
	}
	
	return 0;
}

void generateConstructorCall(char *storage, char *classType, char *name, structInfo *structList) {
	
	sprintf(storage, "Constructor%s (&%s);\n", classType, name);
}

int isADeclaredClass(char *compareMe, localVar *list) {
	
	char line[510];
	strcpy(line, compareMe);
	
	if (line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0';
	
	while (list != NULL) {
		if (strcmp(line, list->varName) == 0) return 1;
		list = list->next;
	}
	
	return 0;
}

int isAMethod(char *methodName, char *objectName, structInfo *structList, localVar *classInMain) {
	
	while (classInMain != NULL) {
		
		if (strcmp(classInMain->varName, objectName) == 0) break;
		
		classInMain = classInMain->next;
	}
	
	/* Now classInMain will point to the object information */
	
	while (structList != NULL) {
		
		if (strcmp(classInMain->varType, structList->structName) == 0) {
			
			localFun *tempFun;
			tempFun = structList->funList;
			
			while (tempFun != NULL) {
				
				if (strcmp(tempFun->funName, methodName) == 0) {
				
					return 1;
				}
				
				tempFun = tempFun->next;
			}
		}
		
		structList = structList->next;
	}
	
	return 0;
}

void findAndCopyFunction(char *storage, char *methodName, char *objectName, structInfo *structList, localVar *classInMain) {
	
	while (classInMain != NULL) {
		
		if (strcmp(classInMain->varName, objectName) == 0) break;
		
		classInMain = classInMain->next;
	}
	
	/* Now classInMain will point to the object information */
	
	while (structList != NULL) {
		
		if (strcmp(classInMain->varType, structList->structName) == 0) {
			
			localFun *tempFun;
			tempFun = structList->funList;
			
			while (tempFun != NULL) {
				
				if (strcmp(tempFun->funName, methodName) == 0) {
				
					functionName(tempFun, storage, structList);
					strcat(storage, "\n");
					
					return;
				}
				
				tempFun = tempFun->next;
			}
		}
		
		structList = structList->next;
	}
}

void mainParser(textInfo *code, structInfo *structList) {
  
  int i;
  i = 0;
  
  localVar *classInMain;
  classInMain = NULL;
  
  /*find main in the laziest way possible */
  while ((strcmp("main\n", code->theText[i]) != 0)) {
    i = nextKeyword(i, code);
  }
  
  while (code->theText[i][0] != '{') {
    i = nextKeyword(i, code);
  }

  while (i < code->numLines) {
	  	  
	  char classType[510];
	  char name[510];
	  char constructorCall[500];
	  int oldLines;
	  
	  if (strcmp(code->theText[i], "class\n") == 0) {
		  
		  free(code->theText[i]);
		  code->theText[i] = malloc(sizeof(char)*(strlen("struct\n")+1));
		  strcpy(code->theText[i], "struct\n");
		  
		  i = nextKeyword(i, code);
		  strcpy(classType, code->theText[i]);
		  
		  i = nextKeyword(i, code);
		  strcpy(name, code->theText[i]);
		  
		  i = nextKeyword(i, code); /* now points to ';' character */
      
      if (code->theText[i][0] == ';') {
        i = nextKeyword(i, code);
		  
        name[strlen(name)-1] = '\0';
        classType[strlen(classType)-1] = '\0';
        
        classInMain = addToVarList(classInMain, createVariable(name, classType, 0)); /* 0 stars, we don't need em */
        generateConstructorCall(constructorCall, classType, name, structList);
        
        oldLines = code->numLines;
        insertFormatted(constructorCall, code, i);
        i = i + (code->numLines - oldLines);
        /* printf("next keyword: %s\n", code->theText[i]); */
        i--; /*dials back i so that the next call of nextKeyword will get the one its pointing at before i-- */
      }
      
      else if (code->theText[i][0] == ',') { /* the character is a comma */
        
        char multipleConstructor[500];
        multipleConstructor[0] = '\0';
        
        i = nextKeyword(i, code);
		  
        name[strlen(name)-1] = '\0';
        classType[strlen(classType)-1] = '\0';
        
        classInMain = addToVarList(classInMain, createVariable(name, classType, 0)); /* 0 stars, we don't need em */
        generateConstructorCall(constructorCall, classType, name, structList);
        strcat(multipleConstructor, constructorCall);
        
        while (code->theText[i][0] != ';') {
          strcpy(name, code->theText[i]);
          name[strlen(name)-1] = '\0';
          
          classInMain = addToVarList(classInMain, createVariable(name, classType, 0));
          generateConstructorCall(constructorCall, classType, name, structList);
          strcat(multipleConstructor, constructorCall);
          
          i = nextKeyword(i, code);
          if (code->theText[i][0] == ',') i = nextKeyword(i, code);
        }
        
        i = nextKeyword(i, code);
        
        oldLines = code->numLines;
        insertFormatted(multipleConstructor, code, i);
        i = i + (code->numLines - oldLines);
        /* printf("next keyword: %s\n", code->theText[i]); */
        i--; /*dials back i so that the next call of nextKeyword will get the one its pointing at before i-- */
      }
	  }
	  
	  else if (isADeclaredClass(code->theText[i], classInMain) == 1) {
		  		  
		  char methodName[510];
		  char objectName[510];
		  
		  strcpy(objectName, code->theText[i]);
		  objectName[strlen(objectName)-1] = '\0';
		  		  		  
		  i = nextKeyword(i, code);
		  
		  if (code->theText[i][0] == '.') {
			  
			  int oldNumLines;
			  
			  i = nextKeyword(i, code);
			  			  
			  strcpy(methodName, code->theText[i]);
			  methodName[strlen(methodName)-1] = '\0';
			  			  
			  if (isAMethod(methodName, objectName, structList, classInMain)){
          
          /*  code to determine which method it is based on parameters */
				  				  
				  char storage[510];
				  char objectReference[510];
				  
				  objectReference[0] = '&';
				  objectReference[1] = '\0';
				  strcat(objectReference, objectName);
				  
				  findAndCopyFunction(storage, methodName, objectName, structList, classInMain);
				  
				  free(code->theText[i]);
				  code->theText[i] = malloc(sizeof(char)* (strlen(storage)+1));
				  strcpy(code->theText[i], storage);
				  
				  /* now add a reference to the object in the method call */
				  
				  while (code->theText[i][0] != '(') i = nextKeyword(i, code);
				  
				  i = nextKeyword(i, code);
				  if (code->theText[i][0] != ')') strcat(objectReference, ", ");
				  
				  oldNumLines = code->numLines;
				  insertFormatted (objectReference, code, i);
				  i = i + (code->numLines - oldNumLines);
			  }
			  else; /* it must be a data member */
		  }
	  }
	  
	  i = nextKeyword(i, code);	  
  }
  
  destroyVarList(classInMain);
}

void modifyFunCodeForClasses(textInfo *code, structInfo *structList) {
  
  int i;
  i = 0;
  
  localVar *classInMain;
  classInMain = NULL;
  
  int end;
  end = code->numLines -1;

  i = nextKeyword(i, code);	  

  while (i < code->numLines) {
	  	  
	  char classType[510];
	  char name[510];
	  char constructorCall[510];
	  int oldLines;
	  
	  if (strcmp(code->theText[i], "class\n") == 0) {
      		  
		  free(code->theText[i]);
		  code->theText[i] = malloc(sizeof(char)*(strlen("struct\n")+1));
		  strcpy(code->theText[i], "struct\n");
		  
		  i = nextKeyword(i, code);
		  strcpy(classType, code->theText[i]);
		  
		  i = nextKeyword(i, code);
		  strcpy(name, code->theText[i]);
		  
		  i = nextKeyword(i, code); /* now points to ';' character */
		  
		  i = nextKeyword(i, code);
		  
		  name[strlen(name)-1] = '\0';
		  classType[strlen(classType)-1] = '\0';
		  
		  classInMain = addToVarList(classInMain, createVariable(name, classType, 0)); /* 0 stars, we don't need em */
		  generateConstructorCall(constructorCall, classType, name, structList);
		  
		  oldLines = code->numLines;
		  insertFormatted(constructorCall, code, i);
		  i = i + (code->numLines - oldLines);
		  end = end + (code->numLines - oldLines);
		  i--; /*dials back i so that the next call of nextKeyword will get the one its pointing at before i-- */
	  }
	  
	  else if (isADeclaredClass(code->theText[i], classInMain) == 1) {
		  		  
		  char methodName[510];
		  char objectName[510];
		  
		  strcpy(objectName, code->theText[i]);
		  objectName[strlen(objectName)-1] = '\0';
		  		  		  
		  i = nextKeyword(i, code);
		  
		  if (code->theText[i][0] == '.') {
			  
			  int oldNumLines;
			  
			  i = nextKeyword(i, code);
			  			  
			  strcpy(methodName, code->theText[i]);
			  methodName[strlen(methodName)-1] = '\0';
			  			  
			  if (isAMethod(methodName, objectName, structList, classInMain)){
				  				  
				  char storage[510];
				  char objectReference[510];
				  
				  objectReference[0] = '&';
				  objectReference[1] = '\0';
				  strcat(objectReference, objectName);
				  
				  findAndCopyFunction(storage, methodName, objectName, structList, classInMain);
				  
				  free(code->theText[i]);
				  code->theText[i] = malloc(sizeof(char)* (strlen(storage)+1));
				  strcpy(code->theText[i], storage);
				  
				  /* now add a reference to the object in the method call */
				  
				  while (code->theText[i][0] != '(') i = nextKeyword(i, code);
				  
				  i = nextKeyword(i, code);
				  if (code->theText[i][0] != ')') strcat(objectReference, ", ");
				  
				  oldNumLines = code->numLines;
				  insertFormatted (objectReference, code, i);
				  i = i + (code->numLines - oldNumLines);
				  end = end + (code->numLines - oldLines);
			  }
			  else; /* it must be a data member */
		  }
	  }
	  
	  i = nextKeyword(i, code);	  
  }
  
  destroyVarList(classInMain);
}

