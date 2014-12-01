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
#include "clang/Basic/SourceLocation.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Lex/LiteralSupport.h"

using namespace clang;

namespace misracpp2008 {

class Rule_2_13_4 : public RuleCheckerASTContext,
                    public RecursiveASTVisitor<Rule_2_13_4> {
public:
  Rule_2_13_4() : RuleCheckerASTContext() {}

  bool VisitExpr(Expr *expr) {
    // Bail out early if this location should not be checked
    if (doIgnore(expr->getLocStart())) {
      return true;
    }

    // This rule applies to float and integer literals only.
    if (!(isa<FloatingLiteral>(expr) || isa<IntegerLiteral>(expr))) {
      return true;
    }

    using std::string;
    const SourceManager &sm = context->getSourceManager();
    const SourceLocation spellingLoc = sm.getSpellingLoc(expr->getLocStart());
    const string lexem = srcLocToString(spellingLoc);
    const NumericLiteralParser nlp(lexem, spellingLoc, CI->getPreprocessor());

    if ((nlp.isUnsigned && lexem.find("u") != string::npos) ||
        (nlp.isFloat && lexem.find("f") != string::npos) ||
        ((nlp.isLong || nlp.isLongLong) && lexem.find("l") != string::npos)) {
      reportError(expr->getLocEnd());
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
