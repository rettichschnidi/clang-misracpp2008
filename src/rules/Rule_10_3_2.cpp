//===-  Rule_10_3_2.cpp - Checker for MISRA C++ 2008 rule 10-3-2-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
// Copyright (C) 2014 Reto Schneider <code@reto-schneider.ch>
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang;

namespace misracpp2008 {

const static std::string ruleName = "10-3-2";

class Rule_10_3_2 : public RuleCheckerASTContext,
                    public clang::RecursiveASTVisitor<Rule_10_3_2> {
public:
  Rule_10_3_2() : RuleCheckerASTContext() {}
  void reportError(SourceLocation loc) {
    RuleChecker::reportError(RULE_TEXT_10_3_2, loc);
  }
  bool VisitCXXRecordDecl(CXXRecordDecl *decl) {
    if (doIgnore(decl->getLocStart())) {
      return true;
    }

    CXXRecordDecl::method_iterator B = decl->method_begin();
    CXXRecordDecl::method_iterator E = decl->method_end();
    while (B != E) {
      if (!B->isImplicit() && B->isVirtual() && !B->isVirtualAsWritten()) {
        reportError(B->getLocation());
        break;
      }
      B++;
    }
    return true;
  }
  bool VisitCXXDestructorDecl(clang::CXXDestructorDecl *decl) {
    if (doIgnore(decl->getLocStart())) {
      return true;
    }

    if (decl->isVirtual() && !decl->isVirtualAsWritten()) {
      reportError(decl->getLocation());
    }
    return true;
  }

  virtual ~Rule_10_3_2() {}

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_10_3_2>
X(ruleName.c_str(), "MISRA C++ 2008 rule checker");
}
