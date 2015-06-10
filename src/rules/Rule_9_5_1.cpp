//===-  Rule_9_5_1.cpp - Checker for MISRA C++ 2008 rule 9-5-1-------------===//
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

class Rule_9_5_1 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_9_5_1> {
public:
  Rule_9_5_1() : RuleCheckerASTContext() {}

  bool VisitCXXRecordDecl(const CXXRecordDecl *RD) {
    if (doIgnore(RD->getLocStart())) {
      return true;
    }

    if (RD->getTagKind() == TTK_Union) {
      reportError(RD->getLocation());
    }

    return true;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_9_5_1> X("9-5-1", "");
}
