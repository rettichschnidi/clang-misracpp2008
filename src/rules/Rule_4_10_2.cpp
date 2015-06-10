//===-  Rule_4_10_2.cpp - Checker for MISRA C++ 2008 rule  4-10-2----------===//
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

using namespace clang;

namespace misracpp2008 {

class Rule_4_10_2 : public RuleCheckerASTContext,
                    public RecursiveASTVisitor<Rule_4_10_2> {
public:
  Rule_4_10_2() : RuleCheckerASTContext() {}

  bool VisitCastExpr(CastExpr *ce) {
    if (doIgnore(ce->getLocStart())) {
      return true;
    }
    // If casting from null ptr constant to pointer
    // and constant has integer type report error
    if (ce->getCastKind() == clang::CK_NullToPointer) {
      if (ce->getSubExpr() && ce->getSubExpr()->getType()->isIntegerType()) {
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
