//===-  Rule_6_2_2.cpp - Checker for MISRA C++ 2008 rule 6-2-2-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
// Copyright (C) 2014 Reto Schneider <code@reto-schneider.ch>
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang;

namespace misracpp2008 {

const static std::string ruleName = "6-2-2";

class Rule_6_2_2 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_6_2_2> {
public:
  Rule_6_2_2() : RuleCheckerASTContext() {}

  bool VisitBinEQ(BinaryOperator *S) {
    VisitBinEqOrNeHelper(S);
    return true;
  }
  bool VisitBinNE(BinaryOperator *S) {
    VisitBinEqOrNeHelper(S);
    return true;
  }

  bool VisitBinLAnd(BinaryOperator *S) {
    LAndAndLorHelper(S);
    return true;
  }
  bool VisitBinLOr(BinaryOperator *S) {
    LAndAndLorHelper(S);
    return true;
  }

private:
  void LAndAndLorHelper(BinaryOperator *S) {
    if (doIgnore(S->getLocStart())) {
      return;
    }
    if (isFloatingComparingExpr(S->getLHS()->IgnoreParenCasts()) &&
        isFloatingComparingExpr(S->getRHS()->IgnoreParenCasts())) {
      reportError(S);
    }
  }

  void VisitBinEqOrNeHelper(BinaryOperator *S) {
    if (doIgnore(S->getLocStart())) {
      return;
    }

    // Report one side only
    if (isFloatingType(S->getLHS())) {
      reportError(S->getLHS());
    } else if (isFloatingType(S->getRHS())) {
      reportError(S->getRHS());
    }
  }

  void reportError(const Expr *expr) {
    RuleCheckerASTContext::reportError(RULE_TEXT_6_2_2, expr->getLocStart());
  }

  bool isFloatingType(const Expr *expr) {
    if (expr->IgnoreParenCasts()->getType()->isFloatingType()) {
      return true;
    }
    return false;
  }

  bool isFloatingComparingExpr(Expr *S) {
    if (BinaryOperator *bo = dyn_cast<BinaryOperator>(S)) {
      if (isFloatingType(bo->getLHS()) || isFloatingType(bo->getRHS())) {
        return true;
      }
    }
    return false;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_6_2_2>
    X(ruleName.c_str(), "MISRA C++ 2008 rule checker");
}
