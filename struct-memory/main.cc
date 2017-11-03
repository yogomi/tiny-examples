// Copyright 2015 Makoto Yano

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct S {
  int a;
  char c[19];
  int b;
  void F() {
    printf("%d %d", a, b);
    return;
  }
};

void F(void* p) {
  S* s = static_cast<S*>(p);
  printf("%d %d %lu", s->a, s->b, sizeof(S));
}

int main() {
  shared_ptr<void>p(new S);
  void* pv = malloc(sizeof(S));


  p->a = 8;
  p->b = 2031;
  memcpy(pv, p.get(), sizeof(S));

  F(pv);

  delete p;
  free(pv);
  return 0;
}
