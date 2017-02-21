#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int a;

	/* different ways to access variables */
struct A {
int a;
   void (*Aprint1i) (struct A *, int);
   void (*Aprint2) (struct A *);
   void (*Aprint3) (struct A *);
};


void Aprint1i (struct A * object, int a) {
		/* print parameter - local to the function*/
      printf("output should be 1: %d\n", a);
   } 

void Aprint2 (struct A * object) {
		/* create a local variable*/
      int a = 2;
		/* print local variable*/
      printf("output should be 2: %d\n", a);
   } 

void Aprint3 (struct A * object) {
		/* there is a class variable named a so*/
		/* assign value to it and print the class variable*/
      object->a = 3;
      printf("output should be 3: %d\n", object->a);
   } 

void ConstructorA (struct A* newStruct) {
	newStruct->Aprint1i = &Aprint1i;
	newStruct->Aprint2 = &Aprint2;
	newStruct->Aprint3 = &Aprint3;
}
struct B {
   void (*Bprint4) (struct B *);
};

	/* simple function outside of a class */

void Bprint4 (struct B * object) {
		/* there is no class variable named a so print global variable*/
      printf("output should be 4: %d\n", a);
   } 

void ConstructorB (struct B* newStruct) {
	newStruct->Bprint4 = &Bprint4;
}
float product(float a, float b) {
   return( a*b );
}



int main(int argc, char *argv[]) {
struct A myA;
ConstructorA (&myA);
struct B myB;
ConstructorB (&myB);
int value;
char str[100];

   printf("Hello \" there\n");
   strcpy(str, "A string containing the word class may be tricky");

   a = 4;
   value = 1;

   myA.Aprint1i(&myA, value);
   myA.Aprint2(&myA);
   myA.Aprint3(&myA);

   myB.Bprint4(&myB);

}

