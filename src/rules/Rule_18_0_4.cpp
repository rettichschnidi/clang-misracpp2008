//===-  Rule_18_0_4.cpp - Checker for MISRA C++ 2008 rule 18-0-4-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
// Copyright (C) 2014 Reto Schneider <code@reto-schneider.ch>
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "clang/AST/ASTContext.h"
#include "clang/Lex/PPCallbacks.h"
#include <string>

using namespace clang;

namespace misracpp2008 {

const static std::string ruleName = "18-0-4";

class Rule_18_0_4 : public RuleCheckerPreprocessor {
private:
  static const std::set<std::string> illegalIncludes;

public:
  virtual void InclusionDirective(SourceLocation HashLoc,
                                  const Token &IncludeTok, StringRef FileName,
                                  bool IsAngled, CharSourceRange FilenameRange,
                                  const FileEntry *File, StringRef SearchPath,
                                  StringRef RelativePath,
                                  const Module *Imported) override {
    if (doIgnore(HashLoc)) {
      return;
    }

    if (illegalIncludes.count(FileName)) {
      reportError(RULE_TEXT_18_0_4, HashLoc);
    }
  }
};

const std::set<std::string> Rule_18_0_4::illegalIncludes = { "ctime" };

static RuleCheckerPreprocessorRegistry::Add<Rule_18_0_4>
X(ruleName.c_str(), "MISRA C++ 2008 rule checker");
}
