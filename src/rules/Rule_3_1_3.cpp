//===-  Rule_3_1_3.cpp - Checker for MISRA C++ 2008 rule 3-1-3-------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "misracpp2008.h"

using namespace clang;

namespace misracpp2008 {

class Rule_3_1_3 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_3_1_3> {
public:
  Rule_3_1_3() : RuleCheckerASTContext() {}

  bool VisitVarDecl(VarDecl *D) {
    if (doIgnore(D->getLocStart())) {
      return true;
    }

    // Bail out if the length of the array is known.
    if (isa<ConstantArrayType>(D->getType())) {
      return true;
    }

    reportError(D->getLocation());

    return true;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_3_1_3> X("3-1-3", "");
}
