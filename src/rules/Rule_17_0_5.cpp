//===-  Rule_17_0_5.cpp - Checker for MISRA C++ 2008 rule 17-0-5 ----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
// Copyright (C) 2014 Reto Schneider <code@reto-schneider.ch>
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
  virtual const std::set<std::string> &getIllegalFunctions() const override {
    return illegalFunction;
  }
  virtual void reportRuleViolation(SourceLocation loc) override {
    RuleChecker::reportError(loc);
  }
};

const std::set<std::string> Rule_17_0_5::illegalFunction = { "longjmp",
                                                             "setjmp" };

static RuleCheckerASTContextRegistry::Add<Rule_17_0_5> X(ruleName.c_str(), "");
static RuleCheckerPreprocessorRegistry::Add<Rule_17_0_5> Y(ruleName.c_str(),
                                                           "");
}
