#include<stdio.h>
#include<stdlib.h>


struct A {
int a;
   void (*Afni) (struct A *, int);
};


/* set the value of a class variable using a method parameter */


void Afni (struct A * object, int value) {
      object->a = value;
   } 

void ConstructorA (struct A* newStruct) {
	newStruct->Afni = &Afni;
}
int main(int argc, char *argv[]) {
struct A myA;
ConstructorA (&myA);
int i;

   i = 3;
   myA.Afni(&myA, i);
   if (myA.a == 3)
      return(0);
   else
      return(1);
}

