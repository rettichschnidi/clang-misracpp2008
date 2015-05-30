//===-  Rule_4_5_1.cpp - Checker for MISRA C++ 2008 rule 4-5-1-------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/AST/OperationKinds.h"
#include <set>

using namespace clang;

namespace misracpp2008 {

class Rule_4_5_1 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_4_5_1> {
public:
  Rule_4_5_1() : RuleCheckerASTContext() {}

  bool VisitBinaryOperator(const BinaryOperator *O) {
    if (doIgnore(O->getLocStart())) {
      return true;
    }

    if (O->getLHS()->IgnoreCasts()->getType()->isBooleanType() &&
        O->getRHS()->IgnoreCasts()->getType()->isBooleanType() &&
        legalBinaryOperators.count(O->getOpcode()) == 0) {
      reportError(O->getLocStart());
    }

    return true;
  }

  bool VisitUnaryOperator(const UnaryOperator *O) {
    if (doIgnore(O->getLocStart())) {
      return true;
    }

    if (O->getSubExpr()->IgnoreCasts()->getType()->isBooleanType() &&
        legalUnaryOperators.count(O->getOpcode()) == 0) {
      reportError(O->getLocStart());
    }

    return true;
  }

private:
  std::set<UnaryOperator::Opcode> legalUnaryOperators = {clang::UO_LNot,
                                                         clang::UO_AddrOf};
  std::set<BinaryOperator::Opcode> legalBinaryOperators = {
      clang::BO_Assign, clang::BO_LAnd, clang::BO_LOr, clang::BO_EQ,
      clang::BO_NE};

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_4_5_1> X("4-5-1", "");
}
