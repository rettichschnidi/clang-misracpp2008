//===-  Rule_15_5_1.cpp - Checker for MISRA C++ 2008 rule 15-5-1-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "clang/AST/ASTContext.h"
#include "clang/AST/OperationKinds.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "misracpp2008.h"
#include <iostream>

using namespace clang;

template <typename T> Stmt *searchStmt(Stmt *S) {

  Stmt *b{nullptr};
  if (!S)
    return b;

  if (isa<T>(S)) {
    return S;
  }

  for (auto c : S->children()) {
    b = searchStmt<T>(c);
    if (b) {
      return b;
    }
  }

  return b;
}

namespace misracpp2008 {

class Rule_15_5_1 : public RuleCheckerASTContext,
                    public RecursiveASTVisitor<Rule_15_5_1> {
public:
  Rule_15_5_1() : RuleCheckerASTContext() {}

  bool VisitCXXDestructorDecl(CXXDestructorDecl *D) {
    if (doIgnore(D->getLocStart())) {
      return true;
    }
    if (!D->isThisDeclarationADefinition()) {
      return true;
    }

    Stmt *t{nullptr}, *p{nullptr};

    p = D->getBody();

    if (p) {
      if (Stmt *throwStmt = searchStmt<CXXThrowExpr>(p)) {
        t = throwStmt;
      }
    }
    // dctor throws, check if there's a catch block
    if (t && p) {
      auto g = searchStmt<CXXCatchStmt>(p);
      if (!g) {
        reportError(t->getLocStart());
      }
    }

    return true;
  };

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_15_5_1> X("15-5-1", "");
}
