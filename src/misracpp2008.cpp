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

using namespace clang;
using namespace llvm;

namespace misracpp2008 {

Consumer::RegCheckersMap &Consumer::getRegisteredASTCheckers() {
  static RegCheckersMap registeredAstCheckers;
  return registeredAstCheckers;
}

std::set<std::string> &Consumer::getEnabledCheckers() {
  static std::set<std::string> enabledCheckers;
  return enabledCheckers;
}

void Consumer::registerCheckerASTContext(
    const std::string &name, std::shared_ptr<RuleCheckerFactoryBase> factory) {
  auto &registeredCheckers = getRegisteredASTCheckers();
  assert(
      registeredCheckers.count(name) == 0 &&
      "Registering multiple AST checkers for the same rule is not supported.");
  registeredCheckers[name] = factory;
}

bool Consumer::enableChecker(const std::string &name) {
  if (getRegisteredASTCheckers().count(name) == 0) {
    return false;
  }
  if (getEnabledCheckers().count(name) != 0) {
    return false;
  }
  getEnabledCheckers().insert(name);
  return true;
}

void Consumer::dumpRegisteredCheckers(raw_ostream &OS) {
  OS << "Registered checks: ";
  for (const auto &checker : getRegisteredASTCheckers()) {
    OS << checker.first << ",";
  }
  OS << "\n";
}

void Consumer::dumpRequestedCheckers(raw_ostream &OS) {
  OS << "Requested checks: ";
  for (const auto &checker : getEnabledCheckers()) {
    OS << checker << ",";
  }
  OS << "\n";
}

Consumer::Consumer() {}

void Consumer::HandleTranslationUnit(ASTContext &ctx) {
  Consumer::dumpRegisteredCheckers(llvm::outs());
  Consumer::dumpRequestedCheckers(llvm::outs());
  for (const std::string &checkerName : getEnabledCheckers()) {
    auto checkerFactory = getRegisteredASTCheckers().at(checkerName);
    auto checker = checkerFactory->create(ctx, clang::DiagnosticsEngine::Error);
    checker->doWork();
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
      if (Consumer::enableChecker(token) == false) {
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
}

static FrontendPluginRegistry::Add<Action> X("misra.cpp.2008",
                                             "MISRA C++ 2008");

RuleCheckerASTContext::RuleCheckerASTContext(ASTContext &context,
                                             DiagnosticsEngine::Level diagLevel)
    : context(context), diagLevel(diagLevel) {}

RuleCheckerASTContext::~RuleCheckerASTContext() {}
}
