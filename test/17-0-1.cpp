// RUN: %clang -fsyntax-only -ferror-limit=0 -Wno-macro-redefined -Wno-builtin-macro-redefined -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 17-0-1 %s

// Some allowed defines
#define LEGAL_DEFINE
#define DATE "today"
#define FILE myfile.cpp
#define LINE 123
#define STDC_HOSTED 1
#define TIME 0
#define STDC 1
#define ERRNO 99

#undef LEGAL_DEFINE
#undef DATE
#undef FILE
#undef LINE
#undef STDC_HOSTED
#undef TIME
#undef STDC
#undef ERRNO
#undef ASSERT

// The few cases where a macro with two leading underscore can be user specified
#define __STDC_FORMAT_MACROS
#include <stdint.h>
#define __STDC_LIMIT_MACROS
#include <inttypes.h>

// Disallowed usages
#define __cplusplus                         // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#define __DATE__                            // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#define __FILE__                            // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#define __LINE__                            // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#define __STDC_HOSTED__                     // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#define __TIME__                            // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#define __STDC__                            // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#define __STDC_MB_MIGHT_NEQ_WC__            // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#define __STDC_VERSION__                    // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#define __STDC_ISO_10646__                  // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#define __STDCPP_STRICT_POINTER_SAFETY__    // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#define __STDCPP_THREADS__                  // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#define errno                               // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#define assert                              // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#define _ILLEGAL_NAME_WITH_UNDERSCORE_FIRST // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}

#undef __cplusplus                         // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#undef __DATE__                            // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#undef __FILE__                            // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#undef __LINE__                            // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#undef __STDC_HOSTED__                     // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#undef __TIME__                            // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#undef __STDC__                            // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#undef __STDC_MB_MIGHT_NEQ_WC__            // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#undef __STDC_VERSION__                    // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#undef __STDC_ISO_10646__                  // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#undef __STDCPP_STRICT_POINTER_SAFETY__    // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#undef __STDCPP_THREADS__                  // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#undef errno                               // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#undef assert                              // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#undef _ILLEGAL_NAME_WITH_UNDERSCORE_FIRST // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}

#undef define  // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
#define define // expected-error {{Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. (MISRA C++ 2008 rule 17-0-1)}}
