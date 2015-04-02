//===-  Rule_10_3_2.cpp - Checker for MISRA C++ 2008 rule 10-3-2-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang;

namespace misracpp2008 {

class Rule_10_3_2 : public RuleCheckerASTContext,
                    public clang::RecursiveASTVisitor<Rule_10_3_2> {
public:
  Rule_10_3_2() : RuleCheckerASTContext() {}
  bool VisitCXXRecordDecl(CXXRecordDecl *decl) {
    if (doIgnore(decl->getLocStart())) {
      return true;
    }

    for (const auto B : decl->methods()) {
      if (!B->isImplicit() && B->isVirtual() && !B->isVirtualAsWritten()) {
        reportError(B->getLocation());
        break;
      }
    }
    return true;
  }
  bool VisitCXXDestructorDecl(clang::CXXDestructorDecl *decl) {
    if (doIgnore(decl->getLocStart())) {
      return true;
    }

    // Definitions outside of the class body do not have the virtual keyword
    if (decl->isThisDeclarationADefinition()) {
      return true;
    }

    if (decl->isVirtual() && !decl->isVirtualAsWritten()) {
      reportError(decl->getLocation());
    }
    return true;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_10_3_2> X("10-3-2", "");
}
