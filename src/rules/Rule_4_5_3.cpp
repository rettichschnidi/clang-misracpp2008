//===-  Rule_4_5_3.cpp - Checker for MISRA C++ 2008 rule 4-5-3-------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "misracpp2008.h"
#include <cctype>

using namespace clang;

namespace misracpp2008 {

// TODO:  4-5-* rules probably could share some code!
class Rule_4_5_3 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_4_5_3> {
public:
  Rule_4_5_3() : RuleCheckerASTContext() {}

  bool VisitBinaryOperator(const BinaryOperator *BO) {
    if (doIgnore(BO->getLocStart())) {
      return true;
    }

    // Bail out if neither of the operands is a plain character or if the
    // operator is explicitly whitelisted
    const Expr *exprLeft = BO->getLHS()->IgnoreImpCasts();
    const Expr *exprRight = BO->getRHS()->IgnoreImpCasts();
    const BinaryOperator::Opcode opCode = BO->getOpcode();
    if ((!isPlainCharType(exprLeft) && !isPlainCharType(exprRight)) ||
        legalBinaryOperators.count(opCode) > 0) {
      return true;
    }

    // First exception: Integers 0 to 9 can be added to '0'
    const CharacterLiteral *charLeft = dyn_cast<CharacterLiteral>(exprLeft);
    const CharacterLiteral *charRight = dyn_cast<CharacterLiteral>(exprRight);
    if (opCode == clang::BO_Add && charLeft && charLeft->getValue() == '0') {
      return true;
    }

    // Second exception: Character '0' can be used to subtract
    if (opCode == clang::BO_Sub && charRight && charRight->getValue() == '0') {
      return true;
    }

    // Third exception: Check if character is a digit
    if (opCode == clang::BO_LT || opCode == clang::BO_LE ||
        opCode == clang::BO_GT || opCode == clang::BO_GE) {
      if ((charRight && std::isdigit(charRight->getValue())) ||
          (charLeft && std::isdigit(charLeft->getValue()))) {
        return true;
      }
    }

    reportError(BO->getLocStart());

    return true;
  }

  bool VisitUnaryOperator(const UnaryOperator *UO) {
    if (doIgnore(UO->getLocStart())) {
      return true;
    }

    if (isPlainCharType(UO->getSubExpr()->IgnoreImpCasts()) &&
        legalUnaryOperators.count(UO->getOpcode()) == 0) {
      reportError(UO->getLocStart());
    }

    return true;
  }

private:
  const std::set<UnaryOperator::Opcode> legalUnaryOperators = {
      clang::UO_AddrOf};
  const std::set<BinaryOperator::Opcode> legalBinaryOperators = {
      clang::BO_Assign, clang::BO_EQ, clang::BO_NE};
  const std::set<std::string> plainCharTypeNames = {
      "char",     "unsigned char", "signed char", "char_t", "wchar_t",
      "char16_t", "char32_t",      "__wchar_t"}; ///< TODO: Is there a better
                                                 /// way to bann all the plain
                                                 /// char types?

  bool isPlainCharType(const Expr *expr) {
    const QualType t = expr->getType();

    if (!t->isAnyCharacterType()) {
      return false;
    }
    return plainCharTypeNames.find(t.getAsString()) != plainCharTypeNames.end();
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_4_5_3> X("4-5-3", "");
}
