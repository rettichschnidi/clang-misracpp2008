//===-  Rule_10_3_2.h - Checker for MISRA C++ 2008 rule 10-3-2-------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef RULE_10_3_2_H
#define RULE_10_3_2_H

#include "misracpp2008.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"

namespace clang {
class ASTContext;
class Decl;
}

namespace misracpp2008 {

class Rule_10_3_2 : public RuleCheckerASTContext,
                    public clang::RecursiveASTVisitor<Rule_10_3_2> {
public:
  explicit Rule_10_3_2(clang::ASTContext &context,
                       clang::DiagnosticsEngine::Level diagLevel);
  bool VisitCXXRecordDecl(clang::CXXRecordDecl *decl);
  virtual ~Rule_10_3_2();

protected:
  virtual void doWork();
};
}

#endif
