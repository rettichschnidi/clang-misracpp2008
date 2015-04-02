//===-  Rule_27_0_1.cpp - Checker for MISRA C++ 2008 rule 27-0-1-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "clang/Basic/SourceManager.h"
#include <string>

using namespace clang;

namespace misracpp2008 {

class Rule_27_0_1 : public RuleCheckerPPCallback {
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
      reportError(HashLoc);
    }
  }
};

const std::set<std::string> Rule_27_0_1::illegalIncludes = { "cstdio" };

static RuleCheckerPreprocessorRegistry::Add<Rule_27_0_1> X("27-0-1", "");
}
