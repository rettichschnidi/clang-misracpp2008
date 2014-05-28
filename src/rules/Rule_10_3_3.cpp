//===-  Rule_10_3_3.cpp - Checker for MISRA C++ 2008 rule 10-3-3-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "Rule_10_3_3.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang;

namespace misracpp2008 {

const static std::string ruleName = "10-3-3";

Rule_10_3_3::Rule_10_3_3(clang::ASTContext &context,
                         clang::DiagnosticsEngine::Level diagLevel)
    : RuleCheckerASTContext(context, diagLevel) {}

bool Rule_10_3_3::VisitCXXMethodDecl(clang::CXXMethodDecl *decl) {
  if (decl->isPure()) {
    auto B = context.overridden_methods_begin(decl);
    auto E = context.overridden_methods_end(decl);

    while (B != E) {
      const CXXMethodDecl &m = **B;
      if (m.isPure() == false) {
        DiagnosticsEngine &diagEngine = context.getDiagnostics();
        unsigned diagID = diagEngine.getCustomDiagID(
            DiagnosticsEngine::Error,
            "A virtual function shall only be overridden by a pure virtual"
            " function if it is itself declared as pure virtual.");
        SourceLocation location = decl->getLocation();
        diagEngine.Report(location, diagID);
        return false;
      }
      B++;
    }
  }
  return true;
}

Rule_10_3_3::~Rule_10_3_3() {}

void Rule_10_3_3::doWork() {
  this->TraverseDecl(this->context.getTranslationUnitDecl());
}

static auto dummy = Consumer::RegisterChecker(
    ruleName, std::shared_ptr<RuleCheckerFactoryBase>(
                  new RuleCheckerCreatorFactory<Rule_10_3_3>));
}
