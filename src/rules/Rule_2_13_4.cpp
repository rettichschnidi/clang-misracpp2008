//===-  Rule_2_13_4.cpp - Checker for MISRA C++ 2008 rule 2-13-4-----------===//
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
#include <string>

using namespace clang;

namespace misracpp2008 {

class Rule_2_13_4 : public RuleCheckerASTContext,
                    public RecursiveASTVisitor<Rule_2_13_4> {
public:
  Rule_2_13_4() : RuleCheckerASTContext() {}

  bool VisitStmt(Stmt *S) {
    // Bail out early if this location should not be checked
    if (doIgnore(S->getLocStart())) {
      return true;
    }

    // This rule applies to float and integer literals only.
    if (!(isa<FloatingLiteral>(S) || isa<IntegerLiteral>(S))) {
      return true;
    }

    std::string lexem = srcLocToString(S->getLocStart());
    if (lexem.find_first_of("ulf") != std::string::npos) {
      reportError(S->getLocStart());
    }

    return true;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_2_13_4> X("2-13-4", "");
}
