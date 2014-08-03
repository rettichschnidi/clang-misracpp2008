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

const static std::string ruleName = "6-4-2";

class Rule_6_4_2 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_6_4_2> {
public:
  Rule_6_4_2() : RuleCheckerASTContext() {}

  bool VisitStmt(Stmt *S) {
    if (doIgnore(S->getLocStart())) {
      return true;
    }

    if (const IfStmt *ifStmt = dyn_cast<IfStmt>(S)) {
      if (const Stmt *elseStmt = ifStmt->getElse()) {
        if (const IfStmt *ifElseStmt = dyn_cast<IfStmt>(elseStmt)) {
          const Stmt *finalElseStmt = ifElseStmt->getElse();
          if (finalElseStmt == nullptr ||
              isa<CompoundStmt>(finalElseStmt) == false) {
            reportError(RULE_TEXT_6_4_2, ifStmt->getLocStart());
          }
        }
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

static RuleCheckerASTContextRegistry::Add<Rule_6_4_2>
    X(ruleName.c_str(), "MISRA C++ 2008 rule checker");
}
