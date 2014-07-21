//===-  Rule_17_0_1.cpp - Checker for MISRA C++ 2008 rule 17-0-1-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
// Copyright (C) 2014 Reto Schneider <code@reto-schneider.ch>
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "clang/Lex/Token.h"
#include "clang/Basic/IdentifierTable.h"
#include <string>

using namespace clang;

namespace misracpp2008 {

const static std::string ruleName = "17-0-1";

class Rule_17_0_1 : public RuleCheckerPreprocessor {
private:
  static const std::set<std::string> illegalMacroNames;
  void detectViolation(const Token &MacroNameTok) {
    const std::string &name = MacroNameTok.getIdentifierInfo()->getName();

    if (doIgnore(MacroNameTok.getLocation())) {
      return;
    }

    if (illegalMacroNames.count(name) || (name.find('_') == 0)) {
      const SourceLocation &loc = MacroNameTok.getLocation();
      if (doIgnore(loc)) {
        return;
      }
      reportError(RULE_TEXT_17_0_1, loc);
    }
  }

public:
  // Detect #defines
  virtual void MacroDefined(const Token &MacroNameTok,
                            const MacroDirective *MD) {
    detectViolation(MacroNameTok);
  }

  // Detect #undef
  virtual void MacroUndefined(const Token &MacroNameTok,
                              const MacroDirective *MD) {
    detectViolation(MacroNameTok);
  }
};

const std::set<std::string> Rule_17_0_1::illegalMacroNames = {
  "__cplusplus",                      "__DATE__",
  "__FILE__",                         "__LINE__",
  "__STDC_HOSTED__",                  "__TIME__",
  "__STDC__",                         "__STDC_MB_MIGHT_NEQ_WC__",
  "__STDC_VERSION__",                 "__STDC_ISO_10646__",
  "__STDCPP_STRICT_POINTER_SAFETY__", "__STDCPP_THREADS__",
  "define",                           "errno",
  "assert"
};

static RuleCheckerPreprocessorRegistry::Add<Rule_17_0_1>
X(ruleName.c_str(), "MISRA C++ 2008 rule checker");
}
