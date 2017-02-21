#include<stdio.h>
#include<stdlib.h>


struct A {
   int (*Afn) (struct A *);
};


/* use the return value of method in a class */


int Afn (struct A * object) {
      return(3);
   } 

void ConstructorA (struct A* newStruct) {
	newStruct->Afn = &Afn;
}
int main(int argc, char *argv[]) {
struct A myA;
ConstructorA (&myA);
int retValue;

   retValue = myA.Afn(&myA);
   if (retValue == 3)
      return(0);
   else
      return(1);
}

