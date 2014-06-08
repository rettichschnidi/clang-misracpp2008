//===-  Rule_17_0_5.cpp - Checker for MISRA C++ 2008 rule 17-0-5 ----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "BannedFunctionUsageChecker.h"

using namespace clang;

namespace misracpp2008 {

static std::string ruleName = "17-0-5";

class Rule_17_0_5 : public BannedFunctionUsageChecker {
private:
  static const std::set<std::string> illegalFunction;

protected:
  virtual const std::set<std::string> &getIllegalFunctions() const {
    return illegalFunction;
  }
  virtual void reportRuleViolation(SourceLocation loc) {
    RuleChecker::reportError(
        "The setjmp macro and the longjmp function shall not be used.", loc);
  }
};

const std::set<std::string> Rule_17_0_5::illegalFunction = {"longjmp",
                                                            "setjmp"};

static RuleCheckerASTContextRegistry::Add<Rule_17_0_5>
X(ruleName.c_str(), "MISRA C++ 2008 rule checker");
static RuleCheckerPreprocessorRegistry::Add<Rule_17_0_5>
Y(ruleName.c_str(), "MISRA C++ 2008 rule checker");
}
