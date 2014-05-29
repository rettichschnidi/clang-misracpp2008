//===-  misracpp2008.cpp - A MISRA C++ 2008 rules checker------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the logic for registering and running MISRA C++ 2008
// rules checkers.
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/CompilerInstance.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/StringExtras.h"
#include <cassert>
#include <map>
#include <set>
#include <sstream>
#include <utility>

using namespace clang;
using namespace llvm;

namespace misracpp2008 {

std::set<std::string> &Consumer::getEnabledCheckers() {
  static std::set<std::string> enabledCheckers;
  return enabledCheckers;
}

Consumer::DiagLevelMap &Consumer::getDiagnosticLevels() {
  static DiagLevelMap diagLevelMap;
  return diagLevelMap;
}

bool Consumer::enableChecker(const std::string &name,
                             clang::DiagnosticsEngine::Level diagLevel) {
  getDiagnosticLevels().insert(std::make_pair(name, diagLevel));
  getEnabledCheckers().insert(name);
  return true;
}

void Consumer::dumpRegisteredCheckers(raw_ostream &OS) {}

void Consumer::dumpRequestedCheckers(raw_ostream &OS) {}

Consumer::Consumer() {}

void Consumer::HandleTranslationUnit(ASTContext &ctx) {
  // Dump the available and activated checkers
  Consumer::dumpRegisteredCheckers(llvm::outs());
  Consumer::dumpRequestedCheckers(llvm::outs());

  // Iterate over all activated ASTContext checkers and execute them
  const auto &enabledCheckers = getEnabledCheckers();
  for (RuleCheckerASTContextRegistry::iterator
       it = RuleCheckerASTContextRegistry::begin(),
       ie = RuleCheckerASTContextRegistry::end();
       it != ie; ++it) {
    const std::string checkerName = RuleCheckerASTContextRegistry::traits::nameof(*it);
    assert(checkerName.size() >= 5 && checkerName.size() <= 6 &&
           "Each checkers has to have its rule number as name");
    if(enabledCheckers.count(checkerName) > 0) {
      auto diagLevel = getDiagnosticLevels().at(checkerName);
      auto instance = it->instantiate();
      instance->setContext(ctx);
      instance->setDiagLevel(diagLevel);
      instance->doWork();
    }
  }
}

ASTConsumer *Action::CreateASTConsumer(CompilerInstance &CI, llvm::StringRef) {
  return new Consumer();
}

bool Action::ParseArgs(const CompilerInstance &CI,
                       const std::vector<std::string> &args) {
  for (unsigned i = 0, e = args.size(); i != e; ++i) {
    // Handle help request
    if (args[i] == "help") {
      PrintHelp(llvm::outs());
      return false;
    }
    std::istringstream ss(args[i]);
    std::string token;
    while (std::getline(ss, token, ',')) {
      DiagnosticsEngine::Level diagLevel;
      if (token.find("--") == 0) {
        token.erase(0, 2);
        diagLevel = DiagnosticsEngine::Remark;
      } else if (token.find('-') == 0) {
        token.erase(0, 1);
        diagLevel = DiagnosticsEngine::Warning;
      } else {
        diagLevel = DiagnosticsEngine::Error;
      }
      if (Consumer::enableChecker(token, diagLevel) == false) {
        llvm::errs() << "Unknown checker: " << token << "\n";
        Consumer::dumpRegisteredCheckers(llvm::errs());
        return false;
      }
    }
  }

  return true;
}

void Action::PrintHelp(llvm::raw_ostream &ros) {
  ros << "Enable rules: [rule[,rule[,...]]]\n";
  ros << "Example for enabling the rules 0-1-8 and 0-1-9: 0-1-8,0-1-9\n";
  ros << "Prefixing a rule number with dashes allows to downgrad a specific"
         " rule to become a warning (one dash) or a remark (two dashes).\n";
}

static FrontendPluginRegistry::Add<Action> X("misra.cpp.2008",
                                             "MISRA C++ 2008");

void RuleCheckerASTContext::setContext(ASTContext &context) {
  this->context = &context;
  this->diagEngine = &context.getDiagnostics();
}

void RuleCheckerASTContext::setDiagLevel(DiagnosticsEngine::Level diagLevel) {
  this->diagLevel = diagLevel;
}

RuleCheckerASTContext::RuleCheckerASTContext()
    : context(nullptr), diagEngine(nullptr),
      diagLevel(DiagnosticsEngine::Error) {}

void RuleCheckerASTContext::doWork() {
  assert(context && "The context has to be set before calling this function.");
  assert(diagEngine);
}
}
