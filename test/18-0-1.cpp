// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 18-0-1 %s
#include <assert.h>   // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <ctype.h>    // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <errno.h>    // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <fenv.h>     // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <float.h>    // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <inttypes.h> // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <iso646.h>   // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <limits.h>   // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <locale.h>   // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <math.h>     // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <setjmp.h>   // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <signal.h>   // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <stdarg.h>   // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <stdbool.h>  // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <stddef.h>   // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <stdint.h>   // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <stdlib.h>   // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <string.h>   // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <tgmath.h>   // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <time.h>     // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <wchar.h>    // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}
#include <wctype.h>   // expected-error {{The C library shall not be used. (MISRA C++ 2008 rule 18-0-1)}}

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
