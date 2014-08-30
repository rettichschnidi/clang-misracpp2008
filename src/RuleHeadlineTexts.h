#ifndef RULE_HEADLINE_TEXTS_H
#define RULE_HEADLINE_TEXTS_H

//===-  RuleHeadlineTexts.h - MISRA C++:2008 rule headlines----------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
// Copyright (C) 2014 Reto Schneider <code@reto-schneider.ch>
//
//===----------------------------------------------------------------------===//

#include <map>
#include <string>

namespace misracpp2008 {

typedef std::map<std::string, std::string> RuleHeadlineMap;

/// \brief Map containing the headline of each MISRA C++ 2008 rule.
extern const RuleHeadlineMap ruleHeadlines;
}

#endif // RULE_HEADLINE_TEXTS_H
