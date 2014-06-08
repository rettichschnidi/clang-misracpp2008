//===-  Rule_10_3_2.cpp - Checker for MISRA C++ 2008 rule 10-3-2-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang;

namespace misracpp2008 {

const static std::string ruleName = "10-3-2";

class Rule_10_3_2 : public RuleCheckerASTContext,
                    public clang::RecursiveASTVisitor<Rule_10_3_2> {
public:
  Rule_10_3_2() : RuleCheckerASTContext() {}
  bool VisitCXXRecordDecl(CXXRecordDecl *decl) {
    if(isInSystemHeader(decl->getLocStart())) {
      return true;
    }

    CXXRecordDecl::method_iterator B = decl->method_begin();
    CXXRecordDecl::method_iterator E = decl->method_end();
    while (B != E) {
      if (!B->isImplicit() && B->isVirtual() && !B->isVirtualAsWritten()) {
        unsigned diagID = diagEngine->getCustomDiagID(
            diagLevel, "Each overriding virtual function shall be declared with"
                       " the virtual keyword.");
        SourceLocation location = B->getLocation();
        diagEngine->Report(location, diagID);
        break;
      }
      B++;
    }
    return true;
  }
  bool VisitCXXDestructorDecl(clang::CXXDestructorDecl *decl) {
      if (decl->isVirtual() && !decl->isVirtualAsWritten()) {
        unsigned diagID = diagEngine->getCustomDiagID(
            diagLevel, "Each overriding virtual function shall be declared with"
                       " the virtual keyword.");
        SourceLocation location = decl->getLocation();
        diagEngine->Report(location, diagID);
      }
    return true;
  }

  virtual ~Rule_10_3_2() {}

protected:
  virtual void doWork() {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_10_3_2>
X(ruleName.c_str(), "MISRA C++ 2008 rule checker");
}
