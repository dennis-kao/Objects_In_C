#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct A {
int a;
   int (*Asumiii) (struct A *, int, int, int);
};


int Asumiii (struct A * object, int x, int y, int z) {
      return(x+ y +z);
   } 

void ConstructorA (struct A* newStruct) {
	newStruct->Asumiii = &Asumiii;
}
struct B {
   float a, b, c;
   void (*Bsetaf) (struct B *, float);
   void (*Bsetbf) (struct B *, float);
   void (*Bsetcf) (struct B *, float);
   float (*Bgeta) (struct B *);
   float (*Bgetb) (struct B *);
   float (*Bgetc) (struct B *);
};




void Bsetaf (struct B * object, float value) {
      object->a = value;
   } 

void Bsetbf (struct B * object, float value) {
      object->b = value;
   } 

void Bsetcf (struct B * object, float value) {
      object->c = value;
   } 

float Bgeta (struct B * object) {
      return(object->a);
   } 

float Bgetb (struct B * object) {
      return(object->b);
   } 

float Bgetc (struct B * object) {
      return(object->c);
   } 

void ConstructorB (struct B* newStruct) {
	newStruct->Bsetaf = &Bsetaf;
	newStruct->Bsetbf = &Bsetbf;
	newStruct->Bsetcf = &Bsetcf;
	newStruct->Bgeta = &Bgeta;
	newStruct->Bgetb = &Bgetb;
	newStruct->Bgetc = &Bgetc;
}
int main(int argc, char *argv[]) {
struct A myA;
ConstructorA (&myA);
int total;
int a, b, c;
struct B myB;
ConstructorB (&myB);
float val;

   a = 1;
   b = 2;
   c = 3;

   total = myA.Asumiii(&myA, a, b, c);
   printf("output shoudl be 6: %d\n", total);

   val =1.5;
   myB.Bsetaf(&myB, val);
   printf("output should be 1.50000: %f\n", myB.Bgeta(&myB));

}

