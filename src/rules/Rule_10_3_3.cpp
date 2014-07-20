//===-  Rule_10_3_3.cpp - Checker for MISRA C++ 2008 rule 10-3-3-----------===//
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

const static std::string ruleName = "10-3-3";

class Rule_10_3_3 : public RuleCheckerASTContext,
                    public clang::RecursiveASTVisitor<Rule_10_3_3> {
public:
  Rule_10_3_3() : RuleCheckerASTContext() {}
  bool VisitCXXMethodDecl(clang::CXXMethodDecl *decl) {
    if (decl->isPure()) {
      auto B = context->overridden_methods_begin(decl);
      auto E = context->overridden_methods_end(decl);

      while (B != E) {
        const CXXMethodDecl &m = **B;
        if (m.isPure() == false) {
          reportError(RULE_TEXT_10_3_3, decl->getLocation());
          break;
        }
        B++;
      }
    }
    return true;
  }

  virtual ~Rule_10_3_3() {}

protected:
  virtual void doWork() {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_10_3_3>
X(ruleName.c_str(), "MISRA C++ 2008 rule checker");
}
