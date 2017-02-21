#include<stdio.h>
#include<stdlib.h>


struct A {
int a;
   int (*Afn) (struct A *);
};


int Afn (struct A * object) {
      object->a = 3;
   } 

void ConstructorA (struct A* newStruct) {
	newStruct->Afn = &Afn;
}
struct B {
int b;
   int (*Bfn) (struct B *);
};


/* two classes which contain the same method name */


int Bfn (struct B * object) {
      object->b = 4;
   } 

void ConstructorB (struct B* newStruct) {
	newStruct->Bfn = &Bfn;
}
int main(int argc, char *argv[]) {
struct A myA;
ConstructorA (&myA);
struct B myB;

   ConstructorB (&myB);
myA.Afn(&myA);
   myB.Bfn(&myB);
   if ((myA.a == 3) && (myB.b == 4))
      return(0);
   else
      return(1);
}

