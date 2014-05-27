//===-  Rule_10_3_3.h - Checker for MISRA C++ 2008 rule 10-3-3-------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef RULE_10_3_3_H
#define RULE_10_3_3_H

#include "misracpp2008.h"
#include "clang/AST/RecursiveASTVisitor.h"

namespace clang {
class ASTContext;
class Decl;
}

namespace misracpp2008 {

class Rule_10_3_3 : public RuleChecker,
                    public clang::RecursiveASTVisitor<Rule_10_3_3> {
public:
  explicit Rule_10_3_3(clang::ASTContext &context);
  bool VisitCXXMethodDecl(clang::CXXMethodDecl *decl);
  virtual ~Rule_10_3_3();

protected:
  virtual void doWork();
};
}

#endif
