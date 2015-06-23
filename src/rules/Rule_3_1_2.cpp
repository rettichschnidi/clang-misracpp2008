//===-  Rule_3_1_2.cpp - Checker for MISRA C++ 2008 rule 3-1-2-------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "misracpp2008.h"
#include <vector>

using namespace clang;

namespace misracpp2008 {

class Rule_3_1_2 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_3_1_2> {
public:
  Rule_3_1_2() : RuleCheckerASTContext() {}

  bool TraverseDecl(Decl *D) {
    bool retVal = true;
    if (D) {
      const bool isFuncDecl = isa<FunctionDecl>(D);
      if (inFunc.back() && isFuncDecl && !doIgnore(D->getLocStart())) {
        reportError(D->getLocation());
      }

      inFunc.push_back(isFuncDecl);
      retVal = RecursiveASTVisitor<Rule_3_1_2>::TraverseDecl(D);
      inFunc.pop_back();
    }
    return retVal;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }

private:
  std::vector<int> inFunc = {false};
};

static RuleCheckerASTContextRegistry::Add<Rule_3_1_2> X("3-1-2", "");
}
