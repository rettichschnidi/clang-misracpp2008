//===-  Rule_4_10_2.cpp - Checker for MISRA C++ 2008 rule  4-10-2----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/OperationKinds.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang;

namespace misracpp2008 {

class Rule_4_10_2 : public RuleCheckerASTContext,
                    public RecursiveASTVisitor<Rule_4_10_2> {
public:
  Rule_4_10_2() : RuleCheckerASTContext() {}

  bool VisitCastExpr(const CastExpr *ce) {
    if (doIgnore(ce->getLocStart())) {
      return true;
    }

    // Bail out if this expression is neither a null-to-pointer nor a
    // null-to-member-pointer cast
    const CastKind castKind = ce->getCastKind();
    if (castKind != clang::CK_NullToPointer &&
        castKind != clang::CK_NullToMemberPointer) {
      return true;
    }

    // Report error if null-pointer-constant is based on a literal zero.
    if (const Expr *subExpr = ce->getSubExpr()->IgnoreImpCasts()) {
      if (subExpr->isNullPointerConstant(*this->context,
                                         Expr::NPC_NeverValueDependent) ==
          Expr::NPCK_ZeroLiteral) {
        reportError(ce->getLocStart());
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

static RuleCheckerASTContextRegistry::Add<Rule_4_10_2> X("4-10-2", "");
}
