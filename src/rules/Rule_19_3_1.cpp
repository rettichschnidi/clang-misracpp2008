//===-  Rule_19_3_1.cpp - Checker for MISRA C++ 2008 rule 19-3-1-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "clang/Lex/Token.h"
#include "clang/Basic/IdentifierTable.h"
#include <string>

using namespace clang;

namespace misracpp2008 {

class Rule_19_3_1 : public RuleCheckerPPCallback {
private:
  static const std::string illegalMacroName;

public:
  // errno is a macro.
  virtual void MacroExpands(const Token &MacroNameTok,
                            const MacroDefinition &MD, SourceRange Range,
                            const MacroArgs *Args) override {
    const std::string &name = MacroNameTok.getIdentifierInfo()->getName();
    if (name == illegalMacroName) {
      if (doIgnore(MacroNameTok.getLastLoc())) {
        return;
      }

      reportError(Range.getBegin());
    }
  }
};

const std::string Rule_19_3_1::illegalMacroName = "errno";

static RuleCheckerPreprocessorRegistry::Add<Rule_19_3_1> X("19-3-1", "");
}
