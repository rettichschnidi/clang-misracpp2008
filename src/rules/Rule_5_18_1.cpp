//===-  Rule_5_18_1.cpp - Checker for MISRA C++ 2008 rule 5-18-1-----------===//
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

class Rule_5_18_1 : public RuleCheckerASTContext,
                    public RecursiveASTVisitor<Rule_5_18_1> {
public:
  Rule_5_18_1() : RuleCheckerASTContext() {}

  bool VisitBinComma(const BinaryOperator *S) {
    if (doIgnore(S->getLocStart())) {
      return true;
    }

    reportError(S->getLocStart());
    return true;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_5_18_1> X("5-18-1", "");
}
