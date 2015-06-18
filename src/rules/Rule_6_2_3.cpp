//===-  Rule_6_2_3.cpp - Checker for MISRA C++ 2008 rule 6-2-3-------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "misracpp2008.h"
#include <set>

using namespace clang;

namespace misracpp2008 {

class Rule_6_2_3 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_6_2_3> {
private:
  std::set<clang::SourceRange> commentLocations;

public:
  Rule_6_2_3() : RuleCheckerASTContext() {}

  bool VisitNullStmt(NullStmt *stmt) {
    if (doIgnore(stmt->getLocStart())) {
      return true;
    }

    if (hasNonWhitespaceBeforeNullStmt(stmt) ||
        hasNonWhitespaceAfterNullStmt(stmt)) {
      reportError(stmt->getLocStart());
    }
    return true;
  }

  bool hasNonWhitespaceAfterNullStmt(const NullStmt *ns) {
    return hasNonWhitespace(ns, 1, 1);
  }

  bool hasNonWhitespaceBeforeNullStmt(const NullStmt *ns) {
    unsigned nullStmtColumnNumber =
        context->getFullLoc(ns->getLocStart()).getSpellingColumnNumber();
    return hasNonWhitespace(ns, nullStmtColumnNumber,
                            -1 * nullStmtColumnNumber);
  }

  bool hasNonWhitespace(const NullStmt *ns, size_t commentLength, int offset) {
    clang::SourceManager &sm = context->getSourceManager();

    SourceLocation offsetToStmtLocation =
        ns->getLocEnd().getLocWithOffset(offset);
    std::pair<FileID, unsigned> startLoc =
        sm.getDecomposedLoc(offsetToStmtLocation);
    llvm::StringRef fileData = sm.getBufferData(startLoc.first);
    llvm::StringRef commentString =
        fileData.substr(startLoc.second, commentLength).trim();
    return commentString.size() > 0;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_6_2_3> X("6-2-3", "");
}
