// RUN: %clang -fsyntax-only -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 18-0-5 %s
#include <cstring>
void useStrcp(char out[]) {
    strcpy(out, "illegal"); // expected-error {{The unbounded functions of library <cstring> shall not be used.}}
}

void useStrcmp(char out[]) {
    int i = strcmp(out, "illegal"); // expected-error {{The unbounded functions of library <cstring> shall not be used.}}
}

void useSrcat(char out[]) {
    strcat(out, "illegal"); // expected-error {{The unbounded functions of library <cstring> shall not be used.}}
}

void useStrchr(char out[]) {
    char *c = strchr(out, 'a'); // expected-error {{The unbounded functions of library <cstring> shall not be used.}}
}

void useStrspn(char out[]) {
    size_t i = strspn(out, "needle"); // expected-error {{The unbounded functions of library <cstring> shall not be used.}}
}

void useStrcspn(char out[]) {
    size_t i = strcspn(out, "non-needle"); // expected-error {{The unbounded functions of library <cstring> shall not be used.}}
}

void useStrpbrk(char out[]) {
    char *c = strpbrk(out, "xyz"); // expected-error {{The unbounded functions of library <cstring> shall not be used.}}
}

void useStrrchr(char out[]) {
    char *c = strrchr(out, 'z'); // expected-error {{The unbounded functions of library <cstring> shall not be used.}}
}

void useStrstr(char out[]) {
    char *c = strstr(out, "needle"); // expected-error {{The unbounded functions of library <cstring> shall not be used.}}
}

void useStr(char out[]) {
    char *c = strtok(out, "x"); // expected-error {{The unbounded functions of library <cstring> shall not be used.}}
}

void useStrlen(char out[]) {
    size_t i = strlen(out); // expected-error {{The unbounded functions of library <cstring> shall not be used.}}
}



