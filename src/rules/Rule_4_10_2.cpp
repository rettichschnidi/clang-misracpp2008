//===-  Rule_4_10_2.cpp - Checker for MISRA C++ 2008 rule 4-10-2-------------===//
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

class Rule_4_10_2 : public RuleCheckerASTContext,
                    public RecursiveASTVisitor<Rule_4_10_2> {
public:
  Rule_4_10_2() : RuleCheckerASTContext() {}

  bool VisitCallExpr(CallExpr *CE) {
    if (doIgnore(CE->getLocStart())) {
      return true;
    }

    auto calleeDecl = CE->getDirectCallee();
    if (!calleeDecl) {
      return true;
    }

    if (calleeDecl->getNumParams() != CE->getNumArgs() ) {
        return true;
    }

    // If any function argument is implicitly casted to a pointer
    // type report an error
    for (unsigned int i = 0; i < CE->getNumArgs(); ++i) {
      auto e = CE->getArg(i)->IgnoreImplicit();
      auto p = calleeDecl->getParamDecl(i);

      if (e->getType()->isIntegerType() &&
          p->getOriginalType()->isPointerType()) {
        reportError(CE->getExprLoc());
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
