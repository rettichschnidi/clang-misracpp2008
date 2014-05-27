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

Consumer::RegCheckersMap &Consumer::getRegisteredCheckers() {
  static RegCheckersMap registeredChecks;
  return registeredChecks;
}

std::set<std::string> &Consumer::getEnabledCheckers() {
  static std::set<std::string> enabledCheckers;
  return enabledCheckers;
}

void
Consumer::registerChecker(const std::string &name,
                          std::shared_ptr<RuleCheckerFactoryBase> factory) {
  auto &registeredCheckers = getRegisteredCheckers();
  assert(registeredCheckers.count(name) == 0 &&
         "Registering multiple checkers for the same rule is not supported.");
  registeredCheckers[name] = factory;
}

bool Consumer::enableChecker(const std::string &name) {
  if (getRegisteredCheckers().count(name) == 0) {
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
  for (const auto &checker : getRegisteredCheckers()) {
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
    auto checkerFactory = getRegisteredCheckers().at(checkerName);
    auto checker = checkerFactory->create(ctx);
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

RuleChecker::RuleChecker(ASTContext &context) : context(context) {}

RuleChecker::~RuleChecker() {}
}
