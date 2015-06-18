//===-  Rule_6_4_1.cpp - Checker for MISRA C++ 2008 rule 6-4-1-------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "misracpp2008.h"

using namespace clang;

namespace misracpp2008 {

class Rule_6_4_1 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_6_4_1> {
public:
  Rule_6_4_1() : RuleCheckerASTContext() {}

  bool VisitIfStmt(const IfStmt *stmt) {
    if (doIgnore(stmt->getLocStart())) {
      return true;
    }

    const Stmt *thenStmt = stmt->getThen();
    const Stmt *elseStmt = stmt->getElse();
    // Check if then has a body
    if (thenStmt && isa<CompoundStmt>(thenStmt) == false) {
      reportError(thenStmt->getLocStart());
    }
    // Check if else has a body or another if statement
    if (elseStmt &&
        ((isa<CompoundStmt>(elseStmt) || isa<IfStmt>(elseStmt)) == false)) {
      reportError(elseStmt->getLocStart());
    }
    return true;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_6_4_1> X("6-4-1", "");
}
