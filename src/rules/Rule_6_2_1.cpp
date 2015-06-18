//===-  Rule_6_2_1.cpp - Checker for MISRA C++ 2008 rule 6-2-1-------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "misracpp2008.h"
#include <set>

using namespace clang;

namespace misracpp2008 {

class Rule_6_2_1 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_6_2_1> {
public:
  Rule_6_2_1() : RuleCheckerASTContext() {}

  bool VisitExpr(Expr *E) {
    if (doIgnore(E->getLocStart())) {
      return true;
    }

    for (const auto I : E->children()) {
      const Stmt *realStmt = I->IgnoreImplicit();
      if (const auto *bo = dyn_cast<BinaryOperator>(realStmt)) {
        if (bo->getOpcode() == BO_Assign) {
          reportViolatingStatement(bo);
        }
      }
      if (const auto *oc = dyn_cast<CXXOperatorCallExpr>(realStmt)) {
        if (oc->getOperator() == OO_Equal) {
          reportViolatingStatement(oc);
        }
      }
    }
    return true;
  }

private:
  std::set<const Stmt *> reportedStatements;
  void reportViolatingStatement(const Stmt *stmt) {
    if (reportedStatements.find(stmt) == reportedStatements.end()) {
      reportedStatements.insert(stmt);
      reportError(stmt->getLocStart());
    }
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_6_2_1> X("6-2-1", "");
}
