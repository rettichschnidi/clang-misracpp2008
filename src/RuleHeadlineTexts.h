//===-  RuleHeadlineTexts.h - MISRA C++:2008 rule headlines----------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#ifndef RULE_HEADLINE_TEXTS_H
#define RULE_HEADLINE_TEXTS_H

#include <map>
#include <string>

namespace misracpp2008 {

using RuleHeadlineMap = std::map<std::string, std::string>;

/// \brief Map containing the headline of each MISRA C++ 2008 rule.
extern const RuleHeadlineMap ruleHeadlines;
}

#endif // RULE_HEADLINE_TEXTS_H
