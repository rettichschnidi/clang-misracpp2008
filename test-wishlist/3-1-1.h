void f();                             // compliant
int inline g(int i) { return i * 2; } // compliant
template <typename T>
T qubicT(T t) { return t * t; } // compliant

int a;                             // expected-error {{It shall be possible to include any header file in multiple translation units without violating the One Definition Rule. (MISRA C++ 2008 rule 3-1-1)}}
int h(int i) { return i * 3; }     // expected-error {{It shall be possible to include any header file in multiple translation units without violating the One Definition Rule. (MISRA C++ 2008 rule 3-1-1)}}
int qubic(int t) { return t * t; } // expected-error {{It shall be possible to include any header file in multiple translation units without violating the One Definition Rule. (MISRA C++ 2008 rule 3-1-1)}}
