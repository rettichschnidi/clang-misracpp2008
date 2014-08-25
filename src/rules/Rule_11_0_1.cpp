//===-  Rule_11_0_1.cpp - Checker for MISRA C++ 2008 rule 11-0-1-----------===//
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

class Rule_11_0_1 : public RuleCheckerASTContext,
                    public RecursiveASTVisitor<Rule_11_0_1> {
public:
  Rule_11_0_1() : RuleCheckerASTContext() {}

  bool VisitDecl(Decl *D) {
    if (doIgnore(D->getLocStart())) {
      return true;
    }

    const auto *cxxRecDecl = dyn_cast<CXXRecordDecl>(D);
    if (!cxxRecDecl) {
      return true;
    }

    // Sort out any non-class or struct declarations
    if ((cxxRecDecl->isClass() || cxxRecDecl->isStruct()) == false) {
      return true;
    }
    // We can only judge classes with a visible definition
    if (cxxRecDecl->hasDefinition() == false) {
      return true;
    }
    // Rule applies to non-POD classes only
    // Note: POD definition from C++11, not 03. Problem?
    if (cxxRecDecl->isPOD()) {
      return true;
    }

    // Report all non-private members
    for (const FieldDecl *fieldDecl : cxxRecDecl->fields()) {
      if (fieldDecl->getAccess() != AS_private) {
        reportError(fieldDecl->getLocStart());
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

static RuleCheckerASTContextRegistry::Add<Rule_11_0_1> X("11-0-1",
                                                         RULE_TEXT_11_0_1);
}
