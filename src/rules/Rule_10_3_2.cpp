//===-  Rule_10_3_2.cpp - Checker for MISRA C++ 2008 rule 10-3-2-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "Rule_10_3_2.h"
#include "clang/AST/ASTContext.h"

using namespace clang;

namespace misracpp2008 {

const static std::string ruleName = "10-3-2";

Rule_10_3_2::Rule_10_3_2(clang::ASTContext &context,
                         clang::DiagnosticsEngine::Level diagLevel)
    : RuleCheckerASTContext(context, diagLevel) {}

bool Rule_10_3_2::VisitCXXRecordDecl(clang::CXXRecordDecl *decl) {
  CXXRecordDecl::method_iterator B = decl->method_begin();
  CXXRecordDecl::method_iterator E = decl->method_end();
  while (B != E) {
    if (B->isVirtual() && !B->isVirtualAsWritten()) {
      unsigned diagID = diagEngine.getCustomDiagID(
          diagLevel, "Each overriding virtual function shall be declared with"
                     " the virtual keyword.");
      SourceLocation location = B->getLocation();
      diagEngine.Report(location, diagID);
      return false;
    }
    B++;
  }
  return true;
}

Rule_10_3_2::~Rule_10_3_2() {}

void Rule_10_3_2::doWork() {
  this->TraverseDecl(this->context.getTranslationUnitDecl());
}

static auto dummy = Consumer::RegisterChecker(
    ruleName, std::shared_ptr<RuleCheckerFactoryBase>(
                  new RuleCheckerCreatorFactory<Rule_10_3_2>));
}
