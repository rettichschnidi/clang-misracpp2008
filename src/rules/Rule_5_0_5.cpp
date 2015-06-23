//===-  Rule_5_0_5.cpp - Checker for MISRA C++ 2008 rule 5-0-5-------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "clang/AST/ASTContext.h"
#include "clang/AST/Expr.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "misracpp2008.h"

using namespace clang;

namespace misracpp2008 {

class Rule_5_0_5 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_5_0_5> {
public:
  bool TraverseStmt(Stmt *S) {
    if (CastExpr *CE = dyn_cast_or_null<CastExpr>(S)) {
      const CastKind ck = CE->getCastKind();
      const SourceLocation loc = CE->getLocStart();
      const bool isExplicitCast = isa<ExplicitCastExpr>(CE);
      if (!hasExplicitParentCastExpr && !isExplicitCast && !doIgnore(loc) &&
          (ck == CK_IntegralToFloating || ck == CK_FloatingToIntegral)) {
        reportError(loc);
      }
      hasExplicitParentCastExpr = isExplicitCast;
    } else {
      hasExplicitParentCastExpr = false;
    }

    return RecursiveASTVisitor<Rule_5_0_5>::TraverseStmt(S);
  }

private:
  bool hasExplicitParentCastExpr = false;

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_5_0_5> X("5-0-5", "");
}
