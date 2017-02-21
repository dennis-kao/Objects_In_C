#include<stdio.h>
#include<stdlib.h>


struct A {
int a, b;
   int (*Afni) (struct A *, int);
   int (*Afnii) (struct A *, int, int);
};



/* overloaded methods, comment with the word class in it */


int Afni (struct A * object, int i) {
      object->a = i;
   } 

int Afnii (struct A * object, int i, int j) {
      object->b = i + j;
   } 

void ConstructorA (struct A* newStruct) {
	newStruct->Afni = &Afni;
	newStruct->Afnii = &Afnii;
}
int main(int argc, char *argv[]) {
struct A myA, myB;
ConstructorA (&myA);
ConstructorA (&myB);
int vali, valj;

   vali = 1;
   valj = 2;

   myA.Afni(&myA, vali);
   myA.Afni(&myA, vali,valj);

   if ((myA.a == 1) && (myA.b == 3))
      return(0);
   else
      return(1);
}

