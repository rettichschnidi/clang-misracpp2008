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

const static std::string ruleName = "19-3-1";

class Rule_19_3_1 : public RuleCheckerPreprocessor {
private:
  static const std::string illegalVariableName;

public:
  // Abuse the fact that errno is defined as a macro (at least on my system)
  virtual void MacroExpands(const Token &MacroNameTok, const MacroDirective *MD,
                            SourceRange Range, const MacroArgs *Args) {
    const std::string &name = MacroNameTok.getIdentifierInfo()->getName();
    if (name == illegalVariableName) {
      if (doIgnore(Range.getBegin())) {
        return;
      }

      reportError("The error indicator errno shall not be used.",
                  Range.getBegin());
    }
  }
};

const std::string Rule_19_3_1::illegalVariableName = "errno";

static RuleCheckerPreprocessorRegistry::Add<Rule_19_3_1>
X(ruleName.c_str(), "MISRA C++ 2008 rule checker");
}
