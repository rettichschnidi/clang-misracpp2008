//===-  BannedFunctionUsageChecker.h - Helper class -----------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
// Copyright (C) 2014 Reto Schneider <code@reto-schneider.ch>
//
//===----------------------------------------------------------------------===//

#ifndef ILLEGAL_FUNCTION_USAGE_CHECKER_H
#define ILLEGAL_FUNCTION_USAGE_CHECKER_H

#include "misracpp2008.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Lex/Token.h"
#include <string>
#include <set>

using namespace clang;

namespace misracpp2008 {

class BannedFunctionUsageChecker
    : public RuleCheckerASTContext,
      public RuleCheckerPreprocessor,
      public RecursiveASTVisitor<BannedFunctionUsageChecker> {
public:
  BannedFunctionUsageChecker() {}
  bool VisitDeclRefExpr(DeclRefExpr *expr) {
    std::string funName = expr->getNameInfo().getAsString();
    if (getIllegalFunctions().count(funName)) {
      reportRuleViolation(expr->getLocStart());
    }
    return true;
  }
  virtual void MacroExpands(const Token &MacroNameTok, const MacroDirective *MD,
                            SourceRange Range, const MacroArgs *Args) {
    const std::string &macroName = MacroNameTok.getIdentifierInfo()->getName();
    if (getIllegalFunctions().count(macroName)) {
      if (doIgnore(Range.getBegin())) {
        return;
      }
      reportRuleViolation(Range.getBegin());
    }
  }

protected:
  virtual void doWork() {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
  virtual const std::set<std::string> &getIllegalFunctions() const = 0;
  virtual void reportRuleViolation(clang::SourceLocation loc) = 0;
};
}

#endif
