// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 11-0-1 %s

struct PodStruct {
  int defaultMember1;
  int defaultMember2;
};

class PodClass {
public:
  int publicMember1;
  int publicMember2;
};

class AllPrivateClass {
  int implicitPrivateMember;

private:
  int explicitPrivateMember;
};

struct NonPodStruct {
  int implicitPublicMember; // expected-error {{Member data in non-POD class types shall be private. (MISRA C++ 2008 rule 11-0-1)}}
public:
  int explicitPublicMember; // expected-error {{Member data in non-POD class types shall be private. (MISRA C++ 2008 rule 11-0-1)}}
protected:
  int explicitProtectedMember; // expected-error {{Member data in non-POD class types shall be private. (MISRA C++ 2008 rule 11-0-1)}}
private:
  int explicitPrivateMember;
};

class NotAllPrivateClass {
  int implicitPrivateMember;

private:
  int explicitPrivateMember;

protected:
  int protectedMember; // expected-error {{Member data in non-POD class types shall be private. (MISRA C++ 2008 rule 11-0-1)}}
public:
  int publicMember; // expected-error {{Member data in non-POD class types shall be private. (MISRA C++ 2008 rule 11-0-1)}}
};
