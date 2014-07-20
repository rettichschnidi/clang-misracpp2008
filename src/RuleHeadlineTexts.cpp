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

namespace misracpp2008 {

// Unnecessary constructs
extern const char RULE_TEXT_0_1_1[] = R"ruletext(A project shall not contain unreachable code.)ruletext";
extern const char RULE_TEXT_0_1_2[] = R"ruletext(A project shall not contain infeasible paths.)ruletext";
extern const char RULE_TEXT_0_1_3[] = R"ruletext(A project shall not contain unused variables.)ruletext";
extern const char RULE_TEXT_0_1_4[] = R"ruletext(A project shall not contain non-volatile POD variables having only one use.)ruletext";
extern const char RULE_TEXT_0_1_5[] = R"ruletext(A project shall not contain unused type declarations.)ruletext";
extern const char RULE_TEXT_0_1_6[] = R"ruletext(A project shall not contain instances of non-volatile variables being given values that are never subsequently used.)ruletext";
extern const char RULE_TEXT_0_1_7[] = R"ruletext(The value returned by a function having a non-void return type that is not an overloaded operator shall always be used.)ruletext";
extern const char RULE_TEXT_0_1_8[] = R"ruletext(All functions with void return type shall have external side effect(s).)ruletext";
extern const char RULE_TEXT_0_1_9[] = R"ruletext(There shall be no dead code.)ruletext";
extern const char RULE_TEXT_0_1_10[] = R"ruletext(Every defined function shall be called at least once.)ruletext";
extern const char RULE_TEXT_0_1_11[] = R"ruletext(There shall be no unused parameters (named or unnamed) in non-virtual functions.)ruletext";
extern const char RULE_TEXT_0_1_12[] = R"ruletext(There shall be no unused parameters (named or unnamed) in the set of parameters for a virtual function and all the functions that override it.)ruletext";

// Storage
extern const char RULE_TEXT_0_2_1[] = R"ruletext(An object shall not be assigned to an overlapping object.)ruletext";

// Runtime failures
extern const char RULE_TEXT_0_3_1[] = R"ruletext(Minimization of run-time failures shall be ensured by the use of at least one of: (a) static analysis tools/techniques; (b) dynamic analysis tools/techniques; (c) explicit coding of checks to handle run-time faults.)ruletext";
extern const char RULE_TEXT_0_3_2[] = R"ruletext(If a function generates error information, then that error information shall be tested.)ruletext";

// Arithmetic
extern const char RULE_TEXT_0_4_1[] = R"ruletext(Use of scaled-integer or fixed-point arithmetic shall be documented.)ruletext";
extern const char RULE_TEXT_0_4_2[] = R"ruletext(Use of floating-point arithmetic shall be documented.)ruletext";
extern const char RULE_TEXT_0_4_3[] = R"ruletext(Floating-point implementations shall comply with a defined floating-point standard.)ruletext";

// Language
extern const char RULE_TEXT_1_0_1[] = R"ruletext(All code shall conform to ISO/IEC 14882:2003 "The C++ Standard Incorporating Technical Corrigendum 1.)ruletext";
extern const char RULE_TEXT_1_0_2[] = R"ruletext(Multiple compilers shall only be used if they have a common, defined interface.)ruletext";
extern const char RULE_TEXT_1_0_3[] = R"ruletext(The implementation of integer division in the chosen compiler shall be determined and documented.)ruletext";

// Character sets
extern const char RULE_TEXT_2_2_1[] = R"ruletext(The character set and the corresponding encoding shall be documented.)ruletext";

// Trigraph sequences
extern const char RULE_TEXT_2_3_1[] = R"ruletext(Trigraphs shall not be used.)ruletext";

// Alternative tokens
extern const char RULE_TEXT_2_5_1[] = R"ruletext(Digraphs should not be used.)ruletext";

// Comments
extern const char RULE_TEXT_2_7_1[] = R"ruletext(The character sequence /* shall not be used within a C-style comment.)ruletext";
extern const char RULE_TEXT_2_7_2[] = R"ruletext(Sections of code shall not be "commented out" using C-style comments.)ruletext";
extern const char RULE_TEXT_2_7_3[] = R"ruletext(Sections of code should not be "commented out" using C++ comments.)ruletext";

// Identifiers
extern const char RULE_TEXT_2_10_1[] = R"ruletext(Different identifiers shall be typographically unambiguous.)ruletext";
extern const char RULE_TEXT_2_10_2[] = R"ruletext(Identifiers declared in an inner scope shall not hide an identifier declared in an outer scope.)ruletext";
extern const char RULE_TEXT_2_10_3[] = R"ruletext(A typedef name (including qualification, if any) shall be a unique identifier.)ruletext";
extern const char RULE_TEXT_2_10_4[] = R"ruletext(A class, union or enum name (including qualification, if any) shall be a unique identifier.)ruletext";
extern const char RULE_TEXT_2_10_5[] = R"ruletext(The identifier name of a non-member object or function with static storage duration should not be reused.)ruletext";
extern const char RULE_TEXT_2_10_6[] = R"ruletext(If an identifier refers to a type, it shall not also refer to an object or a function in the same scope.)ruletext";

// Literals
extern const char RULE_TEXT_2_13_1[] = R"ruletext(Only those escape sequences that are defined in ISO/IEC 14882:2003 shall be used.)ruletext";
extern const char RULE_TEXT_2_13_2[] = R"ruletext(Octal constants (other than zero) and octal escape sequences (other than "\0") shall not be used.)ruletext";
extern const char RULE_TEXT_2_13_3[] = R"ruletext(A "U " suffix shall be applied to all octal or hexadecimal integer literals of unsigned type.)ruletext";
extern const char RULE_TEXT_2_13_4[] = R"ruletext(Literal suffixes shall be upper case.)ruletext";
extern const char RULE_TEXT_2_13_5[] = R"ruletext(Narrow and wide string literals shall not be concatenated.)ruletext";

// Declarations and definitions
extern const char RULE_TEXT_3_1_1[] = R"ruletext(It shall be possible to include any header file in multiple translation units without violating the One Definition Rule.)ruletext";
extern const char RULE_TEXT_3_1_2[] = R"ruletext(Functions shall not be declared at block scope.)ruletext";
extern const char RULE_TEXT_3_1_3[] = R"ruletext(When an array is declared, its size shall either be stated explicitly or defined implicitly by initialization.)ruletext";

// One Definition Rule
extern const char RULE_TEXT_3_2_1[] = R"ruletext(All declarations of an object or function shall have compatible types.)ruletext";
extern const char RULE_TEXT_3_2_2[] = R"ruletext(The One Definition Rule shall not be violated.)ruletext";
extern const char RULE_TEXT_3_2_3[] = R"ruletext(A type, object or function that is used in multiple translation units shall be declared in one and only one file.)ruletext";
extern const char RULE_TEXT_3_2_4[] = R"ruletext(An identifier with external linkage shall have exactly one definition.)ruletext";

// Declarative regions and scope
extern const char RULE_TEXT_3_3_1[] = R"ruletext(Objects or functions with external linkage shall be declared in a header file.)ruletext";
extern const char RULE_TEXT_3_3_2[] = R"ruletext(If a function has internal linkage then all re-declarations shall include the static storage class specifier.)ruletext";

// Name lookup
extern const char RULE_TEXT_3_4_1[] = R"ruletext(An identifier declared to be an object or type shall be defined in a block that minimizes its visibility.)ruletext";

// Types
extern const char RULE_TEXT_3_9_1[] = R"ruletext(If a function has internal linkage then all re-declarations shall include the static storage class specifier.)ruletext";
extern const char RULE_TEXT_3_9_2[] = R"ruletext(typedefs that indicate size and signedness should be used in place of the basic numerical types.)ruletext";
extern const char RULE_TEXT_3_9_3[] = R"ruletext(The underlying bit representations of floating-point values shall not be used.)ruletext";

// Integral promotions
extern const char RULE_TEXT_4_5_1[] = R"ruletext(Expressions with type bool shall not be used as operands to built-in operators other than the assignment operator = , the logical operators && , || , ! , the equality operators == and != , the unary & operator, and the conditional operator.)ruletext";
extern const char RULE_TEXT_4_5_2[] = R"ruletext(Expressions with type enum shall not be used as operands to built-in operators other than the subscript operator [ ] , the assignment operator = , the equality operators == and != , the unary & operator, and the relational operators < , <= , > , >= .)ruletext";
extern const char RULE_TEXT_4_5_3[] = R"ruletext(Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator.)ruletext";

// Pointer conversions
extern const char RULE_TEXT_4_10_1[] = R"ruletext(NULL shall not be used as an integer value.)ruletext";
extern const char RULE_TEXT_4_10_2[] = R"ruletext(Literal zero (0) shall not be used as the null-pointer-constant.)ruletext";

// Expressions
extern const char RULE_TEXT_5_0_1[] = R"ruletext(The value of an expression shall be the same under any order of evaluation that the standard permits.)ruletext";
extern const char RULE_TEXT_5_0_2[] = R"ruletext(Limited dependence should be placed on C++ operator precedence rules in expressions.)ruletext";
extern const char RULE_TEXT_5_0_3[] = R"ruletext(A cvalue expression shall not be implicitly converted to a different underlying type.)ruletext";
extern const char RULE_TEXT_5_0_4[] = R"ruletext(An implicit integral conversion shall not change the signedness of the underlying type.)ruletext";
extern const char RULE_TEXT_5_0_5[] = R"ruletext(There shall be no implicit floating-integral conversions.)ruletext";
extern const char RULE_TEXT_5_0_6[] = R"ruletext(An implicit integral or floating-point conversion shall not reduce the size of the underlying type.)ruletext";
extern const char RULE_TEXT_5_0_7[] = R"ruletext(There shall be no explicit floating-integral conversions of a cvalue expression.)ruletext";
extern const char RULE_TEXT_5_0_8[] = R"ruletext(An explicit integral or floating-point conversion shall not increase the size of the underlying type of a cvalue expression.)ruletext";
extern const char RULE_TEXT_5_0_9[] = R"ruletext(An explicit integral conversion shall not change the signedness of the underlying type of a cvalue expression.)ruletext";
extern const char RULE_TEXT_5_0_10[] = R"ruletext(If the bitwise operators ~ and << are applied to an operand with an underlying type of unsigned char or unsigned short, the result shall be immediately cast to the underlying type of the operand.)ruletext";
extern const char RULE_TEXT_5_0_11[] = R"ruletext(The plain char type shall only be used for the storage and use of character values.)ruletext";
extern const char RULE_TEXT_5_0_12[] = R"ruletext(signed char and unsigned char type shall only be used for the storage and use of numeric values.)ruletext";
extern const char RULE_TEXT_5_0_13[] = R"ruletext(The condition of an if-statement and the condition of an iteration-statement shall have type bool.)ruletext";
extern const char RULE_TEXT_5_0_14[] = R"ruletext(The first operand of a conditional-operator shall have type bool.)ruletext";
extern const char RULE_TEXT_5_0_15[] = R"ruletext(Array indexing shall be the only form of pointer arithmetic.)ruletext";
extern const char RULE_TEXT_5_0_16[] = R"ruletext(A pointer operand and any pointer resulting from pointer arithmetic using that operand shall both address elements of the same array.)ruletext";
extern const char RULE_TEXT_5_0_17[] = R"ruletext(Subtraction between pointers shall only be applied to pointers that address elements of the same array.)ruletext";
extern const char RULE_TEXT_5_0_18[] = R"ruletext(> , >= , < , <= shall not be applied to objects of pointer type, except where they point to the same array.)ruletext";
extern const char RULE_TEXT_5_0_19[] = R"ruletext(The declaration of objects shall contain no more than two levels of pointer indirection.)ruletext";
extern const char RULE_TEXT_5_0_20[] = R"ruletext(Non-constant operands to a binary bitwise operator shall have the same underlying type.)ruletext";
extern const char RULE_TEXT_5_0_21[] = R"ruletext(Bitwise operators shall only be applied to operands of unsigned underlying type.)ruletext";

// Postfix expressions
extern const char RULE_TEXT_5_2_1[] = R"ruletext(Each operand of a logical && or || shall be a postfix‐expression.)ruletext";
extern const char RULE_TEXT_5_2_2[] = R"ruletext(A pointer to a virtual base class shall only be cast to a pointer to a derived class by means of dynamic_cast.)ruletext";
extern const char RULE_TEXT_5_2_3[] = R"ruletext(Casts from a base class to a derived class should not be performed on polymorphic types.)ruletext";
extern const char RULE_TEXT_5_2_4[] = R"ruletext(C-style casts (other than void casts) and functional notation casts (other than explicit constructor calls) shall not be used.)ruletext";
extern const char RULE_TEXT_5_2_5[] = R"ruletext(A cast shall not remove any const or volatile qualification from the type of a pointer or reference.)ruletext";
extern const char RULE_TEXT_5_2_6[] = R"ruletext(A cast shall not convert a pointer to a function to any other pointer type, including a pointer to function type.)ruletext";
extern const char RULE_TEXT_5_2_7[] = R"ruletext(An object with pointer type shall not be converted to an unrelated pointer type, either directly or indirectly.)ruletext";
extern const char RULE_TEXT_5_2_8[] = R"ruletext(An object with integer type or pointer to void type shall not be converted to an object with pointer type.)ruletext";
extern const char RULE_TEXT_5_2_9[] = R"ruletext(A cast should not convert a pointer type to an integral type.)ruletext";
extern const char RULE_TEXT_5_2_10[] = R"ruletext(The increment ( ++ ) and decrement ( -- ) operators should not be mixed with other operators in an expression.)ruletext";
extern const char RULE_TEXT_5_2_11[] = R"ruletext(The comma operator, && operator and the || operator shall not be overloaded.)ruletext";
extern const char RULE_TEXT_5_2_12[] = R"ruletext(An identifier with array type passed as a function argument shall not decay to a pointer.)ruletext";

// Unary expressions
extern const char RULE_TEXT_5_3_1[] = R"ruletext(Each operand of the ! operator, the logical && or the logical || operators shall have type bool.)ruletext";
extern const char RULE_TEXT_5_3_2[] = R"ruletext(The unary minus operator shall not be applied to an expression whose underlying type is unsigned.)ruletext";
extern const char RULE_TEXT_5_3_3[] = R"ruletext(The unary & operator shall not be overloaded.)ruletext";
extern const char RULE_TEXT_5_3_4[] = R"ruletext(Evaluation of the operand to the sizeof operator shall not contain side effects.)ruletext";

// Shift operators
extern const char RULE_TEXT_5_8_1[] = R"ruletext(The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand.)ruletext";

// Logical AND operator
extern const char RULE_TEXT_5_14_1[] = R"ruletext(The right hand operand of a logical && or || operator shall not contain side effects.)ruletext";

// Assignment operators
extern const char RULE_TEXT_5_17_1[] = R"ruletext(The semantic equivalence between a binary operator and its assignment operator form shall be preserved.)ruletext";

// Comma operator
extern const char RULE_TEXT_5_18_1[] = R"ruletext(The comma operator shall not be used.)ruletext";

// Constant expressions
extern const char RULE_TEXT_5_19_1[] = R"ruletext(Evaluation of constant unsigned integer expressions should not lead to wrap-around.)ruletext";

// Expression statement
extern const char RULE_TEXT_6_2_1[] = R"ruletext(Assignment operators shall not be used in sub-expressions.)ruletext";
extern const char RULE_TEXT_6_2_2[] = R"ruletext(Floating-point expressions shall not be directly or indirectly tested for equality or inequality.)ruletext";
extern const char RULE_TEXT_6_2_3[] = R"ruletext(Before preprocessing, a null statement shall only occur on a line by itself; it may be followed by a comment, provided that the first character following the null statement is a white‐space character.)ruletext";

// Compound statement
extern const char RULE_TEXT_6_3_1[] = R"ruletext(The statement forming the body of a switch, while, do ... while or for statement shall be a compound statement.)ruletext";

// Selection statements
extern const char RULE_TEXT_6_4_1[] = R"ruletext(An if ( condition ) construct shall be followed by a compound statement. The else keyword shall be followed by either a compound statement, or another if statement.)ruletext";
extern const char RULE_TEXT_6_4_2[] = R"ruletext(All if ... else if constructs shall be terminated with an else clause.)ruletext";
extern const char RULE_TEXT_6_4_3[] = R"ruletext(A switch statement shall be a well-formed switch statement.)ruletext";
extern const char RULE_TEXT_6_4_4[] = R"ruletext(A switch-label shall only be used when the most closely-enclosing compound statement is the body of a switch statement.)ruletext";
extern const char RULE_TEXT_6_4_5[] = R"ruletext(An unconditional throw or break statement shall terminate every non‐empty switch-clause.)ruletext";
extern const char RULE_TEXT_6_4_6[] = R"ruletext(The final clause of a switch statement shall be the default-clause.)ruletext";
extern const char RULE_TEXT_6_4_7[] = R"ruletext(The condition of a switch statement shall not have bool type.)ruletext";
extern const char RULE_TEXT_6_4_8[] = R"ruletext(Every switch statement shall have at least one case-clause.)ruletext";

// Iteration statements
extern const char RULE_TEXT_6_5_1[] = R"ruletext(A for loop shall contain a single loop-counter which shall not have floating type.)ruletext";
extern const char RULE_TEXT_6_5_2[] = R"ruletext(If loop-counter is not modified by -- or ++ , then, within condition, the loop-counter shall only be used as an operand to <= , < , > or >= .)ruletext";
extern const char RULE_TEXT_6_5_3[] = R"ruletext(The loop-counter shall not be modified within condition or statement.)ruletext";
extern const char RULE_TEXT_6_5_4[] = R"ruletext(The loop-counter shall be modified by one of: -- , ++ , -=n , or +=n ; where n remains constant for the duration of the loop.)ruletext";
extern const char RULE_TEXT_6_5_5[] = R"ruletext(A loop-control-variable other than the loop-counter shall not be modified within condition or expression.)ruletext";
extern const char RULE_TEXT_6_5_6[] = R"ruletext(A loop-control-variable other than the loop-counter which is modified in statement shall have type bool.)ruletext";

// Jump statements
extern const char RULE_TEXT_6_6_1[] = R"ruletext(Any label referenced by a goto statement shall be declared in the same block, or in a block enclosing the goto statement.)ruletext";
extern const char RULE_TEXT_6_6_2[] = R"ruletext(The goto statement shall jump to a label declared later in the same function body.)ruletext";
extern const char RULE_TEXT_6_6_3[] = R"ruletext(The continue statement shall only be used within a well-formed for loop.)ruletext";
extern const char RULE_TEXT_6_6_4[] = R"ruletext(For any iteration statement there shall be no more than one break or goto statement used for loop termination.)ruletext";
extern const char RULE_TEXT_6_6_5[] = R"ruletext(A function shall have a single point of exit at the end of the function.)ruletext";

// Specifiers
extern const char RULE_TEXT_7_1_1[] = R"ruletext(A variable which is not modified shall be const qualified.)ruletext";
extern const char RULE_TEXT_7_1_2[] = R"ruletext(A pointer or reference parameter in a function shall be declared as pointer to const or reference to const if the corresponding object is not modified.)ruletext";

// Enumeration declarations
extern const char RULE_TEXT_7_2_1[] = R"ruletext(An expression with enum underlying type shall only have values corresponding to the enumerators of the enumeration.)ruletext";

// Namespaces
extern const char RULE_TEXT_7_3_1[] = R"ruletext(The global namespace shall only contain main, namespace declarations and extern "C" declarations.)ruletext";
extern const char RULE_TEXT_7_3_2[] = R"ruletext(The identifier main shall not be used for a function other than the global function main.)ruletext";
extern const char RULE_TEXT_7_3_3[] = R"ruletext(There shall be no unnamed namespaces in header files.)ruletext";
extern const char RULE_TEXT_7_3_4[] = R"ruletext(using-directives shall not be used.)ruletext";
extern const char RULE_TEXT_7_3_5[] = R"ruletext(Multiple declarations for an identifier in the same namespace shall not straddle a using-declaration for that identifier.)ruletext";
extern const char RULE_TEXT_7_3_6[] = R"ruletext(using-directives and using-declarations (excluding class scope or function scope using-declarations) shall not be used in header files.)ruletext";

// The asm declaration
extern const char RULE_TEXT_7_4_1[] = R"ruletext(All usage of assembler shall be documented.)ruletext";
extern const char RULE_TEXT_7_4_2[] = R"ruletext(Assembler instructions shall only be introduced using the asm declaration.)ruletext";
extern const char RULE_TEXT_7_4_3[] = R"ruletext(Assembly language shall be encapsulated and isolated.)ruletext";

// Linkage specifications
extern const char RULE_TEXT_7_5_1[] = R"ruletext(A function shall not return a reference or a pointer to an automatic variable (including parameters), defined within the function.)ruletext";
extern const char RULE_TEXT_7_5_2[] = R"ruletext(The address of an object with automatic storage shall not be assigned to another object that may persist after the first object has ceased to exist.)ruletext";
extern const char RULE_TEXT_7_5_3[] = R"ruletext(A function shall not return a reference or a pointer to a parameter that is passed by reference or const reference.)ruletext";
extern const char RULE_TEXT_7_5_4[] = R"ruletext(Functions should not call themselves, either directly or indirectly.)ruletext";

// Declarators - General
extern const char RULE_TEXT_8_0_1[] = R"ruletext(An init-declarator-list or a member-declarator-list shall consist of a single init-declarator or member-declarator respectively.)ruletext";

// Meaning of declarators
extern const char RULE_TEXT_8_3_1[] = R"ruletext(Parameters in an overriding virtual function shall either use the same default arguments as the function they override, or else shall not specify any default arguments.)ruletext";

// Function definitions
extern const char RULE_TEXT_8_4_1[] = R"ruletext(Functions shall not be defined using the ellipsis notation.)ruletext";
extern const char RULE_TEXT_8_4_2[] = R"ruletext(The identifiers used for the parameters in a re-declaration of a function shall be identical to those in the declaration.)ruletext";
extern const char RULE_TEXT_8_4_3[] = R"ruletext(All exit paths from a function with non-void return type shall have an explicit return statement with an expression.)ruletext";
extern const char RULE_TEXT_8_4_4[] = R"ruletext(A function identifier shall either be used to call the function or it shall be preceded by & .)ruletext";

// Declarators - Initializers
extern const char RULE_TEXT_8_5_1[] = R"ruletext(All variables shall have a defined value before they are used.)ruletext";
extern const char RULE_TEXT_8_5_2[] = R"ruletext(Braces shall be used to indicate and match the structure in the non-zero initialization of arrays and structures.)ruletext";
extern const char RULE_TEXT_8_5_3[] = R"ruletext(In an enumerator list, the = construct shall not be used to explicitly initialize members other than the first, unless all items are explicitly initialized.)ruletext";

// Member functions
extern const char RULE_TEXT_9_3_1[] = R"ruletext(const member functions shall not return non-const pointers or references to class-data.)ruletext";
extern const char RULE_TEXT_9_3_2[] = R"ruletext(Member functions shall not return non-const handles to class-data.)ruletext";
extern const char RULE_TEXT_9_3_3[] = R"ruletext(If a member function can be made static then it shall be made static, otherwise if it can be made const then it shall be made const.)ruletext";

// Unions
extern const char RULE_TEXT_9_5_1[] = R"ruletext(Unions shall not be used.)ruletext";

// Bit-fields
extern const char RULE_TEXT_9_6_1[] = R"ruletext(When the absolute positioning of bits representing a bit-field is required, then the behaviour and packing of bit-fields shall be documented.)ruletext";
extern const char RULE_TEXT_9_6_2[] = R"ruletext(Bit-fields shall be either bool type or an explicitly unsigned or signed integral type.)ruletext";
extern const char RULE_TEXT_9_6_3[] = R"ruletext(Bit-fields shall not have enum type.)ruletext";
extern const char RULE_TEXT_9_6_4[] = R"ruletext(Named bit-fields with signed integer type shall have a length of more than one bit.)ruletext";

// Multiple base classes
extern const char RULE_TEXT_10_1_1[] = R"ruletext(Classes should not be derived from virtual bases.)ruletext";
extern const char RULE_TEXT_10_1_2[] = R"ruletext(A base class shall only be declared virtual if it is used in a diamond hierarchy.)ruletext";
extern const char RULE_TEXT_10_1_3[] = R"ruletext(An accessible base class shall not be both virtual and non-virtual in the same hierarchy.)ruletext";

// Member name lookup
extern const char RULE_TEXT_10_2_1[] = R"ruletext(All accessible entity names within a multiple inheritance hierarchy should be unique.)ruletext";

// Virtual functions
extern const char RULE_TEXT_10_3_1[] = R"ruletext(There shall be no more than one definition of each virtual function on each path through the inheritance hierarchy.)ruletext";
extern const char RULE_TEXT_10_3_2[] = R"ruletext(Each overriding virtual function shall be declared with the virtual keyword.)ruletext";
extern const char RULE_TEXT_10_3_3[] = R"ruletext(A virtual function shall only be overridden by a pure virtual function if it is itself declared as pure virtual.)ruletext";

// Member access control - General
extern const char RULE_TEXT_11_0_1[] = R"ruletext(Member data in non-POD class types shall be private.)ruletext";

// Constructors
extern const char RULE_TEXT_12_1_1[] = R"ruletext(An object’s dynamic type shall not be used from the body of its constructor or destructor.)ruletext";
extern const char RULE_TEXT_12_1_2[] = R"ruletext(All constructors of a class should explicitly call a constructor for all of its immediate base classes and all virtual base classes.)ruletext";
extern const char RULE_TEXT_12_1_3[] = R"ruletext(All constructors that are callable with a single argument of fundamental type shall be declared explicit.)ruletext";

// Copying class objects
extern const char RULE_TEXT_12_8_1[] = R"ruletext(A copy constructor shall only initialize its base classes and the non-static members of the class of which it is a member.)ruletext";
extern const char RULE_TEXT_12_8_2[] = R"ruletext(The copy assignment operator shall be declared protected or private in an abstract class.)ruletext";

// Template declarations
extern const char RULE_TEXT_14_5_1[] = R"ruletext(A non-member generic function shall only be declared in a namespace that is not an associated namespace.)ruletext";
extern const char RULE_TEXT_14_5_2[] = R"ruletext(A copy constructor shall be declared when there is a template constructor with a single parameter that is a generic parameter.)ruletext";
extern const char RULE_TEXT_14_5_3[] = R"ruletext(A copy assignment operator shall be declared when there is a template assignment operator with a parameter that is a generic parameter.)ruletext";

// Name resolution
extern const char RULE_TEXT_14_6_1[] = R"ruletext(In a class template with a dependent base, any name that may be found in that dependent base shall be referred to using a qualified-id or this->)ruletext";
extern const char RULE_TEXT_14_6_2[] = R"ruletext(The function chosen by overload resolution shall resolve to a function declared previously in the translation unit.)ruletext";

// Template instantiation and specialization
extern const char RULE_TEXT_14_7_1[] = R"ruletext(All class templates, function templates, class template member functions and class template static members shall be instantiated at least once.)ruletext";
extern const char RULE_TEXT_14_7_2[] = R"ruletext(For any given template specialization, an explicit instantiation of the template with the template-arguments used in the specialization shall not render the program ill-formed.)ruletext";
extern const char RULE_TEXT_14_7_3[] = R"ruletext(All partial and explicit specializations for a template shall be declared in the same file as the declaration of their primary template.)ruletext";

// Function template specialization
extern const char RULE_TEXT_14_8_1[] = R"ruletext(Overloaded function templates shall not be explicitly specialized.)ruletext";
extern const char RULE_TEXT_14_8_2[] = R"ruletext(The viable function set for a function call should either contain no function specializations, or only contain function specializations.)ruletext";

// Exception handling - General
extern const char RULE_TEXT_15_0_1[] = R"ruletext(Exceptions shall only be used for error handling.)ruletext";
extern const char RULE_TEXT_15_0_2[] = R"ruletext(An exception object should not have pointer type.)ruletext";
extern const char RULE_TEXT_15_0_3[] = R"ruletext(Control shall not be transferred into a try or catch block using a goto or a switch statement.)ruletext";

// Throwing an exception
extern const char RULE_TEXT_15_1_1[] = R"ruletext(The assignment-expression of a throw statement shall not itself cause an exception to be thrown.)ruletext";
extern const char RULE_TEXT_15_1_2[] = R"ruletext(NULL shall not be thrown explicitly.)ruletext";
extern const char RULE_TEXT_15_1_3[] = R"ruletext(An empty throw ( throw; ) shall only be used in the compound-statement of a catch handler.)ruletext";

// Handling an exception
extern const char RULE_TEXT_15_3_1[] = R"ruletext(Exceptions shall be raised only after start-up and before termination of the program.)ruletext";
extern const char RULE_TEXT_15_3_2[] = R"ruletext(There should be at least one exception handler to catch all otherwise unhandled exceptions)ruletext";
extern const char RULE_TEXT_15_3_3[] = R"ruletext(Handlers of a function-try-block implementation of a class constructor or destructor shall not reference non-static members from this class or its bases.)ruletext";
extern const char RULE_TEXT_15_3_4[] = R"ruletext(Each exception explicitly thrown in the code shall have a handler of a compatible type in all call paths that could lead to that point.)ruletext";
extern const char RULE_TEXT_15_3_5[] = R"ruletext(A class type exception shall always be caught by reference.)ruletext";
extern const char RULE_TEXT_15_3_6[] = R"ruletext(Where multiple handlers are provided in a single try-catch statement or function-try-block for a derived class and some or all of its bases, the handlers shall be ordered most-derived to base class.)ruletext";
extern const char RULE_TEXT_15_3_7[] = R"ruletext(Where multiple handlers are provided in a single try-catch statement or function-try-block, any ellipsis (catch-all) handler shall occur last.)ruletext";

// Exception specifications
extern const char RULE_TEXT_15_4_1[] = R"ruletext(If a function is declared with an exception-specification, then all declarations of the same function (in other translation units) shall be declared with the same set of type-ids.)ruletext";

// Exception handling - Special functions
extern const char RULE_TEXT_15_5_1[] = R"ruletext(A class destructor shall not exit with an exception.)ruletext";
extern const char RULE_TEXT_15_5_2[] = R"ruletext(Where a function’s declaration includes an exception-specification, the function shall only be capable of throwing exceptions of the indicated type(s).)ruletext";
extern const char RULE_TEXT_15_5_3[] = R"ruletext(The terminate() function shall not be called implicitly.)ruletext";

// Preprocessing directives - General
extern const char RULE_TEXT_16_0_1[] = R"ruletext(#include directives in a file shall only be preceded by other preprocessor directives or comments.)ruletext";
extern const char RULE_TEXT_16_0_2[] = R"ruletext(Macros shall only be #define’d or #undef’d in the global namespace.)ruletext";
extern const char RULE_TEXT_16_0_3[] = R"ruletext(#undef shall not be used.)ruletext";
extern const char RULE_TEXT_16_0_4[] = R"ruletext(Function-like macros shall not be defined.)ruletext";
extern const char RULE_TEXT_16_0_5[] = R"ruletext(Arguments to a function-like macro shall not contain tokens that look like preprocessing directives.)ruletext";
extern const char RULE_TEXT_16_0_6[] = R"ruletext(In the definition of a function-like macro, each instance of a parameter shall be enclosed in parentheses, unless it is used as the operand of # or ## .)ruletext";
extern const char RULE_TEXT_16_0_7[] = R"ruletext(Undefined macro identifiers shall not be used in #if or #elif preprocessor directives, except as operands to the defined operator.)ruletext";
extern const char RULE_TEXT_16_0_8[] = R"ruletext(If the # token appears as the first token on a line, then it shall be immediately followed by a preprocessing token.)ruletext";

// Conditional inclusion
extern const char RULE_TEXT_16_1_1[] = R"ruletext(The defined preprocessor operator shall only be used in one of the two standard forms.)ruletext";
extern const char RULE_TEXT_16_1_2[] = R"ruletext(All #else, #elif and #endif preprocessor directives shall reside in the same file as the #if or #ifdef directive to which they are related.)ruletext";

// Source file inclusion
extern const char RULE_TEXT_16_2_1[] = R"ruletext(The pre-processor shall only be used for file inclusion and include guards.)ruletext";
extern const char RULE_TEXT_16_2_2[] = R"ruletext(C++ macros shall only be used for: include guards, type qualifiers, or storage class specifiers.)ruletext";
extern const char RULE_TEXT_16_2_3[] = R"ruletext(Include guards shall be provided.)ruletext";
extern const char RULE_TEXT_16_2_4[] = R"ruletext(The ' , " , /* or // characters shall not occur in a header file name.)ruletext";
extern const char RULE_TEXT_16_2_5[] = R"ruletext(The \ character should not occur in a header file name.)ruletext";
extern const char RULE_TEXT_16_2_6[] = R"ruletext(The #include directive shall be followed by either a <filename> or "filename" sequence.)ruletext";

// Macro replacement
extern const char RULE_TEXT_16_3_1[] = R"ruletext(There shall be at most one occurrence of the # or ## operators in a single macro definition.)ruletext";
extern const char RULE_TEXT_16_3_2[] = R"ruletext(The # and ## operators should not be used.)ruletext";

// Pragma directive
extern const char RULE_TEXT_16_6_1[] = R"ruletext(All uses of the #pragma directive shall be documented.)ruletext";

// Library introduction - General
extern const char RULE_TEXT_17_0_1[] = R"ruletext(Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined.)ruletext";
extern const char RULE_TEXT_17_0_2[] = R"ruletext(The names of standard library macros and objects shall not be reused.)ruletext";
extern const char RULE_TEXT_17_0_3[] = R"ruletext(The names of standard library functions shall not be overridden.)ruletext";
extern const char RULE_TEXT_17_0_4[] = R"ruletext(All library code shall conform to MISRA C++.)ruletext";
extern const char RULE_TEXT_17_0_5[] = R"ruletext(The setjmp macro and the longjmp function shall not be used.61)ruletext";

// Language support library - General
extern const char RULE_TEXT_18_0_1[] = R"ruletext(The C library shall not be used.)ruletext";
extern const char RULE_TEXT_18_0_2[] = R"ruletext(The library functions atof, atoi and atol from library <cstdlib> shall not be used.)ruletext";
extern const char RULE_TEXT_18_0_3[] = R"ruletext(The library functions abort, exit, getenv and system from library <cstdlib> shall not be used.)ruletext";
extern const char RULE_TEXT_18_0_4[] = R"ruletext(The time handling functions of library <ctime> shall not be used.)ruletext";
extern const char RULE_TEXT_18_0_5[] = R"ruletext(The unbounded functions of library <cstring> shall not be used.)ruletext";

// Language support library - Implementation properties
extern const char RULE_TEXT_18_2_1[] = R"ruletext(The macro offsetof shall not be used.)ruletext";

// Language support library - Dynamic memory management
extern const char RULE_TEXT_18_4_1[] = R"ruletext(Dynamic heap memory allocation shall not be used.)ruletext";

// Language support library - Other runtime support
extern const char RULE_TEXT_18_7_1[] = R"ruletext(The signal handling facilities of <csignal> shall not be used.)ruletext";

// Diagnostics library - Error numbers
extern const char RULE_TEXT_19_3_1[] = R"ruletext(The error indicator errno shall not be used.)ruletext";

// Input/output library - General
extern const char RULE_TEXT_27_0_1[] = R"ruletext(The stream input/output library <cstdio> shall not be used.)ruletext";


// Assertions to make sure the array sizes and the string lengths match exactly
static_assert( sizeof(RULE_TEXT_0_1_1) == strlen(RULE_TEXT_0_1_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_0_1_2) == strlen(RULE_TEXT_0_1_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_0_1_3) == strlen(RULE_TEXT_0_1_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_0_1_4) == strlen(RULE_TEXT_0_1_4) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_0_1_5) == strlen(RULE_TEXT_0_1_5) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_0_1_6) == strlen(RULE_TEXT_0_1_6) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_0_1_7) == strlen(RULE_TEXT_0_1_7) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_0_1_8) == strlen(RULE_TEXT_0_1_8) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_0_1_9) == strlen(RULE_TEXT_0_1_9) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_0_1_10) == strlen(RULE_TEXT_0_1_10) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_0_1_11) == strlen(RULE_TEXT_0_1_11) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_0_1_12) == strlen(RULE_TEXT_0_1_12) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_0_2_1) == strlen(RULE_TEXT_0_2_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_0_3_1) == strlen(RULE_TEXT_0_3_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_0_3_2) == strlen(RULE_TEXT_0_3_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_0_4_1) == strlen(RULE_TEXT_0_4_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_0_4_2) == strlen(RULE_TEXT_0_4_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_0_4_3) == strlen(RULE_TEXT_0_4_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_1_0_1) == strlen(RULE_TEXT_1_0_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_1_0_2) == strlen(RULE_TEXT_1_0_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_1_0_3) == strlen(RULE_TEXT_1_0_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_2_2_1) == strlen(RULE_TEXT_2_2_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_2_3_1) == strlen(RULE_TEXT_2_3_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_2_5_1) == strlen(RULE_TEXT_2_5_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_2_7_1) == strlen(RULE_TEXT_2_7_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_2_7_2) == strlen(RULE_TEXT_2_7_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_2_7_3) == strlen(RULE_TEXT_2_7_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_2_10_1) == strlen(RULE_TEXT_2_10_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_2_10_2) == strlen(RULE_TEXT_2_10_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_2_10_3) == strlen(RULE_TEXT_2_10_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_2_10_4) == strlen(RULE_TEXT_2_10_4) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_2_10_5) == strlen(RULE_TEXT_2_10_5) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_2_10_6) == strlen(RULE_TEXT_2_10_6) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_2_13_1) == strlen(RULE_TEXT_2_13_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_2_13_2) == strlen(RULE_TEXT_2_13_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_2_13_3) == strlen(RULE_TEXT_2_13_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_2_13_4) == strlen(RULE_TEXT_2_13_4) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_2_13_5) == strlen(RULE_TEXT_2_13_5) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_3_1_1) == strlen(RULE_TEXT_3_1_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_3_1_2) == strlen(RULE_TEXT_3_1_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_3_1_3) == strlen(RULE_TEXT_3_1_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_3_2_1) == strlen(RULE_TEXT_3_2_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_3_2_2) == strlen(RULE_TEXT_3_2_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_3_2_3) == strlen(RULE_TEXT_3_2_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_3_2_4) == strlen(RULE_TEXT_3_2_4) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_3_3_1) == strlen(RULE_TEXT_3_3_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_3_3_2) == strlen(RULE_TEXT_3_3_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_3_4_1) == strlen(RULE_TEXT_3_4_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_3_9_1) == strlen(RULE_TEXT_3_9_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_3_9_2) == strlen(RULE_TEXT_3_9_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_3_9_3) == strlen(RULE_TEXT_3_9_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_4_5_1) == strlen(RULE_TEXT_4_5_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_4_5_2) == strlen(RULE_TEXT_4_5_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_4_5_3) == strlen(RULE_TEXT_4_5_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_4_10_1) == strlen(RULE_TEXT_4_10_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_4_10_2) == strlen(RULE_TEXT_4_10_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_1) == strlen(RULE_TEXT_5_0_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_2) == strlen(RULE_TEXT_5_0_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_3) == strlen(RULE_TEXT_5_0_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_4) == strlen(RULE_TEXT_5_0_4) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_5) == strlen(RULE_TEXT_5_0_5) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_6) == strlen(RULE_TEXT_5_0_6) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_7) == strlen(RULE_TEXT_5_0_7) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_8) == strlen(RULE_TEXT_5_0_8) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_9) == strlen(RULE_TEXT_5_0_9) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_10) == strlen(RULE_TEXT_5_0_10) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_11) == strlen(RULE_TEXT_5_0_11) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_12) == strlen(RULE_TEXT_5_0_12) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_13) == strlen(RULE_TEXT_5_0_13) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_14) == strlen(RULE_TEXT_5_0_14) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_15) == strlen(RULE_TEXT_5_0_15) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_16) == strlen(RULE_TEXT_5_0_16) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_17) == strlen(RULE_TEXT_5_0_17) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_18) == strlen(RULE_TEXT_5_0_18) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_19) == strlen(RULE_TEXT_5_0_19) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_20) == strlen(RULE_TEXT_5_0_20) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_0_21) == strlen(RULE_TEXT_5_0_21) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_2_1) == strlen(RULE_TEXT_5_2_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_2_2) == strlen(RULE_TEXT_5_2_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_2_3) == strlen(RULE_TEXT_5_2_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_2_4) == strlen(RULE_TEXT_5_2_4) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_2_5) == strlen(RULE_TEXT_5_2_5) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_2_6) == strlen(RULE_TEXT_5_2_6) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_2_7) == strlen(RULE_TEXT_5_2_7) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_2_8) == strlen(RULE_TEXT_5_2_8) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_2_9) == strlen(RULE_TEXT_5_2_9) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_2_10) == strlen(RULE_TEXT_5_2_10) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_2_11) == strlen(RULE_TEXT_5_2_11) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_2_12) == strlen(RULE_TEXT_5_2_12) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_3_1) == strlen(RULE_TEXT_5_3_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_3_2) == strlen(RULE_TEXT_5_3_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_3_3) == strlen(RULE_TEXT_5_3_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_3_4) == strlen(RULE_TEXT_5_3_4) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_8_1) == strlen(RULE_TEXT_5_8_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_14_1) == strlen(RULE_TEXT_5_14_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_17_1) == strlen(RULE_TEXT_5_17_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_18_1) == strlen(RULE_TEXT_5_18_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_5_19_1) == strlen(RULE_TEXT_5_19_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_2_1) == strlen(RULE_TEXT_6_2_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_2_2) == strlen(RULE_TEXT_6_2_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_2_3) == strlen(RULE_TEXT_6_2_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_3_1) == strlen(RULE_TEXT_6_3_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_4_1) == strlen(RULE_TEXT_6_4_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_4_2) == strlen(RULE_TEXT_6_4_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_4_3) == strlen(RULE_TEXT_6_4_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_4_4) == strlen(RULE_TEXT_6_4_4) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_4_5) == strlen(RULE_TEXT_6_4_5) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_4_6) == strlen(RULE_TEXT_6_4_6) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_4_7) == strlen(RULE_TEXT_6_4_7) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_4_8) == strlen(RULE_TEXT_6_4_8) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_5_1) == strlen(RULE_TEXT_6_5_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_5_2) == strlen(RULE_TEXT_6_5_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_5_3) == strlen(RULE_TEXT_6_5_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_5_4) == strlen(RULE_TEXT_6_5_4) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_5_5) == strlen(RULE_TEXT_6_5_5) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_5_6) == strlen(RULE_TEXT_6_5_6) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_6_1) == strlen(RULE_TEXT_6_6_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_6_2) == strlen(RULE_TEXT_6_6_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_6_3) == strlen(RULE_TEXT_6_6_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_6_4) == strlen(RULE_TEXT_6_6_4) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_6_6_5) == strlen(RULE_TEXT_6_6_5) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_7_1_1) == strlen(RULE_TEXT_7_1_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_7_1_2) == strlen(RULE_TEXT_7_1_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_7_2_1) == strlen(RULE_TEXT_7_2_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_7_3_1) == strlen(RULE_TEXT_7_3_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_7_3_2) == strlen(RULE_TEXT_7_3_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_7_3_3) == strlen(RULE_TEXT_7_3_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_7_3_4) == strlen(RULE_TEXT_7_3_4) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_7_3_5) == strlen(RULE_TEXT_7_3_5) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_7_3_6) == strlen(RULE_TEXT_7_3_6) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_7_4_1) == strlen(RULE_TEXT_7_4_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_7_4_2) == strlen(RULE_TEXT_7_4_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_7_4_3) == strlen(RULE_TEXT_7_4_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_7_5_1) == strlen(RULE_TEXT_7_5_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_7_5_2) == strlen(RULE_TEXT_7_5_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_7_5_3) == strlen(RULE_TEXT_7_5_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_7_5_4) == strlen(RULE_TEXT_7_5_4) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_8_0_1) == strlen(RULE_TEXT_8_0_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_8_3_1) == strlen(RULE_TEXT_8_3_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_8_4_1) == strlen(RULE_TEXT_8_4_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_8_4_2) == strlen(RULE_TEXT_8_4_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_8_4_3) == strlen(RULE_TEXT_8_4_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_8_4_4) == strlen(RULE_TEXT_8_4_4) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_8_5_1) == strlen(RULE_TEXT_8_5_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_8_5_2) == strlen(RULE_TEXT_8_5_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_8_5_3) == strlen(RULE_TEXT_8_5_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_9_3_1) == strlen(RULE_TEXT_9_3_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_9_3_2) == strlen(RULE_TEXT_9_3_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_9_3_3) == strlen(RULE_TEXT_9_3_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_9_5_1) == strlen(RULE_TEXT_9_5_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_9_6_1) == strlen(RULE_TEXT_9_6_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_9_6_2) == strlen(RULE_TEXT_9_6_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_9_6_3) == strlen(RULE_TEXT_9_6_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_9_6_4) == strlen(RULE_TEXT_9_6_4) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_10_1_1) == strlen(RULE_TEXT_10_1_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_10_1_2) == strlen(RULE_TEXT_10_1_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_10_1_3) == strlen(RULE_TEXT_10_1_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_10_2_1) == strlen(RULE_TEXT_10_2_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_10_3_1) == strlen(RULE_TEXT_10_3_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_10_3_2) == strlen(RULE_TEXT_10_3_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_10_3_3) == strlen(RULE_TEXT_10_3_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_11_0_1) == strlen(RULE_TEXT_11_0_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_12_1_1) == strlen(RULE_TEXT_12_1_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_12_1_2) == strlen(RULE_TEXT_12_1_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_12_1_3) == strlen(RULE_TEXT_12_1_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_12_8_1) == strlen(RULE_TEXT_12_8_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_12_8_2) == strlen(RULE_TEXT_12_8_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_14_5_1) == strlen(RULE_TEXT_14_5_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_14_5_2) == strlen(RULE_TEXT_14_5_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_14_5_3) == strlen(RULE_TEXT_14_5_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_14_6_1) == strlen(RULE_TEXT_14_6_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_14_6_2) == strlen(RULE_TEXT_14_6_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_14_7_1) == strlen(RULE_TEXT_14_7_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_14_7_2) == strlen(RULE_TEXT_14_7_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_14_7_3) == strlen(RULE_TEXT_14_7_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_14_8_1) == strlen(RULE_TEXT_14_8_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_14_8_2) == strlen(RULE_TEXT_14_8_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_15_0_1) == strlen(RULE_TEXT_15_0_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_15_0_2) == strlen(RULE_TEXT_15_0_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_15_0_3) == strlen(RULE_TEXT_15_0_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_15_1_1) == strlen(RULE_TEXT_15_1_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_15_1_2) == strlen(RULE_TEXT_15_1_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_15_1_3) == strlen(RULE_TEXT_15_1_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_15_3_1) == strlen(RULE_TEXT_15_3_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_15_3_2) == strlen(RULE_TEXT_15_3_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_15_3_3) == strlen(RULE_TEXT_15_3_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_15_3_4) == strlen(RULE_TEXT_15_3_4) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_15_3_5) == strlen(RULE_TEXT_15_3_5) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_15_3_6) == strlen(RULE_TEXT_15_3_6) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_15_3_7) == strlen(RULE_TEXT_15_3_7) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_15_4_1) == strlen(RULE_TEXT_15_4_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_15_5_1) == strlen(RULE_TEXT_15_5_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_15_5_2) == strlen(RULE_TEXT_15_5_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_15_5_3) == strlen(RULE_TEXT_15_5_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_16_0_1) == strlen(RULE_TEXT_16_0_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_16_0_2) == strlen(RULE_TEXT_16_0_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_16_0_3) == strlen(RULE_TEXT_16_0_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_16_0_4) == strlen(RULE_TEXT_16_0_4) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_16_0_5) == strlen(RULE_TEXT_16_0_5) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_16_0_6) == strlen(RULE_TEXT_16_0_6) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_16_0_7) == strlen(RULE_TEXT_16_0_7) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_16_0_8) == strlen(RULE_TEXT_16_0_8) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_16_1_1) == strlen(RULE_TEXT_16_1_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_16_1_2) == strlen(RULE_TEXT_16_1_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_16_2_1) == strlen(RULE_TEXT_16_2_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_16_2_2) == strlen(RULE_TEXT_16_2_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_16_2_3) == strlen(RULE_TEXT_16_2_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_16_2_4) == strlen(RULE_TEXT_16_2_4) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_16_2_5) == strlen(RULE_TEXT_16_2_5) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_16_2_6) == strlen(RULE_TEXT_16_2_6) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_16_3_1) == strlen(RULE_TEXT_16_3_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_16_3_2) == strlen(RULE_TEXT_16_3_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_16_6_1) == strlen(RULE_TEXT_16_6_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_17_0_1) == strlen(RULE_TEXT_17_0_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_17_0_2) == strlen(RULE_TEXT_17_0_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_17_0_3) == strlen(RULE_TEXT_17_0_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_17_0_4) == strlen(RULE_TEXT_17_0_4) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_17_0_5) == strlen(RULE_TEXT_17_0_5) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_18_0_1) == strlen(RULE_TEXT_18_0_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_18_0_2) == strlen(RULE_TEXT_18_0_2) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_18_0_3) == strlen(RULE_TEXT_18_0_3) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_18_0_4) == strlen(RULE_TEXT_18_0_4) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_18_0_5) == strlen(RULE_TEXT_18_0_5) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_18_2_1) == strlen(RULE_TEXT_18_2_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_18_4_1) == strlen(RULE_TEXT_18_4_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_18_7_1) == strlen(RULE_TEXT_18_7_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_19_3_1) == strlen(RULE_TEXT_19_3_1) + 1, "Array/stringlenth missmatch!");
static_assert( sizeof(RULE_TEXT_27_0_1) == strlen(RULE_TEXT_27_0_1) + 1, "Array/stringlenth missmatch!");

}
