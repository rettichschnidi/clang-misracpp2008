//===-  Rule_27_0_1.cpp - Checker for MISRA C++ 2008 rule 27-0-1-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "clang/AST/ASTContext.h"
#include "clang/Lex/PPCallbacks.h"
#include <string>

using namespace clang;

namespace misracpp2008 {

const static std::string ruleName = "27-0-1";

class Rule_27_0_1 : public RuleCheckerPreprocessor {
private:
  static const std::string illegalInclude;

public:
  virtual void InclusionDirective(SourceLocation HashLoc,
                                  const Token &IncludeTok, StringRef FileName,
                                  bool IsAngled, CharSourceRange FilenameRange,
                                  const FileEntry *File, StringRef SearchPath,
                                  StringRef RelativePath,
                                  const Module *Imported) {
    if (FileName == illegalInclude) {
      unsigned diagID = diagEngine->getCustomDiagID(
          diagLevel,
          "The stream input/output library <cstdio> shall not be used.");
      diagEngine->Report(HashLoc, diagID);
    }
  }
};

const std::string Rule_27_0_1::illegalInclude = "cstdio";

static RuleCheckerPreprocessorRegistry::Add<Rule_27_0_1>
X(ruleName.c_str(), "MISRA C++ 2008 rule 27-0-1 checker");
}
