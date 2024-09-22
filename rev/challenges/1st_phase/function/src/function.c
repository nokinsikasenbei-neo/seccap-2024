#include <stdio.h>

// many nesting functions

void FLAG(){
    printf("FLAG は、この関数を呼び出している関数名を_で連結したものです。\n");
    printf("連結する順番は、アルファベット順です。\n");
    printf("例：この関数がa1とb1から呼び出されている場合、FLAG{a1_b1}\n");
}

void a5() {
    FLAG();
}

void a4() {
    a5();
}

void a3() {
    a4();
}

void a2() {
    a3();
}

void a1() {
    a2();
}

void A() {
    a1();
}

void b5() {
}

void b4() {
    b5();
    FLAG();
}

void b3() {
    b4();
}

void b2() {
    b3();
}

void b1() {
    b2();
}

void B() {
    b1();
}

void c5() {
}

void c4() {
    c5();
}

void c3() {
    c4();
    FLAG();
}

void c2() {
    c3();
}

void c1() {
    c2();
}

void C() {
    c1();
}

void d5() {
}

void d4() {
    d5();
}

void d3() {
    d4();
    FLAG();
}

void d2() {
    d3();
}

void d1() {
    d2();
}

void D() {
    d1();
}

int main(void) {

    A();
    B();
    C();
    D();
}