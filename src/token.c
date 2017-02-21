#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void restoreFormatting(FILE *input, char *fileName) {

  char presentChar;
  char pastChar;
  char line[510];
  
  char name[510];
  
  strcpy(name, fileName);
  name[strlen(name)-1] = '\0';
    
  FILE *output = fopen(name, "w");

  if (output == NULL) {
    printf("Could not create output file\n");
    exit(1);
  }

  presentChar = fgetc(input);

  /*rest of the file*/
  while (!feof(input)) {

    /*handles #include<>*/
    if (presentChar == '#') {

      fputc('#', output); /*place the #*/
      fgets(line, 509, input); /*get the remainder of the include line*/
      fputs(line, output); /*place the remainder of the include line*/

      pastChar = presentChar;
      presentChar = fgetc(input);
    }

    /*whole lines of comments are preserved*/
    else if (presentChar == '/') {

      fputc('/', output); /*place the forward slash*/
      fgets(line, 509, input); /*get the remainder of comment*/
      fputs(line, output); /*place the remainder of comment*/

      pastChar = presentChar;
      presentChar = fgetc(input);
    }

    /*retains whole lines of quotations*/
    else if (presentChar == '"') {

      fputc('"', output); /*place the beginning quotation*/

      pastChar = presentChar;
      presentChar = fgetc(input);

      while (presentChar != '"' || (pastChar == '\\' && presentChar == '"')) { /*loop only terminates when a lone closing bracket is detected*/

        fputc(presentChar, output);

        pastChar = presentChar;
        presentChar = fgetc(input);
      }

      fputc(presentChar, output); /*place closing bracket*/

      pastChar = presentChar;
      presentChar = fgetc(input);
    }

    /*places the whitespace char AND a newline*/
    else if (presentChar == '\n') {

      pastChar = presentChar;
      presentChar = fgetc(input);

      if (presentChar == ',' || presentChar == ';' || presentChar == '(' || presentChar == ')' || presentChar == '{' || presentChar == '}' || presentChar == '\n' || presentChar == '\t' || presentChar == '\r' || presentChar == ' ' || presentChar == '*' || presentChar == '+' || presentChar == '-' || presentChar == '.' || presentChar == '*') {
        fputc(presentChar, output);
        fgetc(input); /*skips the newline*/

        pastChar = presentChar;
        presentChar = fgetc(input);
      }

      else {

        fputc(presentChar, output); /*put the character*/

        pastChar = presentChar;
        presentChar = fgetc(input);
      }
    }

    else if (presentChar == ',' || presentChar == ';' || presentChar == '(' || presentChar == ')' || presentChar == '{' || presentChar == '}') {

      fputc(presentChar, output); /*put the punctuation*/
      fgetc(input); /*skip newline char*/

      pastChar = presentChar;
      presentChar = fgetc(input);
    }

    else {
      fputc(presentChar, output);

      pastChar = presentChar;
      presentChar = fgetc(input);
    }
  }

  fclose(output);
}

void tokenizeFile(FILE *input, FILE *output) {

  char line[510];
  char presentChar;
  char pastChar;

  if (input == NULL) {
    printf("Could not open input file\n");
    exit(1);
  }

  if (output == NULL) {
    printf("Could not create output file\n");
    exit(1);
  }

  presentChar = fgetc(input);

  /*rest of the file*/
  while (!feof(input)) {

    /*handles #include<>*/
    if (presentChar == '#') {

      fputc('#', output); /*place the #*/
      fgets(line, 509, input); /*get the remainder of the include line*/
      fputs(line, output); /*place the remainder of the include line*/
    }

    /*whole lines of comments are preserved*/
    /*accounts for star comments */
    else if (presentChar == '/') {
      
      pastChar = presentChar;
      presentChar = fgetc(input);
      
      if (presentChar == '/') { /*this is for //comments */
				
				int nullTermPos;
				
				fputc('/', output);
				fputc('*', output);
				
				fgets(line, 509, input);
				
				nullTermPos = strlen(line);
				
				line[nullTermPos-1] = '*';
				line[nullTermPos] = '/';
				line[nullTermPos+1] = '\n';
				line[nullTermPos+2] = '\0';
				
				fputs(line, output);
			}
      else if (presentChar == '*') { /*for star comments */
				fputc('/', output);
				fputc('*', output);
				fgets(line, 509, input);
				fputs(line, output);
			}
      else { /*the slash is a divisor */
				fputc('\n', output);
				fputc('/', output);
				fputc('\n', output);
				ungetc(presentChar, input);
			}
    }

    /*retains whole lines of quotations*/
    else if (presentChar == '"') {

      fputc('"', output); /*place the beginning quotation*/

      pastChar = presentChar;
      presentChar = fgetc(input);

      while (presentChar != '"' || (pastChar == '\\' && presentChar == '"')) { /*loop only terminates when a lone closing bracket is detected*/

        fputc(presentChar, output);

        pastChar = presentChar;
        presentChar = fgetc(input);
      }

      fputc(presentChar, output); /*place closing bracket*/
    }

    else if (presentChar == '*' || presentChar == '+' || presentChar == '-' || presentChar == '.') {
      fputc('\n', output);
      fputc(presentChar, output);
      fputc('\n', output);
    }

    /*places the whitespace char between 2 newlines*/
    else if (presentChar == '\n' || presentChar == '\t' || presentChar == '\r' || presentChar == ' ') {
      fputc('\n', output);
      fputc(presentChar, output);
      fputc('\n', output);
    }

    else if (presentChar == ',' || presentChar == ';' || presentChar == '(' || presentChar == ')' || presentChar == '{' || presentChar == '}') {
      if (pastChar != ' ' && pastChar != '\\') fputc('\n', output);
      fputc(presentChar, output);
      fputc('\n', output);
    }

    else if (presentChar == '\\') {
      if (pastChar != ' ') fputc('\n', output);
      fputc(presentChar, output);
    }

    else fputc(presentChar, output);

    pastChar = presentChar;
    presentChar = fgetc(input);
  }
}
