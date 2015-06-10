//===-  Rule_12_8_2.cpp - Checker for MISRA C++ 2008 rule 12-8-2-----------===//
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

class Rule_12_8_2 : public RuleCheckerASTContext,
                    public RecursiveASTVisitor<Rule_12_8_2> {
public:
  Rule_12_8_2() : RuleCheckerASTContext() {}

  bool VisitCXXRecordDecl(CXXRecordDecl *decl) {
    if (doIgnore(decl->getLocStart())) {
      return true;
    }

    // If a class is not abstract skip it
    if (!decl->isAbstract()) {
      return true;
    }

    // If abstract class doesn't have user declared
    // operator= skip it
    if (!decl->hasUserDeclaredCopyAssignment()) {
      return true;
    }

    for (CXXMethodDecl *method : decl->methods()) {
      if (method->isCopyAssignmentOperator() &&
          method->getAccess() == clang::AS_public) {
        reportError(method->getLocStart());
      }
    }

    return true;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_12_8_2> X("12-8-2", "");
}
