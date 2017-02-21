#include<stdio.h>
#include<stdlib.h>

struct mystruct {
   float f;
};

struct
E {
   float
      abc ; 



struct mystruct* (*Emethod) (struct E *);
};



/* complex class structure with initialized variable */


struct mystruct* Emethod (struct E * object) {
   struct mystruct *ptr;
      ptr = malloc(sizeof(struct mystruct));
      ptr->f = object->abc;
      return(ptr);
   } 

void ConstructorE (struct E* newStruct) {
	newStruct->Emethod = &Emethod;
}
int main(int argc, char *argv[]) {
struct E myE;
ConstructorE (&myE);
struct mystruct *p;
   
   p = myE.Emethod(&myE);
   if (p->f == 1.2f)
      return(0);
   else
      return(1);
}

