// RUN: %clang -fsyntax-only -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 5-0-5 %s

int i;
float f;

float implicitIntToFloat = i; // expected-error {{There shall be no implicit floating-integral conversions. (MISRA C++ 2008 rule 5-0-5)}}
float explicitIntToFloat = static_cast<float>(i);

int implicitFloatToInt = f; // expected-error {{There shall be no implicit floating-integral conversions. (MISRA C++ 2008 rule 5-0-5)}}
int explicitFloatToInt = static_cast<int>(f);

int explicitDoubleWithImplicitIntCast = static_cast<double>(f); // expected-error {{There shall be no implicit floating-integral conversions. (MISRA C++ 2008 rule 5-0-5)}}
