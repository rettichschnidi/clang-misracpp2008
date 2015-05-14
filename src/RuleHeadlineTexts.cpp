//===-  RuleHeadlineTexts.cpp - MISRA C++:2008 rule headlines--------------===//
//
// This file contains a list with headline of each MISRA C++:2008 rule.
//
// Copyright (C) 2008 - MISRA Consortium, www.misra-cpp.com
//
// Please note: According to a lawyer I have consulted, the Swiss copyright law
// (most likely) allows the usage of such small snippets taken from a protected
// work.
//
//===----------------------------------------------------------------------===//

#include "RuleHeadlineTexts.h"
#include <cstring>
#include <iostream>
#include <cassert>

namespace misracpp2008 {

extern const RuleHeadlineMap ruleHeadlines = {
// Unnecessary constructs
{ "0-1-1", R"ruletext(A project shall not contain unreachable code.)ruletext" },
{ "0-1-2", R"ruletext(A project shall not contain infeasible paths.)ruletext" },
{ "0-1-3", R"ruletext(A project shall not contain unused variables.)ruletext" },
{ "0-1-4", R"ruletext(A project shall not contain non-volatile POD variables having only one use.)ruletext" },
{ "0-1-5", R"ruletext(A project shall not contain unused type declarations.)ruletext" },
{ "0-1-6", R"ruletext(A project shall not contain instances of non-volatile variables being given values that are never subsequently used.)ruletext" },
{ "0-1-7", R"ruletext(The value returned by a function having a non-void return type that is not an overloaded operator shall always be used.)ruletext" },
{ "0-1-8", R"ruletext(All functions with void return type shall have external side effect(s).)ruletext" },
{ "0-1-9", R"ruletext(There shall be no dead code.)ruletext" },
{ "0-1-10", R"ruletext(Every defined function shall be called at least once.)ruletext" },
{ "0-1-11", R"ruletext(There shall be no unused parameters (named or unnamed) in non-virtual functions.)ruletext" },
{ "0-1-12", R"ruletext(There shall be no unused parameters (named or unnamed) in the set of parameters for a virtual function and all the functions that override it.)ruletext" },

// Storage
{ "0-2-1", R"ruletext(An object shall not be assigned to an overlapping object.)ruletext" },

// Runtime failures
{ "0-3-1", R"ruletext(Minimization of run-time failures shall be ensured by the use of at least one of: (a) static analysis tools/techniques; (b) dynamic analysis tools/techniques; (c) explicit coding of checks to handle run-time faults.)ruletext" },
{ "0-3-2", R"ruletext(If a function generates error information, then that error information shall be tested.)ruletext" },

// Arithmetic
{ "0-4-1", R"ruletext(Use of scaled-integer or fixed-point arithmetic shall be documented.)ruletext" },
{ "0-4-2", R"ruletext(Use of floating-point arithmetic shall be documented.)ruletext" },
{ "0-4-3", R"ruletext(Floating-point implementations shall comply with a defined floating-point standard.)ruletext" },

// Language
{ "1-0-1", R"ruletext(All code shall conform to ISO/IEC 14882:2003 "The C++ Standard Incorporating Technical Corrigendum 1.)ruletext" },
{ "1-0-2", R"ruletext(Multiple compilers shall only be used if they have a common, defined interface.)ruletext" },
{ "1-0-3", R"ruletext(The implementation of integer division in the chosen compiler shall be determined and documented.)ruletext" },

// Character sets
{ "2-2-1", R"ruletext(The character set and the corresponding encoding shall be documented.)ruletext" },

// Trigraph sequences
{ "2-3-1", R"ruletext(Trigraphs shall not be used.)ruletext" },

// Alternative tokens
{ "2-5-1", R"ruletext(Digraphs should not be used.)ruletext" },

// Comments
{ "2-7-1", R"ruletext(The character sequence /* shall not be used within a C-style comment.)ruletext" },
{ "2-7-2", R"ruletext(Sections of code shall not be "commented out" using C-style comments.)ruletext" },
{ "2-7-3", R"ruletext(Sections of code should not be "commented out" using C++ comments.)ruletext" },

// Identifiers
{ "2-10-1", R"ruletext(Different identifiers shall be typographically unambiguous.)ruletext" },
{ "2-10-2", R"ruletext(Identifiers declared in an inner scope shall not hide an identifier declared in an outer scope.)ruletext" },
{ "2-10-3", R"ruletext(A typedef name (including qualification, if any) shall be a unique identifier.)ruletext" },
{ "2-10-4", R"ruletext(A class, union or enum name (including qualification, if any) shall be a unique identifier.)ruletext" },
{ "2-10-5", R"ruletext(The identifier name of a non-member object or function with static storage duration should not be reused.)ruletext" },
{ "2-10-6", R"ruletext(If an identifier refers to a type, it shall not also refer to an object or a function in the same scope.)ruletext" },

// Literals
{ "2-13-1", R"ruletext(Only those escape sequences that are defined in ISO/IEC 14882:2003 shall be used.)ruletext" },
{ "2-13-2", R"ruletext(Octal constants (other than zero) and octal escape sequences (other than "\0") shall not be used.)ruletext" },
{ "2-13-3", R"ruletext(A "U " suffix shall be applied to all octal or hexadecimal integer literals of unsigned type.)ruletext" },
{ "2-13-4", R"ruletext(Literal suffixes shall be upper case.)ruletext" },
{ "2-13-5", R"ruletext(Narrow and wide string literals shall not be concatenated.)ruletext" },

// Declarations and definitions
{ "3-1-1", R"ruletext(It shall be possible to include any header file in multiple translation units without violating the One Definition Rule.)ruletext" },
{ "3-1-2", R"ruletext(Functions shall not be declared at block scope.)ruletext" },
{ "3-1-3", R"ruletext(When an array is declared, its size shall either be stated explicitly or defined implicitly by initialization.)ruletext" },

// One Definition Rule
{ "3-2-1", R"ruletext(All declarations of an object or function shall have compatible types.)ruletext" },
{ "3-2-2", R"ruletext(The One Definition Rule shall not be violated.)ruletext" },
{ "3-2-3", R"ruletext(A type, object or function that is used in multiple translation units shall be declared in one and only one file.)ruletext" },
{ "3-2-4", R"ruletext(An identifier with external linkage shall have exactly one definition.)ruletext" },

// Declarative regions and scope
{ "3-3-1", R"ruletext(Objects or functions with external linkage shall be declared in a header file.)ruletext" },
{ "3-3-2", R"ruletext(If a function has internal linkage then all re-declarations shall include the static storage class specifier.)ruletext" },

// Name lookup
{ "3-4-1", R"ruletext(An identifier declared to be an object or type shall be defined in a block that minimizes its visibility.)ruletext" },

// Types
{ "3-9-1", R"ruletext(The types used for an object, a function return type, or a function parameter shall be token-for-token identical in all declarations and re-declarations.)ruletext" },
{ "3-9-2", R"ruletext(typedefs that indicate size and signedness should be used in place of the basic numerical types.)ruletext" },
{ "3-9-3", R"ruletext(The underlying bit representations of floating-point values shall not be used.)ruletext" },

// Integral promotions
{ "4-5-1", R"ruletext(Expressions with type bool shall not be used as operands to built-in operators other than the assignment operator = , the logical operators && , || , ! , the equality operators == and != , the unary & operator, and the conditional operator.)ruletext" },
{ "4-5-2", R"ruletext(Expressions with type enum shall not be used as operands to built-in operators other than the subscript operator [ ] , the assignment operator = , the equality operators == and != , the unary & operator, and the relational operators < , <= , > , >= .)ruletext" },
{ "4-5-3", R"ruletext(Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator.)ruletext" },

// Pointer conversions
{ "4-10-1", R"ruletext(NULL shall not be used as an integer value.)ruletext" },
{ "4-10-2", R"ruletext(Literal zero (0) shall not be used as the null-pointer-constant.)ruletext" },

// Expressions
{ "5-0-1", R"ruletext(The value of an expression shall be the same under any order of evaluation that the standard permits.)ruletext" },
{ "5-0-2", R"ruletext(Limited dependence should be placed on C++ operator precedence rules in expressions.)ruletext" },
{ "5-0-3", R"ruletext(A cvalue expression shall not be implicitly converted to a different underlying type.)ruletext" },
{ "5-0-4", R"ruletext(An implicit integral conversion shall not change the signedness of the underlying type.)ruletext" },
{ "5-0-5", R"ruletext(There shall be no implicit floating-integral conversions.)ruletext" },
{ "5-0-6", R"ruletext(An implicit integral or floating-point conversion shall not reduce the size of the underlying type.)ruletext" },
{ "5-0-7", R"ruletext(There shall be no explicit floating-integral conversions of a cvalue expression.)ruletext" },
{ "5-0-8", R"ruletext(An explicit integral or floating-point conversion shall not increase the size of the underlying type of a cvalue expression.)ruletext" },
{ "5-0-9", R"ruletext(An explicit integral conversion shall not change the signedness of the underlying type of a cvalue expression.)ruletext" },
{ "5-0-10", R"ruletext(If the bitwise operators ~ and << are applied to an operand with an underlying type of unsigned char or unsigned short, the result shall be immediately cast to the underlying type of the operand.)ruletext" },
{ "5-0-11", R"ruletext(The plain char type shall only be used for the storage and use of character values.)ruletext" },
{ "5-0-12", R"ruletext(signed char and unsigned char type shall only be used for the storage and use of numeric values.)ruletext" },
{ "5-0-13", R"ruletext(The condition of an if-statement and the condition of an iteration-statement shall have type bool.)ruletext" },
{ "5-0-14", R"ruletext(The first operand of a conditional-operator shall have type bool.)ruletext" },
{ "5-0-15", R"ruletext(Array indexing shall be the only form of pointer arithmetic.)ruletext" },
{ "5-0-16", R"ruletext(A pointer operand and any pointer resulting from pointer arithmetic using that operand shall both address elements of the same array.)ruletext" },
{ "5-0-17", R"ruletext(Subtraction between pointers shall only be applied to pointers that address elements of the same array.)ruletext" },
{ "5-0-18", R"ruletext(> , >= , < , <= shall not be applied to objects of pointer type, except where they point to the same array.)ruletext" },
{ "5-0-19", R"ruletext(The declaration of objects shall contain no more than two levels of pointer indirection.)ruletext" },
{ "5-0-20", R"ruletext(Non-constant operands to a binary bitwise operator shall have the same underlying type.)ruletext" },
{ "5-0-21", R"ruletext(Bitwise operators shall only be applied to operands of unsigned underlying type.)ruletext" },

// Postfix expressions
{ "5-2-1", R"ruletext(Each operand of a logical && or || shall be a postfix‐expression.)ruletext" },
{ "5-2-2", R"ruletext(A pointer to a virtual base class shall only be cast to a pointer to a derived class by means of dynamic_cast.)ruletext" },
{ "5-2-3", R"ruletext(Casts from a base class to a derived class should not be performed on polymorphic types.)ruletext" },
{ "5-2-4", R"ruletext(C-style casts (other than void casts) and functional notation casts (other than explicit constructor calls) shall not be used.)ruletext" },
{ "5-2-5", R"ruletext(A cast shall not remove any const or volatile qualification from the type of a pointer or reference.)ruletext" },
{ "5-2-6", R"ruletext(A cast shall not convert a pointer to a function to any other pointer type, including a pointer to function type.)ruletext" },
{ "5-2-7", R"ruletext(An object with pointer type shall not be converted to an unrelated pointer type, either directly or indirectly.)ruletext" },
{ "5-2-8", R"ruletext(An object with integer type or pointer to void type shall not be converted to an object with pointer type.)ruletext" },
{ "5-2-9", R"ruletext(A cast should not convert a pointer type to an integral type.)ruletext" },
{ "5-2-10", R"ruletext(The increment ( ++ ) and decrement ( -- ) operators should not be mixed with other operators in an expression.)ruletext" },
{ "5-2-11", R"ruletext(The comma operator, && operator and the || operator shall not be overloaded.)ruletext" },
{ "5-2-12", R"ruletext(An identifier with array type passed as a function argument shall not decay to a pointer.)ruletext" },

// Unary expressions
{ "5-3-1", R"ruletext(Each operand of the ! operator, the logical && or the logical || operators shall have type bool.)ruletext" },
{ "5-3-2", R"ruletext(The unary minus operator shall not be applied to an expression whose underlying type is unsigned.)ruletext" },
{ "5-3-3", R"ruletext(The unary & operator shall not be overloaded.)ruletext" },
{ "5-3-4", R"ruletext(Evaluation of the operand to the sizeof operator shall not contain side effects.)ruletext" },

// Shift operators
{ "5-8-1", R"ruletext(The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand.)ruletext" },

// Logical AND operator
{ "5-14-1", R"ruletext(The right hand operand of a logical && or || operator shall not contain side effects.)ruletext" },

// Assignment operators
{ "5-17-1", R"ruletext(The semantic equivalence between a binary operator and its assignment operator form shall be preserved.)ruletext" },

// Comma operator
{ "5-18-1", R"ruletext(The comma operator shall not be used.)ruletext" },

// Constant expressions
{ "5-19-1", R"ruletext(Evaluation of constant unsigned integer expressions should not lead to wrap-around.)ruletext" },

// Expression statement
{ "6-2-1", R"ruletext(Assignment operators shall not be used in sub-expressions.)ruletext" },
{ "6-2-2", R"ruletext(Floating-point expressions shall not be directly or indirectly tested for equality or inequality.)ruletext" },
{ "6-2-3", R"ruletext(Before preprocessing, a null statement shall only occur on a line by itself; it may be followed by a comment, provided that the first character following the null statement is a white‐space character.)ruletext" },

// Compound statement
{ "6-3-1", R"ruletext(The statement forming the body of a switch, while, do ... while or for statement shall be a compound statement.)ruletext" },

// Selection statements
{ "6-4-1", R"ruletext(An if ( condition ) construct shall be followed by a compound statement. The else keyword shall be followed by either a compound statement, or another if statement.)ruletext" },
{ "6-4-2", R"ruletext(All if ... else if constructs shall be terminated with an else clause.)ruletext" },
{ "6-4-3", R"ruletext(A switch statement shall be a well-formed switch statement.)ruletext" },
{ "6-4-4", R"ruletext(A switch-label shall only be used when the most closely-enclosing compound statement is the body of a switch statement.)ruletext" },
{ "6-4-5", R"ruletext(An unconditional throw or break statement shall terminate every non‐empty switch-clause.)ruletext" },
{ "6-4-6", R"ruletext(The final clause of a switch statement shall be the default-clause.)ruletext" },
{ "6-4-7", R"ruletext(The condition of a switch statement shall not have bool type.)ruletext" },
{ "6-4-8", R"ruletext(Every switch statement shall have at least one case-clause.)ruletext" },

// Iteration statements
{ "6-5-1", R"ruletext(A for loop shall contain a single loop-counter which shall not have floating type.)ruletext" },
{ "6-5-2", R"ruletext(If loop-counter is not modified by -- or ++ , then, within condition, the loop-counter shall only be used as an operand to <= , < , > or >= .)ruletext" },
{ "6-5-3", R"ruletext(The loop-counter shall not be modified within condition or statement.)ruletext" },
{ "6-5-4", R"ruletext(The loop-counter shall be modified by one of: -- , ++ , -=n , or +=n ; where n remains constant for the duration of the loop.)ruletext" },
{ "6-5-5", R"ruletext(A loop-control-variable other than the loop-counter shall not be modified within condition or expression.)ruletext" },
{ "6-5-6", R"ruletext(A loop-control-variable other than the loop-counter which is modified in statement shall have type bool.)ruletext" },

// Jump statements
{ "6-6-1", R"ruletext(Any label referenced by a goto statement shall be declared in the same block, or in a block enclosing the goto statement.)ruletext" },
{ "6-6-2", R"ruletext(The goto statement shall jump to a label declared later in the same function body.)ruletext" },
{ "6-6-3", R"ruletext(The continue statement shall only be used within a well-formed for loop.)ruletext" },
{ "6-6-4", R"ruletext(For any iteration statement there shall be no more than one break or goto statement used for loop termination.)ruletext" },
{ "6-6-5", R"ruletext(A function shall have a single point of exit at the end of the function.)ruletext" },

// Specifiers
{ "7-1-1", R"ruletext(A variable which is not modified shall be const qualified.)ruletext" },
{ "7-1-2", R"ruletext(A pointer or reference parameter in a function shall be declared as pointer to const or reference to const if the corresponding object is not modified.)ruletext" },

// Enumeration declarations
{ "7-2-1", R"ruletext(An expression with enum underlying type shall only have values corresponding to the enumerators of the enumeration.)ruletext" },

// Namespaces
{ "7-3-1", R"ruletext(The global namespace shall only contain main, namespace declarations and extern "C" declarations.)ruletext" },
{ "7-3-2", R"ruletext(The identifier main shall not be used for a function other than the global function main.)ruletext" },
{ "7-3-3", R"ruletext(There shall be no unnamed namespaces in header files.)ruletext" },
{ "7-3-4", R"ruletext(using-directives shall not be used.)ruletext" },
{ "7-3-5", R"ruletext(Multiple declarations for an identifier in the same namespace shall not straddle a using-declaration for that identifier.)ruletext" },
{ "7-3-6", R"ruletext(using-directives and using-declarations (excluding class scope or function scope using-declarations) shall not be used in header files.)ruletext" },

// The asm declaration
{ "7-4-1", R"ruletext(All usage of assembler shall be documented.)ruletext" },
{ "7-4-2", R"ruletext(Assembler instructions shall only be introduced using the asm declaration.)ruletext" },
{ "7-4-3", R"ruletext(Assembly language shall be encapsulated and isolated.)ruletext" },

// Linkage specifications
{ "7-5-1", R"ruletext(A function shall not return a reference or a pointer to an automatic variable (including parameters), defined within the function.)ruletext" },
{ "7-5-2", R"ruletext(The address of an object with automatic storage shall not be assigned to another object that may persist after the first object has ceased to exist.)ruletext" },
{ "7-5-3", R"ruletext(A function shall not return a reference or a pointer to a parameter that is passed by reference or const reference.)ruletext" },
{ "7-5-4", R"ruletext(Functions should not call themselves, either directly or indirectly.)ruletext" },

// Declarators - General
{ "8-0-1", R"ruletext(An init-declarator-list or a member-declarator-list shall consist of a single init-declarator or member-declarator respectively.)ruletext" },

// Meaning of declarators
{ "8-3-1", R"ruletext(Parameters in an overriding virtual function shall either use the same default arguments as the function they override, or else shall not specify any default arguments.)ruletext" },

// Function definitions
{ "8-4-1", R"ruletext(Functions shall not be defined using the ellipsis notation.)ruletext" },
{ "8-4-2", R"ruletext(The identifiers used for the parameters in a re-declaration of a function shall be identical to those in the declaration.)ruletext" },
{ "8-4-3", R"ruletext(All exit paths from a function with non-void return type shall have an explicit return statement with an expression.)ruletext" },
{ "8-4-4", R"ruletext(A function identifier shall either be used to call the function or it shall be preceded by & .)ruletext" },

// Declarators - Initializers
{ "8-5-1", R"ruletext(All variables shall have a defined value before they are used.)ruletext" },
{ "8-5-2", R"ruletext(Braces shall be used to indicate and match the structure in the non-zero initialization of arrays and structures.)ruletext" },
{ "8-5-3", R"ruletext(In an enumerator list, the = construct shall not be used to explicitly initialize members other than the first, unless all items are explicitly initialized.)ruletext" },

// Member functions
{ "9-3-1", R"ruletext(const member functions shall not return non-const pointers or references to class-data.)ruletext" },
{ "9-3-2", R"ruletext(Member functions shall not return non-const handles to class-data.)ruletext" },
{ "9-3-3", R"ruletext(If a member function can be made static then it shall be made static, otherwise if it can be made const then it shall be made const.)ruletext" },

// Unions
{ "9-5-1", R"ruletext(Unions shall not be used.)ruletext" },

// Bit-fields
{ "9-6-1", R"ruletext(When the absolute positioning of bits representing a bit-field is required, then the behaviour and packing of bit-fields shall be documented.)ruletext" },
{ "9-6-2", R"ruletext(Bit-fields shall be either bool type or an explicitly unsigned or signed integral type.)ruletext" },
{ "9-6-3", R"ruletext(Bit-fields shall not have enum type.)ruletext" },
{ "9-6-4", R"ruletext(Named bit-fields with signed integer type shall have a length of more than one bit.)ruletext" },

// Multiple base classes
{ "10-1-1", R"ruletext(Classes should not be derived from virtual bases.)ruletext" },
{ "10-1-2", R"ruletext(A base class shall only be declared virtual if it is used in a diamond hierarchy.)ruletext" },
{ "10-1-3", R"ruletext(An accessible base class shall not be both virtual and non-virtual in the same hierarchy.)ruletext" },

// Member name lookup
{ "10-2-1", R"ruletext(All accessible entity names within a multiple inheritance hierarchy should be unique.)ruletext" },

// Virtual functions
{ "10-3-1", R"ruletext(There shall be no more than one definition of each virtual function on each path through the inheritance hierarchy.)ruletext" },
{ "10-3-2", R"ruletext(Each overriding virtual function shall be declared with the virtual keyword.)ruletext" },
{ "10-3-3", R"ruletext(A virtual function shall only be overridden by a pure virtual function if it is itself declared as pure virtual.)ruletext" },

// Member access control - General
{ "11-0-1", R"ruletext(Member data in non-POD class types shall be private.)ruletext" },

// Constructors
{ "12-1-1", R"ruletext(An object’s dynamic type shall not be used from the body of its constructor or destructor.)ruletext" },
{ "12-1-2", R"ruletext(All constructors of a class should explicitly call a constructor for all of its immediate base classes and all virtual base classes.)ruletext" },
{ "12-1-3", R"ruletext(All constructors that are callable with a single argument of fundamental type shall be declared explicit.)ruletext" },

// Copying class objects
{ "12-8-1", R"ruletext(A copy constructor shall only initialize its base classes and the non-static members of the class of which it is a member.)ruletext" },
{ "12-8-2", R"ruletext(The copy assignment operator shall be declared protected or private in an abstract class.)ruletext" },

// Template declarations
{ "14-5-1", R"ruletext(A non-member generic function shall only be declared in a namespace that is not an associated namespace.)ruletext" },
{ "14-5-2", R"ruletext(A copy constructor shall be declared when there is a template constructor with a single parameter that is a generic parameter.)ruletext" },
{ "14-5-3", R"ruletext(A copy assignment operator shall be declared when there is a template assignment operator with a parameter that is a generic parameter.)ruletext" },

// Name resolution
{ "14-6-1", R"ruletext(In a class template with a dependent base, any name that may be found in that dependent base shall be referred to using a qualified-id or this->)ruletext" },
{ "14-6-2", R"ruletext(The function chosen by overload resolution shall resolve to a function declared previously in the translation unit.)ruletext" },

// Template instantiation and specialization
{ "14-7-1", R"ruletext(All class templates, function templates, class template member functions and class template static members shall be instantiated at least once.)ruletext" },
{ "14-7-2", R"ruletext(For any given template specialization, an explicit instantiation of the template with the template-arguments used in the specialization shall not render the program ill-formed.)ruletext" },
{ "14-7-3", R"ruletext(All partial and explicit specializations for a template shall be declared in the same file as the declaration of their primary template.)ruletext" },

// Function template specialization
{ "14-8-1", R"ruletext(Overloaded function templates shall not be explicitly specialized.)ruletext" },
{ "14-8-2", R"ruletext(The viable function set for a function call should either contain no function specializations, or only contain function specializations.)ruletext" },

// Exception handling - General
{ "15-0-1", R"ruletext(Exceptions shall only be used for error handling.)ruletext" },
{ "15-0-2", R"ruletext(An exception object should not have pointer type.)ruletext" },
{ "15-0-3", R"ruletext(Control shall not be transferred into a try or catch block using a goto or a switch statement.)ruletext" },

// Throwing an exception
{ "15-1-1", R"ruletext(The assignment-expression of a throw statement shall not itself cause an exception to be thrown.)ruletext" },
{ "15-1-2", R"ruletext(NULL shall not be thrown explicitly.)ruletext" },
{ "15-1-3", R"ruletext(An empty throw ( throw; ) shall only be used in the compound-statement of a catch handler.)ruletext" },

// Handling an exception
{ "15-3-1", R"ruletext(Exceptions shall be raised only after start-up and before termination of the program.)ruletext" },
{ "15-3-2", R"ruletext(There should be at least one exception handler to catch all otherwise unhandled exceptions)ruletext" },
{ "15-3-3", R"ruletext(Handlers of a function-try-block implementation of a class constructor or destructor shall not reference non-static members from this class or its bases.)ruletext" },
{ "15-3-4", R"ruletext(Each exception explicitly thrown in the code shall have a handler of a compatible type in all call paths that could lead to that point.)ruletext" },
{ "15-3-5", R"ruletext(A class type exception shall always be caught by reference.)ruletext" },
{ "15-3-6", R"ruletext(Where multiple handlers are provided in a single try-catch statement or function-try-block for a derived class and some or all of its bases, the handlers shall be ordered most-derived to base class.)ruletext" },
{ "15-3-7", R"ruletext(Where multiple handlers are provided in a single try-catch statement or function-try-block, any ellipsis (catch-all) handler shall occur last.)ruletext" },

// Exception specifications
{ "15-4-1", R"ruletext(If a function is declared with an exception-specification, then all declarations of the same function (in other translation units) shall be declared with the same set of type-ids.)ruletext" },

// Exception handling - Special functions
{ "15-5-1", R"ruletext(A class destructor shall not exit with an exception.)ruletext" },
{ "15-5-2", R"ruletext(Where a function’s declaration includes an exception-specification, the function shall only be capable of throwing exceptions of the indicated type(s).)ruletext" },
{ "15-5-3", R"ruletext(The terminate() function shall not be called implicitly.)ruletext" },

// Preprocessing directives - General
{ "16-0-1", R"ruletext(#include directives in a file shall only be preceded by other preprocessor directives or comments.)ruletext" },
{ "16-0-2", R"ruletext(Macros shall only be #define’d or #undef’d in the global namespace.)ruletext" },
{ "16-0-3", R"ruletext(#undef shall not be used.)ruletext" },
{ "16-0-4", R"ruletext(Function-like macros shall not be defined.)ruletext" },
{ "16-0-5", R"ruletext(Arguments to a function-like macro shall not contain tokens that look like preprocessing directives.)ruletext" },
{ "16-0-6", R"ruletext(In the definition of a function-like macro, each instance of a parameter shall be enclosed in parentheses, unless it is used as the operand of # or ## .)ruletext" },
{ "16-0-7", R"ruletext(Undefined macro identifiers shall not be used in #if or #elif preprocessor directives, except as operands to the defined operator.)ruletext" },
{ "16-0-8", R"ruletext(If the # token appears as the first token on a line, then it shall be immediately followed by a preprocessing token.)ruletext" },

// Conditional inclusion
{ "16-1-1", R"ruletext(The defined preprocessor operator shall only be used in one of the two standard forms.)ruletext" },
{ "16-1-2", R"ruletext(All #else, #elif and #endif preprocessor directives shall reside in the same file as the #if or #ifdef directive to which they are related.)ruletext" },

// Source file inclusion
{ "16-2-1", R"ruletext(The pre-processor shall only be used for file inclusion and include guards.)ruletext" },
{ "16-2-2", R"ruletext(C++ macros shall only be used for: include guards, type qualifiers, or storage class specifiers.)ruletext" },
{ "16-2-3", R"ruletext(Include guards shall be provided.)ruletext" },
{ "16-2-4", R"ruletext(The ' , " , /* or // characters shall not occur in a header file name.)ruletext" },
{ "16-2-5", R"ruletext(The \ character should not occur in a header file name.)ruletext" },
{ "16-2-6", R"ruletext(The #include directive shall be followed by either a <filename> or "filename" sequence.)ruletext" },

// Macro replacement
{ "16-3-1", R"ruletext(There shall be at most one occurrence of the # or ## operators in a single macro definition.)ruletext" },
{ "16-3-2", R"ruletext(The # and ## operators should not be used.)ruletext" },

// Pragma directive
{ "16-6-1", R"ruletext(All uses of the #pragma directive shall be documented.)ruletext" },

// Library introduction - General
{ "17-0-1", R"ruletext(Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined.)ruletext" },
{ "17-0-2", R"ruletext(The names of standard library macros and objects shall not be reused.)ruletext" },
{ "17-0-3", R"ruletext(The names of standard library functions shall not be overridden.)ruletext" },
{ "17-0-4", R"ruletext(All library code shall conform to MISRA C++.)ruletext" },
{ "17-0-5", R"ruletext(The setjmp macro and the longjmp function shall not be used.)ruletext" },

// Language support library - General
{ "18-0-1", R"ruletext(The C library shall not be used.)ruletext" },
{ "18-0-2", R"ruletext(The library functions atof, atoi and atol from library <cstdlib> shall not be used.)ruletext" },
{ "18-0-3", R"ruletext(The library functions abort, exit, getenv and system from library <cstdlib> shall not be used.)ruletext" },
{ "18-0-4", R"ruletext(The time handling functions of library <ctime> shall not be used.)ruletext" },
{ "18-0-5", R"ruletext(The unbounded functions of library <cstring> shall not be used.)ruletext" },

// Language support library - Implementation properties
{ "18-2-1", R"ruletext(The macro offsetof shall not be used.)ruletext" },

// Language support library - Dynamic memory management
{ "18-4-1", R"ruletext(Dynamic heap memory allocation shall not be used.)ruletext" },

// Language support library - Other runtime support
{ "18-7-1", R"ruletext(The signal handling facilities of <csignal> shall not be used.)ruletext" },

// Diagnostics library - Error numbers
{ "19-3-1", R"ruletext(The error indicator errno shall not be used.)ruletext" },

// Input/output library - General
{ "27-0-1", R"ruletext(The stream input/output library <cstdio> shall not be used.)ruletext" }
};

}
