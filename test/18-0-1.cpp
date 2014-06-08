// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 18-0-1 %s
#include <assert.h> // expected-error {{The C library shall not be used.}}
#include <ctype.h> // expected-error {{The C library shall not be used.}}
#include <errno.h> // expected-error {{The C library shall not be used.}}
#include <fenv.h> // expected-error {{The C library shall not be used.}}
#include <float.h> // expected-error {{The C library shall not be used.}}
#include <inttypes.h> // expected-error {{The C library shall not be used.}}
#include <iso646.h> // expected-error {{The C library shall not be used.}}
#include <limits.h> // expected-error {{The C library shall not be used.}}
#include <locale.h> // expected-error {{The C library shall not be used.}}
#include <math.h> // expected-error {{The C library shall not be used.}}
#include <setjmp.h> // expected-error {{The C library shall not be used.}}
#include <signal.h> // expected-error {{The C library shall not be used.}}
#include <stdarg.h> // expected-error {{The C library shall not be used.}}
#include <stdbool.h> // expected-error {{The C library shall not be used.}}
#include <stddef.h> // expected-error {{The C library shall not be used.}}
#include <stdint.h> // expected-error {{The C library shall not be used.}}
#include <stdlib.h> // expected-error {{The C library shall not be used.}}
#include <string.h> // expected-error {{The C library shall not be used.}}
#include <tgmath.h> // expected-error {{The C library shall not be used.}}
#include <time.h> // expected-error {{The C library shall not be used.}}
#include <wchar.h> // expected-error {{The C library shall not be used.}}
#include <wctype.h> // expected-error {{The C library shall not be used.}}

#include <cassert> 
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstdbool>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctgmath>
#include <ctime>
#include <cwchar>
#include <cwctype>

