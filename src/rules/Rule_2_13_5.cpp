//===-  Rule_2_13_5.cpp - Checker for MISRA C++ 2008 rule 2-13-5-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/Diagnostic.h"
#include <string>

using namespace clang;

namespace misracpp2008 {

class Rule_2_13_5 : public RuleCheckerASTContext,
                    public clang::RecursiveASTVisitor<Rule_2_13_5> {
public:
  Rule_2_13_5() : RuleCheckerASTContext() {}

  bool VisitStringLiteral(const StringLiteral *sl) {
    if (doIgnore(sl->getLocStart())) {
      return true;
    }

    // Bail out if there is just one "string-literal" behind this StringLiteral
    if (sl->getNumConcatenated() == 1) {
      return true;
    }

    const SourceLocation *I = sl->tokloc_begin();
    const bool isWide = isWideStringLiteralPart(*I);
    for (const SourceLocation *IE = sl->tokloc_end(); I != IE; ++I) {
      if (isWide != isWideStringLiteralPart(*I)) {
        reportError(*I);
        break;
      }
    }
    return true;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }

  bool isWideStringLiteralPart(const SourceLocation &loc) {
    const clang::SourceManager &sm = context->getSourceManager();
    const SourceLocation spellingLoc = sm.getSpellingLoc(loc);
    const std::string lexem = srcLocToString(spellingLoc);
    assert(lexem.size() > 0 &&
           "Lexems for string literals are at least 2 chars wide.");
    return lexem[0] == 'L';
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_2_13_5> X("2-13-5", "");
}
