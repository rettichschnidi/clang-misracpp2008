//===-  Rule_3_3_2.cpp - Checker for MISRA C++ 2008 rule 3-3-2-------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang;

namespace misracpp2008 {

class Rule_3_3_2 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_3_3_2> {
public:
  Rule_3_3_2() : RuleCheckerASTContext() {}

  bool VisitFunctionDecl(const FunctionDecl *D) {
    if (doIgnore(D->getLocStart())) {
      return true;
    }

    if ((D->getStorageClass() == SC_Static) &&
        (D->isCXXClassMember() == false)) {
      for (const auto RI : D->redecls()) {
        if (RI->getStorageClass() != SC_Static) {
          reportError(RI->getLocation());
          break;
        }
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

static RuleCheckerASTContextRegistry::Add<Rule_3_3_2> X("3-3-2", "");
}
