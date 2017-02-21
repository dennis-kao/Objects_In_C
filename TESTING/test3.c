#include<stdio.h>
#include<stdlib.h>


struct A {
int a;
   int (*Afn) (struct A *);
};


/* set the value of a class variable from a method within the class */


int Afn (struct A * object) {
      object->a = 3;
   } 

void ConstructorA (struct A* newStruct) {
	newStruct->Afn = &Afn;
}
int main(int argc, char *argv[]) {
struct A myA;

   ConstructorA (&myA);
myA.Afn(&myA);
   if (myA.a == 3)
      return(0);
   else
      return(1);
}

