#include<stdio.h>
#include<stdlib.h>
#include<string.h>

double vald;
float  valf;
char   valc;
struct D myD;

struct mystruct {
   float f;
   double d;
   long l;
   short s;
   int i;
   char c;
};

	/* function prototype */
float total (float,float) ;
float product(float , float  ) ;

	/* class with overloaded methods */
struct A {
int a, aa;
int aaa;
	/* add parameters */
   void (*Aaddii) (struct A *, int, int);
	/* add class variables*/
   void (*Aadd) (struct A *);
};

	/* simple function outside of a class */

void Aaddii (struct A * object, int a, int aa) {
      printf("%d\n", a+ aa);
   } 

void Aadd (struct A * object) {
      printf("%d\n", object->a + object->aa);
   } 

void ConstructorA (struct A* newStruct) {
	newStruct->Aaddii = &Aaddii;
	newStruct->Aadd = &Aadd;
}
float product(float a, float b) {
   return( a*b );
}


	/* class with no methods */
struct B {
long b;
short c;
};

	/* class with no variables */

void ConstructorB (struct B* newStruct) {
}
struct C{
   void (*Caddii) (struct C *, int, int);
	/* create a class inside the method*/
   void (*CmakeObject) (struct C *);};


void Caddii (struct C * object, int a, int b) {
      printf("%d\n", a+b);
   } 

void CmakeObject (struct C * object) {
      int a, b;
      struct B myB1;
         ConstructorB (&myB1);
a = 7;
         myB1.b = 3;
         myB1.c = 10;
         printf("output should be 20: %d", a + (int)myB1.b +myB1.c); 

		/* call the method inside the class */
         ptintf("output should be 3: ");
         a = 1; b = 2;
         add(a, b);} 

void ConstructorC (struct C* newStruct) {
	newStruct->Caddii = &Caddii;
	newStruct->CmakeObject = &CmakeObject;
}
struct   D
{
int a,b, c;
   void (*Dsetai) (struct D *, int);
   void (*Dsetbi) (struct D *, int);
   void (*Dsetci) (struct D *, int);
   int (*Dgeta) (struct D *);
   int (*Dgetb) (struct D *);
   int (*Dgetc) (struct D *);
   void (*Dmath) (struct D *);
};


void Dsetai (struct D * object, int val) {
      object->a = val;
   } 

void Dsetbi (struct D * object, int val) {
      object->b = val;
   } 

void Dsetci (struct D * object, int val) {
      object->c = val;
   } 

int Dgeta (struct D * object) {
      return(object->a);
   } 

int Dgetb (struct D * object) {
      return( object->b);
   } 

int Dgetc (struct D * object) {
      return( object->c );
   } 

void Dmath (struct D * object) {
   int result;
      result = object->a + object->b* object->c /object->a;
   } 

void ConstructorD (struct D* newStruct) {
	newStruct->Dsetai = &Dsetai;
	newStruct->Dsetbi = &Dsetbi;
	newStruct->Dsetci = &Dsetci;
	newStruct->Dgeta = &Dgeta;
	newStruct->Dgetb = &Dgetb;
	newStruct->Dgetc = &Dgetc;
	newStruct->Dmath = &Dmath;
}
struct
E {
   float
      abc ; 




struct mystruct* (*Emethod) (struct E *);
   void (*Estring1c) (struct E *, char);
   void (*Estring2c) (struct E *, char*);
};



struct mystruct* Emethod (struct E * object) {
   struct mystruct *ptr;
      int z = 3;
      z++;
      printf("output should be 4 1.200000 : %d %f\n", z, object->abc);

      ptr = malloc(sizeof(struct mystruct));
      return(ptr);
   } 

void Estring1c (struct E * object, char str[]) {
      printf("output should be abcd: %s\n", str);
   } 

void Estring2c (struct E * object, char* str) {
      printf("output should be efgh: %s\n", str);
   } 

void ConstructorE (struct E* newStruct) {
	newStruct->Emethod = &Emethod;
	newStruct->Estring1c = &Estring1c;
	newStruct->Estring2c = &Estring2c;
}
int main(int argc, char *argv[]) {
struct A myA;
ConstructorA (&myA);
struct B myB1,myB2, myB3;
ConstructorB (&myB1);
ConstructorB (&myB2);
ConstructorB (&myB3);
struct C myC;
ConstructorC (&myC);
int x, y;
char str[50];
struct mystruct *sptr;
char *name;
struct E myE;

   ConstructorE (&myE);
printf("Hello \" there\n");
   strcpy(str, "A string containing the word class may be tricky");

   sptr = malloc(sizeof(struct mystruct));

   name = malloc(sizeof(char)*100);

   myA.a = 5;
   myA.aa = 10;
   printf("output should be 15: ");
   myA.Aaddii(&myA);

   x = 4;
   y = 5;
   printf("output should be 9: ");
   myA.Aaddii(&myA, x, y);

   myB3.b = 10;
   myB3.c = 11;
   printf("output should be 10, 11: %ld %d", myB3.b, myB3.c);
   myC.CmakeObject(&myC) ;

	/* comment with a keyword in it class A nota {*/
   x = 11;
   myD.seta(x);
   printf("output should be 11: %d\n", myD.geta());

   free(sptr);
   sptr = myE.Emethod(&myE);
   strcpy(str, "abcd");
   myE.Estring1c(&myE, str);
   strcpy(str, "efgh");
   myE.Estring2c(&myE, str);
}


float total(float a, float b){
   return(a +b );
}

