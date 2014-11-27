//===-  Rule_6_4_2.cpp - Checker for MISRA C++ 2008 rule 6-4-2-------------===//
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

class Rule_6_4_2 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_6_4_2> {
public:
  Rule_6_4_2() : RuleCheckerASTContext() {}

  bool VisitStmt(Stmt *S) {
    if (doIgnore(S->getLocStart())) {
      return true;
    }

    const IfStmt *ifStmt = dyn_cast<IfStmt>(S);
    if (!ifStmt) {
      return true;
    }

    const auto &parents = context->getParents(*ifStmt);
    assert(parents.size() == 1 && "Expect exactly one parent node.");

    // Bail out if this is not the first if in a if...else-if clause
    if (parents[0].get<IfStmt>() != nullptr) {
      return true;
    }

    // Walk down all the else branches, see if they are in fact another ifStmt
    // (true for else-if constructs) and report an error if the very last else-
    // if construct does not have an else branch.
    for (unsigned int elseIfCount = 0; ifStmt != nullptr; ++elseIfCount) {
      const Stmt *elseStmt = ifStmt->getElse();
      if (elseStmt != nullptr) {
        ifStmt = dyn_cast<IfStmt>(elseStmt);
        continue;
      }

      if (elseIfCount > 0) {
        reportError(S->getLocStart());
      }

      break;
    }

    return true;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_6_4_2> X("6-4-2", "");
}
