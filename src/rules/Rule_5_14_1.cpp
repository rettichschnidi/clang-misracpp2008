//===-  Rule_5_14_1.cpp - Checker for MISRA C++ 2008 rule 5-14-1-----------===//
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

class Rule_5_14_1 : public RuleCheckerASTContext,
                    public RecursiveASTVisitor<Rule_5_14_1> {
public:
  Rule_5_14_1() : RuleCheckerASTContext() {}

  bool VisitBinLAnd(const BinaryOperator *S) {
    return rightHandOperatorHasSideEffect(S);
  }
  bool VisitBinLOr(const BinaryOperator *S) {
    return rightHandOperatorHasSideEffect(S);
  }

protected:
  bool rightHandOperatorHasSideEffect(const BinaryOperator *S) {
    if (doIgnore(S->getLocStart())) {
      return true;
    }

    Expr *rightHandExpr = S->getRHS();
    if (rightHandExpr->HasSideEffects(*context)) {
      reportError(rightHandExpr->getLocStart());
    }
    return true;
  }

  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_5_14_1> X("5-14-1", "");
}
