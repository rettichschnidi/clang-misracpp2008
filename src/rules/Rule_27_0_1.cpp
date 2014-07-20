//===-  Rule_27_0_1.cpp - Checker for MISRA C++ 2008 rule 27-0-1-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
// Copyright (C) 2014 Reto Schneider <code@reto-schneider.ch>
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "clang/Basic/SourceManager.h"
#include <string>

using namespace clang;

namespace misracpp2008 {

const static std::string ruleName = "27-0-1";

class Rule_27_0_1 : public RuleCheckerPreprocessor {
private:
  static const std::set<std::string> illegalIncludes;

public:
  virtual void InclusionDirective(SourceLocation HashLoc,
                                  const Token &IncludeTok, StringRef FileName,
                                  bool IsAngled, CharSourceRange FilenameRange,
                                  const FileEntry *File, StringRef SearchPath,
                                  StringRef RelativePath,
                                  const Module *Imported) {
    if (illegalIncludes.count(FileName)) {
      reportError(RULE_TEXT_27_0_1, HashLoc);
    }
  }
};

const std::set<std::string> Rule_27_0_1::illegalIncludes = {"cstdio"};

static RuleCheckerPreprocessorRegistry::Add<Rule_27_0_1>
X(ruleName.c_str(), "MISRA C++ 2008 rule checker");
}
