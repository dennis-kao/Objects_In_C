#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "token.h"
#include "storedList.h"
#include "dynamicStringLib.h"

int main (int argc, char *argv[]) {
  
  FILE *input = fopen(argv[1], "r");
  
  if ((input) == NULL) {
		printf("Failed to open input code!\n");
		exit(1);
	}
  
  FILE *tokenizedCode = fopen("intermediateFiles/tokenizedCode.c", "w");
  FILE *tokenOutput = fopen("intermediateFiles/tokenizedCode.c", "w");
  textInfo *code = calloc(1, sizeof(textInfo));
  structInfo *structList = NULL;
  
  tokenizeFile(input, tokenizedCode);
  tokenizedCode = freopen("intermediateFiles/tokenizedCode.c", "r", tokenizedCode);
  
  if (input == NULL) {
    printf("Could not open input file\n");
    exit(1);
  }
  
  storeText(tokenizedCode, code);
  
  structList = classToStruct(code, structList);
  
  mainParser(code, structList);
  
  printToFile(code, tokenOutput);
  tokenOutput = freopen("intermediateFiles/tokenizedCode.c", "r", tokenOutput); 
  
  restoreFormatting(tokenOutput, argv[1]);
  
  freeStoredText(code);
  
  destroyStructList(structList);
  
  fclose(tokenizedCode);
  fclose(input);
  fclose(tokenOutput);
    
  return 0;
}
