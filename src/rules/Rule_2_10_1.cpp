//===-  Rule_2_10_1.cpp - Checker for MISRA C++ 2008 rule 2-10-1-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "misracpp2008.h"
#include <algorithm>
#include <cstring>
#include <functional>
#include <locale>
#include <map>
#include <string>

using namespace clang;
using std::string;

namespace misracpp2008 {

class Rule_2_10_1 : public RuleCheckerASTContext,
                    public RecursiveASTVisitor<Rule_2_10_1> {
public:
  Rule_2_10_1() : RuleCheckerASTContext() {}

  bool TraverseDecl(Decl *D) {
    const DeclContext *DC = dyn_cast_or_null<DeclContext>(D);
    const bool isNewContext = DC && !DC->isTransparentContext();

    if (isNewContext) {
      str2decls.emplace_back(Str2Decls());
    }

    const bool retVal = RecursiveASTVisitor<Rule_2_10_1>::TraverseDecl(D);

    if (isNewContext) {
      str2decls.pop_back();
    }

    return retVal;
  }

  bool VisitNamedDecl(const NamedDecl *D) {
    if (doIgnore(D->getLocation())) {
      return true;
    }

    assert(!str2decls.empty() &&
           "At least one DeclContext must be on the stack!");

    // If the decl has no name, no collision can happen. Bail out.
    // This may be the case for constructs like this:
    // typedef struct { int i; } MyStruct;
    if (!D->getIdentifier() || D->getName().empty()) {
      return true;
    }

    // FunctionDecl which belong to a FunctionTemplateDecl should not be
    // checked separately
    if (const FunctionDecl *FD = dyn_cast<FunctionDecl>(D)) {
      if (FD->getTemplatedKind() != FunctionDecl::TK_NonTemplate) {
        return true;
      }
    }

    const string fullQualIdent = D->getQualifiedNameAsString();
    const string normalizedIdent = normalizeIdent(fullQualIdent);

    bool reportedError = false;
    for (const Str2Decls &s2d : str2decls) {
      auto lookalikeIdentifiers = s2d.equal_range(normalizedIdent);
      // Add notes about ambiguous identifiers
      for (Str2Decls::const_iterator I = lookalikeIdentifiers.first;
           I != lookalikeIdentifiers.second; ++I) {
        const NamedDecl *previousNamedDecl = I->second;
        // Do not report errors on identifiers with exact the same name, e.g.
        // overloads
        if (previousNamedDecl->getName() == D->getName()) {
          continue;
        }
        // Report error just once, even when multiple typographically close
        // identifiers are in one of the parent decl contextes.
        if (!reportedError) {
          reportError(D->getLocation());
          reportedError = true;
        }
        report(previousNamedDecl->getLocation(),
               "Typographically too close to '%0'",
               clang::DiagnosticsEngine::Note)
            << D->getName();
      }
    }

    str2decls.back().insert(std::make_pair(normalizedIdent, D));

    return true;
  }

private:
  const std::vector<std::pair<string, string>> replaceMap = {
      {"RN", "M"}, // rn (string) to m (letter)
      {"O", "0"},  // O (letter) to 0 (number)
      {"L", "1"},  // l (letter) to 1 (number)
      {"I", "1"},  // I (letter) to 1 (number)
      {"S", "5"},  // S (letter) to 5 (number)
      {"Z", "2"},  // Z (letter) to 2 (number)
      {"N", "H"},  // n (letter) to h (number)
      {"B", "8"},  // B (letter) to 8 (number)
      {"_", ""}    // remove the underscore
  };
  using Str2Decls = std::multimap<string, const NamedDecl *>;
  std::vector<Str2Decls> str2decls;

  static void replaceSubStr(string &str, const string &from, const string &to) {
    for (string::size_type pos = str.find(from); pos != string::npos;
         pos = str.find(from)) {
      str.replace(pos, from.length(), to);
    }
  }

  string normalizeIdent(const string inputStr) {
    string preparedString;
    // Make string uppercase
    std::transform(inputStr.begin(), inputStr.end(),
                   std::back_inserter(preparedString),
                   std::bind(&std::toupper<string::value_type>,
                             std::placeholders::_1, std::locale()));

    // Apply substitutions
    for (const auto &replace : replaceMap) {
      const string &from = replace.first;
      const string &to = replace.second;
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

static RuleCheckerASTContextRegistry::Add<Rule_2_10_1> X("2-10-1", "");
}
