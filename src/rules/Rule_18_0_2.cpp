//===-  Rule_18_0_2.cpp - Checker for MISRA C++ 2008 rule 18-0-2-----------===//
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
#include <string>
#include <set>

using namespace clang;

namespace misracpp2008 {

const static std::string ruleName = "18-0-2";

class Rule_18_0_2 : public RuleCheckerASTContext,
                    public RecursiveASTVisitor<Rule_18_0_2> {
private:
  static const std::set<std::string> illegalFunctions;

public:
  bool VisitDeclRefExpr(DeclRefExpr *expr) {
    if (doIgnore(expr->getLocation())) {
      return true;
    }

    std::string funName = expr->getNameInfo().getAsString();
    if (illegalFunctions.count(funName)) {
      reportError(expr->getLocStart());
    }
    return true;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

const std::set<std::string> Rule_18_0_2::illegalFunctions = { "atof", "atoi",
                                                              "atol" };

static RuleCheckerASTContextRegistry::Add<Rule_18_0_2> X(ruleName.c_str(),
                                                         RULE_TEXT_18_0_2);
}
