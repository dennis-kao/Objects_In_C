#include<stdio.h>
#include<stdlib.h>


struct A {
int a;
   int (*Afnc) (struct A *, char*);
};


/* set the value of a class variable using a method pointer parameter */
/* using a method in an expression */


int Afnc (struct A * object, char* str) {
      if (strcmp(str, "abc") == 0)
         return(0);
      else
         return(1);
   } 

void ConstructorA (struct A* newStruct) {
	newStruct->Afnc = &Afnc;
}
int main(int argc, char *argv[]) {
struct A myA;
ConstructorA (&myA);
char *str = "abc";

   if ( myA.Afnc(&myA, str)==0)
      return(0);
   else
      return(1);
}

