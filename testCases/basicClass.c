#include <stdlib.h>

struct A {
	int a, *b, **c;
	int d;
  char hello;
  int z;
  
  /*this is a comment */
  
  int (*Afirstsci) (struct A *, signed char, int);
  
  int (*Adivsci) (struct A *, signed char, int);

	int (*Aaddc) (struct A *, char);
  
  int (*ADIV2ci) (struct A *, char, int);
  
  int (*ADIV3ci) (struct A *, char, int);
}

int 
int Afirstsci (struct A * object, signed char d, int c) {
    /*int d;*/
		char z;
		float lilBoat;
		return (object->b+z+c+d);
  } 

int Adivsci (struct A * object, signed char b, int d) {
		char f;
    return (object->a-b+object->c);
  } 

int Aaddc (struct A * object, char d) {
		/*int d;*/
		char z;
		float lilBoat;
		return (object->b+object->a+object->c+d);
	} 

int ADIV2ci (struct A * object, char d, int c) {
    return (object->b /
c);
  } 

int ADIV3ci (struct A * object, char d, int c) {
    return (object->b    -    c);
  } 

void ConstructorA (struct A* newStruct) {
	newStruct->Afirstsci = &Afirstsci;
	newStruct->Adivsci = &Adivsci;
	newStruct->Aaddc = &Aaddc;
	newStruct->ADIV2ci = &ADIV2ci;
	newStruct->ADIV3ci = &ADIV3ci;
}
main() {
	/* this is also a comment */
	/*double slash comment lord save me!*/
 struct A DEATHTOPONIES;
 ConstructorA (&DEATHTOPONIES);
int temp;
 int hello;
 
 DEATHTOPONIES.Aaddc(&DEATHTOPONIES, temp);
}
