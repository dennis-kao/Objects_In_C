#include <stdlib.h>

struct A {
   int a, *b, **c, d;
   char hello;

   int (*Aaddic) (int, char);
}

constructorA (struct A *this) {
  this->Aaddic = &Aaddic;
}

int main() {

  struct A hello;
  constructorA (&hello);
}
