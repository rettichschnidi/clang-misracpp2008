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
#include <algorithm>

using namespace clang;

namespace misracpp2008 {

class Rule_6_2_2 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_6_2_2> {
public:
  Rule_6_2_2() : RuleCheckerASTContext() {}

  bool VisitBinEQ(BinaryOperator *S) {
    reportViolationIfFloatSubexpr(S);
    return true;
  }
  bool VisitBinNE(BinaryOperator *S) {
    reportViolationIfFloatSubexpr(S);
    return true;
  }

  bool VisitBinLAnd(BinaryOperator *S) {
    FindObfuscatedViolation(S);
    return true;
  }
  bool VisitBinLOr(BinaryOperator *S) {
    FindObfuscatedViolation(S);
    return true;
  }

private:
  typedef std::set<DeclRefExpr *> DeclRefExprPtrSet;

  void FindObfuscatedViolation(BinaryOperator *S) {
    assert((S->getOpcode() == BO_LAnd || S->getOpcode() == BO_LOr) &&
           "This method only works on logical operators.");

    if (doIgnore(S->getLocStart())) {
      return;
    }

    BinaryOperator *lhs =
        dyn_cast<BinaryOperator>(S->getLHS()->IgnoreParenCasts());
    BinaryOperator *rhs =
        dyn_cast<BinaryOperator>(S->getRHS()->IgnoreParenCasts());
    // There must be binary operators on both sides
    if (lhs && isFloatingComparingBinOp(lhs) && rhs &&
        isFloatingComparingBinOp(rhs)) {
      const DeclRefExprPtrSet lhsChildren = getChildrenExpr(lhs);
      const DeclRefExprPtrSet rhsChildren = getChildrenExpr(rhs);

      // What did I miss? Is there really no equal operator for DeclRefExpr?
      auto isDeclRefEqualFunc = [](DeclRefExpr *a, DeclRefExpr *b) {
        return a->getDecl() == b->getDecl();
      };

      // Report error only when on the left and on the right side the same two
      // variables get compared
      if (std::equal(lhsChildren.begin(), lhsChildren.end(),
                     rhsChildren.begin(), isDeclRefEqualFunc)) {
        reportError(S->getLocStart());
      }
    }
  }

  void reportViolationIfFloatSubexpr(BinaryOperator *S) {
    assert((S->getOpcode() == BO_EQ || S->getOpcode() == BO_NE) &&
           "This method only works on (not) equal operators.");

    if (doIgnore(S->getLocStart())) {
      return;
    }

    // Issue at most one report
    if (isFloatingType(S->getLHS())) {
      reportError(S->getLHS()->getLocStart());
    } else if (isFloatingType(S->getRHS())) {
      reportError(S->getRHS()->getLocStart());
    }
  }

  bool isFloatingType(const Expr *expr) {
    if (expr->IgnoreParenCasts()->getType()->isFloatingType()) {
      return true;
    }
    return false;
  }

  bool isFloatingComparingBinOp(BinaryOperator *bo) {
    if (isFloatingType(bo->getLHS()) || isFloatingType(bo->getRHS())) {
      return true;
    }
    return false;
  }

  const DeclRefExprPtrSet getChildrenExpr(BinaryOperator *bo) {
    DeclRefExpr *lhs = dyn_cast<DeclRefExpr>(bo->getLHS()->IgnoreParenCasts());
    DeclRefExpr *rhs = dyn_cast<DeclRefExpr>(bo->getRHS()->IgnoreParenCasts());
    assert(lhs && "Left hand side is expected to be a DeclRefExpr!");
    assert(rhs && "Right hand side is expected to be a DeclRefExpr!");
    return DeclRefExprPtrSet({lhs, rhs});
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_6_2_2> X("6-2-2",
                                                        RULE_TEXT_6_2_2);
}
