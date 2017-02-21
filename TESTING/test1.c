#include<stdio.h>
#include<stdlib.h>


struct A {
   int a;
};



/* reference a class variable */


void ConstructorA (struct A* newStruct) {
}
int main(int argc, char *argv[]) {
struct A myA;
   ConstructorA (&myA);
myA.a = 3;
   if (myA.a == 3)
      return(0);
   else
      return(1);
}

