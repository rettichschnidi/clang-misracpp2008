//===-  Rule_2_10_2.cpp - Checker for MISRA C++ 2008 rule 2-10-2-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "misracpp2008.h"
#include <algorithm>
#include <cstring>
#include <functional>
#include <map>
#include <string>

using namespace clang;

namespace misracpp2008 {

class Rule_2_10_2 : public RuleCheckerASTContext,
                    public RecursiveASTVisitor<Rule_2_10_2> {
public:
  Rule_2_10_2() : RuleCheckerASTContext() {}

  bool VisitNamedDecl(const NamedDecl *decl) {
    // Bail out early if this location should not be checked.
    if (doIgnore(decl->getLocation())) {
      return true;
    }

    const DeclarationName &declN = decl->getDeclName();
    // Bail out if the declaration is an operator (while all having the name
    // "operator", none of them constitute a violation)
    if (declN.getCXXOverloadedOperator() != OO_None) {
      return true;
    }

    // Walk up till we reach the outermost scope, check each one for a
    // declaration with the same name.
    for (const DeclContext *outerScope = decl->getDeclContext()->getParent();
         outerScope != nullptr; outerScope = outerScope->getParent()) {
      // If e.g. extern "C" gets found, simply continue with the surrounding
      // scope.
      if (isa<LinkageSpecDecl>(outerScope)) {
        continue;
      }

      // If we can not find a declaration with the same name as we have,
      // move one scope up.
      DeclContext::lookup_result result = outerScope->lookup(declN);
      if (result.empty()) {
        continue;
      }

      // Move one scope up if we find ourselves.
      if (std::find(result.begin(), result.end(), decl) != result.end()) {
        continue;
      }

      // Deal with linkage declarations e.g. 'extern "C"'
      if (isRedeclaration<FunctionDecl>(decl, result) ||
          isRedeclaration<VarDecl>(decl, result) ||
          isRedeclaration<TagDecl>(decl, result)) {
        continue;
      }

      // All hope is lost - we have a shadowing declaration.
      // Report location of the offending and the shadowed declaration.
      reportError(decl->getLocation());
      report(result[0]->getLocation(), "Previous occurence of identifier '%0'",
             clang::DiagnosticsEngine::Note)
          << declN.getAsString();
    }
    return true;
  }

private:
  template <typename TDeclType>
  bool isRedeclaration(const NamedDecl *declUnderTest,
                       DeclContext::lookup_result results) {
    using T = Redeclarable<TDeclType>;
    for (const NamedDecl *d : results) {
      if (auto i = dyn_cast<TDeclType>(d)) {
        typename T::redecl_range r = i->redecls();
        if (std::find(r.begin(), r.end(), declUnderTest) != r.end()) {
          return true;
        }
      }
    }
    return false;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_2_10_2> X("2-10-2", "");
}
