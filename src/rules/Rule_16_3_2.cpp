//===-  Rule_16_3_2.cpp - Checker for MISRA C++ 2008 rule 16-3-2-----------===//
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
#include "clang/Lex/MacroInfo.h"
#include <string>

using namespace clang;

namespace misracpp2008 {

class Rule_16_3_2 : public RuleCheckerPPCallback {
private:
public:
  virtual void MacroDefined(const Token &MacroNameTok,
                            const MacroDirective *MD) override {
    const MacroInfo *macroInfo = MD->getMacroInfo();

    if (doIgnore(MD->getLocation())) {
      return;
    }

    for (MacroInfo::tokens_iterator I = macroInfo->tokens_begin(),
                                    E = macroInfo->tokens_end();
         I != E; ++I) {
      const std::string tokenType = I->getName();
      // Count occurrences of "hash" and "hashhash"
      if (tokenType.find("hash") == 0) {
        reportError(I->getLocation());
        break;
      }
    }
  }
};

static RuleCheckerPreprocessorRegistry::Add<Rule_16_3_2> X("16-3-2", "");
}
