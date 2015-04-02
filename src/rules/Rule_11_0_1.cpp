//===-  Rule_11_0_1.cpp - Checker for MISRA C++ 2008 rule 11-0-1-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
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

  bool VisitCXXRecordDecl(const CXXRecordDecl *decl) {
    if (doIgnore(decl->getLocStart())) {
      return true;
    }

    // Sort out any non-class or struct declarations
    if ((decl->isClass() || decl->isStruct()) == false) {
      return true;
    }
    // We can only judge classes with a visible definition
    if (decl->hasDefinition() == false) {
      return true;
    }
    // Rule applies to non-POD classes only
    // Note: POD definition from C++11, not 03. Problem?
    if (decl->isPOD()) {
      return true;
    }

    // Report all non-private members
    for (const FieldDecl *fieldDecl : decl->fields()) {
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

static RuleCheckerASTContextRegistry::Add<Rule_11_0_1> X("11-0-1", "");
}
