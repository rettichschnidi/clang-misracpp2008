//===-  Rule_2_10_1.cpp - Checker for MISRA C++ 2008 rule 2-10-1-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
// Copyright (C) 2014 Reto Schneider <code@reto-schneider.ch>
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/Diagnostic.h"
#include <map>
#include <string>
#include <cstring>
#include <algorithm>
#include <functional>

using namespace clang;

namespace misracpp2008 {

class Rule_2_10_1 : public RuleCheckerASTContext,
                    public RecursiveASTVisitor<Rule_2_10_1> {
public:
  Rule_2_10_1() : RuleCheckerASTContext() {}

  bool VisitDecl(const Decl *D) {
    if (doIgnore(D->getLocation())) {
      return true;
    }
    if (const NamedDecl *nd = dyn_cast<NamedDecl>(D)) {
      const std::string ident = nd->getNameAsString();
      const std::string typoUniqIdent = makeTypoUnique(ident);
      if (uniqueIdents.count(typoUniqIdent) != 0) {
        reportError(nd->getLocation());
      }
      uniqueIdents.insert(std::make_pair(typoUniqIdent, nd));
    }
    return true;
  }

private:
  std::vector<std::pair<std::string, std::string> > replaceMap = {
    { "RN", "M" }, // rn (string) to m (letter)
    { "O", "0" },  // O (letter) to 0 (number)
    { "L", "1" },  // l (letter) to 1 (number)
    { "I", "1" },  // I (letter) to 1 (number)
    { "S", "5" },  // S (letter) to 5 (number)
    { "Z", "2" },  // Z (letter) to 2 (number)
    { "N", "H" },  // n (letter) to h (number)
    { "B", "8" },  // B (letter) to 8 (number)
    { "_", "" }    // remove the underscore
  };
  std::multimap<std::string, const Decl *> uniqueIdents;

  static void replaceSubStr(std::string &str, const std::string &from,
                            const std::string &to) {
    for (std::string::size_type pos = str.find(from); pos != std::string::npos;
         pos = str.find(from)) {
      str.replace(pos, from.length(), to);
    }
  }

  std::string makeTypoUnique(const std::string inputStr) {
    std::string preparedString;
    // Make string uppercase
    std::transform(inputStr.begin(), inputStr.end(),
                   std::back_inserter(preparedString), toupper);

    // Apply substitutions
    for (const auto &replace : replaceMap) {
      const std::string &from = replace.first;
      const std::string &to = replace.second;
      replaceSubStr(preparedString, from, to);
    }

    return preparedString;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_2_10_1> X("2-10-1",
                                                         RULE_TEXT_2_10_1);
}
