//===-  Rule_4_5_2.cpp - Checker for MISRA C++ 2008 rule 4-5-2-------------===//
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

// TODO:  4-5-* rules probably could share some code!
class Rule_4_5_2 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_4_5_2> {
public:
  Rule_4_5_2() : RuleCheckerASTContext() {}

  bool VisitBinaryOperator(const BinaryOperator *BO) {
    if (doIgnore(BO->getLocStart())) {
      return true;
    }

    if (BO->getLHS()->IgnoreImpCasts()->getType()->isEnumeralType() &&
        BO->getRHS()->IgnoreImpCasts()->getType()->isEnumeralType() &&
        legalBinaryOperators.count(BO->getOpcode()) == 0) {
      reportError(BO->getLocStart());
    }

    return true;
  }

  bool VisitUnaryOperator(const UnaryOperator *UO) {
    if (doIgnore(UO->getLocStart())) {
      return true;
    }

    if (UO->getSubExpr()->IgnoreImpCasts()->getType()->isEnumeralType() &&
        legalUnaryOperators.count(UO->getOpcode()) == 0) {
      reportError(UO->getLocStart());
    }

    return true;
  }

private:
  std::set<UnaryOperator::Opcode> legalUnaryOperators = {clang::UO_AddrOf};
  std::set<BinaryOperator::Opcode> legalBinaryOperators = {
      clang::BO_Assign, clang::BO_EQ, clang::BO_NE, clang::BO_LT,
      clang::BO_LE,     clang::BO_GT, clang::BO_GE};

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_4_5_2> X("4-5-2", "");
}
