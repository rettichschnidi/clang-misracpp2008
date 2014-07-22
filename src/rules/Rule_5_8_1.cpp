//===-  Rule_5_8_1.cpp - Checker for MISRA C++ 2008 rule 5-8-1-------------===//
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

const static std::string ruleName = "5-8-1";

class Rule_5_8_1 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_5_8_1> {
public:
  Rule_5_8_1() : RuleCheckerASTContext() {}
  bool VisitBinShl(const BinaryOperator *S) { return isShiftStatementValid(S); }
  bool VisitBinShr(const BinaryOperator *S) { return isShiftStatementValid(S); }
  bool VisitBinShrAssign(const CompoundAssignOperator *S) {
    return isShiftStatementValid(S);
  }
  bool VisitBinShlAssign(const CompoundAssignOperator *S) {
    return isShiftStatementValid(S);
  }

protected:
  bool isShiftStatementValid(const BinaryOperator *S) {
    const Expr *additiveExpr = S->getRHS();
    if (additiveExpr->isEvaluatable(*context)) {
      const llvm::APSInt bitsToShift =
          additiveExpr->EvaluateKnownConstInt(*context);
      const unsigned integerSize = getBitWidthOfInteger(S->getLHS());

      // Report an error if we can be sure (statically checked), that the number
      // of bits to shift is either negative or greater-equal than the bit-size
      // of the integer we are operating on.
      if (bitsToShift.isNegative() || bitsToShift.uge(integerSize)) {
        reportError(RULE_TEXT_5_8_1, S->getLocStart());
      }
    } else {
      // Shifting can not statically be verified - review or runtime test
      // needed!
    }
    return true;
  }

  unsigned getBitWidthOfInteger(const Expr *expr) {
    const QualType &qualifierType = expr->IgnoreImpCasts()->getType();
    assert(qualifierType->isIntegerType() &&
           "Shift operators have to work on integers!");
    return context->getIntWidth(qualifierType);
  }

  virtual void doWork() {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_5_8_1>
X(ruleName.c_str(), "MISRA C++ 2008 rule checker");
}
