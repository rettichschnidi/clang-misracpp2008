//===-  Rule_2_10_2.cpp - Checker for MISRA C++ 2008 rule 2-10-2-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
// Copyright (C) 2014 Reto Schneider <code@reto-schneider.ch>
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/Diagnostic.h"
#include <map>
#include <string>
#include <cstring>
#include <algorithm>
#include <functional>

using namespace clang;

namespace misracpp2008 {

class Rule_2_10_2 : public RuleCheckerASTContext,
                    public RecursiveASTVisitor<Rule_2_10_2> {
public:
  Rule_2_10_2() : RuleCheckerASTContext() {}

  bool VisitDecl(Decl *decl) {
    // Bail out early if this location should not be checked.
    if (doIgnore(decl->getLocation())) {
      return true;
    }
    // Bail out if this is not a named declaration.
    if (!isa<NamedDecl>(decl)) {
      return true;
    }

    const auto *namedDecl = cast<NamedDecl>(decl);
    const DeclarationName &declN = namedDecl->getDeclName();
    // Bail out if it is an operator
    if (declN.getCXXOverloadedOperator() != OO_None) {
      return true;
    }

    // Walk up till we reach the outermost scope, check each one for a
    // declaration with the same name.
    for (const DeclContext *outerScope =
             namedDecl->getDeclContext()->getParent();
         outerScope != nullptr; outerScope = outerScope->getParent()) {
      if (isa<LinkageSpecDecl>(outerScope)) {
        continue;
      }

      DeclContext::lookup_const_result result = outerScope->lookup(declN);
      if (result.empty()) {
        continue;
      }
      // Bail out if we find ourself
      if (std::find(result.begin(), result.end(), namedDecl) != result.end()) {
        continue;
      }

      // All hope is lost - we have a shadowing declaration.
      // Report location of the offending and the shadowed declaration.
      reportError(decl->getLocation());
      reportError(result[0]->getLocation(),
                  "Previous occurence of identifier '%0'")
          << declN.getAsString();
    }
    return true;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_2_10_2> X("2-10-2",
                                                         RULE_TEXT_2_10_2);
}
