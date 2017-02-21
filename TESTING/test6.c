#include<stdio.h>
#include<stdlib.h>


struct A{
int a ;
   int (*Afn) (struct A *); }
;


/* unusual formatting */


int Afn (struct A * object) {
      a=3; } 

void ConstructorA (struct A* newStruct) {
	newStruct->Afn = &Afn;
}
int main(int argc, char *argv[])
{
struct A
myA;

   ConstructorA (&myA);
myA.Afn(&myA) ;
   if (myA.a ==3)return(0);
   else return(1) ;
}

