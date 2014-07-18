//===-  Rule_18_0_1.cpp - Checker for MISRA C++ 2008 rule 18-0-1-----------===//
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

const static std::string ruleName = "18-0-1";

class Rule_18_0_1 : public RuleCheckerPreprocessor {
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
      if (doIgnore(HashLoc)) {
        return;
      }
      reportError("The C library shall not be used.", HashLoc);
    }
  }
};

const std::set<std::string> Rule_18_0_1::illegalIncludes = {
    "assert.h", "ctype.h",   "errno.h",  "fenv.h",   "float.h",  "inttypes.h",
    "iso646.h", "limits.h",  "locale.h", "math.h",   "setjmp.h", "signal.h",
    "stdarg.h", "stdbool.h", "stddef.h", "stdint.h", "stdlib.h", "string.h",
    "tgmath.h", "time.h",    "uchar.h",  "wchar.h",  "wctype.h"};

static RuleCheckerPreprocessorRegistry::Add<Rule_18_0_1>
X(ruleName.c_str(), "MISRA C++ 2008 rule checker");
}
