//===-  Rule_6_3_1.cpp - Checker for MISRA C++ 2008 rule 6-3-1-------------===//
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

class Rule_6_3_1 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_6_3_1> {
public:
  Rule_6_3_1() : RuleCheckerASTContext() {}

  bool VisitStmt(Stmt *S) {
    if (doIgnore(S->getLocStart())) {
      return true;
    }

    if (ForStmt *fs = dyn_cast<ForStmt>(S)) {
      ReportIfNotCompund(fs->getBody());
    } else if (DoStmt *ds = dyn_cast<DoStmt>(S)) {
      ReportIfNotCompund(ds->getBody());
    } else if (WhileStmt *ws = dyn_cast<WhileStmt>(S)) {
      ReportIfNotCompund(ws->getBody());
    }
    return true;
  }

private:
  void ReportIfNotCompund(const Stmt *S) {
    if (isa<CompoundStmt>(S) != true) {
      reportError(S->getLocStart());
    }
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_6_3_1> X("6-3-1",
                                                        RULE_TEXT_6_3_1);
}
