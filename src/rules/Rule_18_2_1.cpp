//===-  Rule_18_2_1.h - Checker for MISRA C++ 2008 rule 18-2-1-------------===//
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

const static std::string ruleName = "18-2-1";

class Rule_18_2_1 : public RuleCheckerASTContext,
                    public RecursiveASTVisitor<Rule_18_2_1> {
public:
  Rule_18_2_1() : RuleCheckerASTContext() {}
  bool VisitOffsetOfExpr(OffsetOfExpr *expr) {
    unsigned diagID = diagEngine->getCustomDiagID(
        diagLevel, "The macro offsetof shall not be used.");
    diagEngine->Report(expr->getLocStart(), diagID);
    return true;
  }

protected:
  virtual void doWork() {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_18_2_1>
X(ruleName.c_str(), "MISRA C++ 2008 rule checker");
}
