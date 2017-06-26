// Copyright 2017 Makoto Yano

#include <stdio.h>

class BaseClass {
 public:
  BaseClass();
  virtual ~BaseClass();

  static int n;

  virtual void F();
  virtual void G();
  void H();
  static void PrintNum() {
    printf("static number is %d\n", n);
  }

  BaseClass(const BaseClass &b);
 private:
};

int BaseClass::n = 0;

BaseClass::BaseClass() {
  printf("BaseClass constructor\n");
  n++;
}

BaseClass::BaseClass(const BaseClass &b) {
  printf("BaseClass copy constructor\n");
  n++;
}

BaseClass::~BaseClass() {
  printf("BaseClass destructor\n");
  n--;
}

void BaseClass::F() {
  printf("BaseClass F()\n");
}

void BaseClass::G() {
  printf("BaseClass G()\n");
}

void BaseClass::H() {
  printf("BaseClass H()\n");
}

class DerivationClass: public BaseClass {
 public:
  DerivationClass();
  ~DerivationClass();

  virtual void F();
  void G();
  void H();
};

DerivationClass::DerivationClass() {
  printf("DerivationClass constructor\n");
}

DerivationClass::~DerivationClass() {
  printf("DerivationClass destructor\n");
}

void DerivationClass::F() {
  printf("DerivationClass F()\n");
}

void DerivationClass::G() {
  printf("DerivationClass G()\n");
}

void DerivationClass::H() {
  printf("DerivationClass H()\n");
}

int main() {
  BaseClass::PrintNum();
  {
    BaseClass b = DerivationClass();
    b.F();
    b.G();
    b.H();
  }
  BaseClass::PrintNum();
  {
    BaseClass *b = new DerivationClass;
    b->F();
    b->G();
    b->H();
    delete b;
  }

  printf("end\n");
  return 0;
}
