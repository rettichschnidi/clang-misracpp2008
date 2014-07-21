//===-  misracpp2008.cpp - A MISRA C++ 2008 rules checker------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
// Copyright (C) 2014 Reto Schneider <code@reto-schneider.ch>
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
#include "clang/Lex/Preprocessor.h"
#include <cassert>
#include <map>
#include <set>
#include <sstream>
#include <utility>
#include <string>

using namespace clang;
using namespace llvm;

namespace misracpp2008 {

typedef std::map<std::string, clang::DiagnosticsEngine::Level> DiagLevelMap;
DiagLevelMap &getDiagnosticLevels();
std::set<std::string> &getEnabledCheckers();
std::set<std::string> getRegisteredCheckers();
bool enableChecker(const std::string &name,
                   clang::DiagnosticsEngine::Level diagLevel);
void dumpRegisteredCheckers(llvm::raw_ostream &OS);
void dumpActiveCheckers(llvm::raw_ostream &OS);

RuleChecker::RuleChecker()
    : diagEngine(nullptr), diagLevel(DiagnosticsEngine::Error),
      doIgnoreSystemHeaders(true) {}

void RuleChecker::setDiagLevel(DiagnosticsEngine::Level diagLevel) {
  this->diagLevel = diagLevel;
}

void RuleChecker::setDiagEngine(DiagnosticsEngine &diagEngine) {
  this->diagEngine = &diagEngine;
}

bool RuleChecker::isInSystemHeader(clang::SourceLocation loc) {
  const SourceManager &sourceManager = diagEngine->getSourceManager();
  return sourceManager.isInSystemHeader(loc);
}

bool RuleChecker::isBuiltIn(clang::SourceLocation loc) {
  const SourceManager &sourceManager = diagEngine->getSourceManager();
  const char *const filename = sourceManager.getPresumedLoc(loc).getFilename();
  return (strcmp(filename, "<built-in>") == 0);
}

bool RuleChecker::isCommandLine(clang::SourceLocation loc) {
  const SourceManager &sourceManager = diagEngine->getSourceManager();
  const char *const filename = sourceManager.getPresumedLoc(loc).getFilename();
  return (strcmp(filename, "<command line>") == 0);
}

bool RuleChecker::doIgnore(clang::SourceLocation loc) {
  if (isBuiltIn(loc)) {
    return true;
  }
  if (isCommandLine(loc)) {
    return true;
  }
  if (isInSystemHeader(loc)) {
    return doIgnoreSystemHeaders;
  }
  return false;
}

std::set<std::string> &getEnabledCheckers() {
  static std::set<std::string> enabledCheckers;
  return enabledCheckers;
}

DiagLevelMap &getDiagnosticLevels() {
  static DiagLevelMap diagLevelMap;
  return diagLevelMap;
}

bool enableChecker(const std::string &checkerName,
                   clang::DiagnosticsEngine::Level diagLevel) {
  if (getRegisteredCheckers().count(checkerName) == 0) {
    return false;
  }
  auto &checkerDiagLevelMap = getDiagnosticLevels();
  checkerDiagLevelMap[checkerName] = diagLevel;
  getEnabledCheckers().insert(checkerName);
  return true;
}

void dumpRegisteredCheckers(raw_ostream &OS) {
  OS << "Registered checks: ";
  for (const auto &checkerName : getRegisteredCheckers()) {
    OS << checkerName << ", ";
  }
  OS << "\n";
}

void dumpActiveCheckers(raw_ostream &OS) {
  OS << "Active checks: ";
  for (const auto &checkerName : getEnabledCheckers()) {
    OS << checkerName << ",";
  }
  OS << "\n";
}

class Consumer : public clang::ASTConsumer {
public:
  Consumer() {}
  virtual void HandleTranslationUnit(clang::ASTContext &ctx) {
    // Iterate over registered ASTContext checkers and execute the ones active
    const auto &enabledCheckers = getEnabledCheckers();
    for (RuleCheckerASTContextRegistry::iterator
             it = RuleCheckerASTContextRegistry::begin(),
             ie = RuleCheckerASTContextRegistry::end();
         it != ie; ++it) {
      const std::string checkerName =
          RuleCheckerASTContextRegistry::traits::nameof(*it);
      assert(checkerName.size() >= 5 && checkerName.size() <= 6 &&
             "Each checkers has to have its rule number as name");
      if (enabledCheckers.count(checkerName) > 0) {
        auto diagLevel = getDiagnosticLevels().at(checkerName);
        auto instance = it->instantiate();
        instance->setContext(ctx);
        instance->setDiagLevel(diagLevel);
        instance->doWork();
      }
    }
  }
};

class Action : public clang::PluginASTAction {
protected:
  clang::ASTConsumer *CreateASTConsumer(clang::CompilerInstance &CI,
                                        llvm::StringRef) {
    // Dump the available and activated checkers
    dumpRegisteredCheckers(llvm::outs());
    dumpActiveCheckers(llvm::outs());

    // Iterate over registered preprocessor checkers and execute the ones active
    const auto &enabledCheckers = getEnabledCheckers();
    for (RuleCheckerPreprocessorRegistry::iterator
             it = RuleCheckerPreprocessorRegistry::begin(),
             ie = RuleCheckerPreprocessorRegistry::end();
         it != ie; ++it) {
      const std::string checkerName =
          RuleCheckerPreprocessorRegistry::traits::nameof(*it);
      assert(checkerName.size() >= 5 && checkerName.size() <= 6 &&
             "Each checkers has to have its rule number as name");
      if (enabledCheckers.count(checkerName) > 0) {
        assert(CI.hasPreprocessor() &&
               "Compiler instance has no preprocessor!");
        auto diagLevel = getDiagnosticLevels().at(checkerName);
        std::unique_ptr<RuleCheckerPreprocessor> ppCallback = it->instantiate();
        ppCallback->setDiagLevel(diagLevel);
        ppCallback->setDiagEngine(CI.getDiagnostics());
        CI.getPreprocessor().addPPCallbacks(ppCallback.release());
      }
    }
    return new Consumer();
  }

  bool ParseArgs(const clang::CompilerInstance &CI,
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
        if (token == "all") {
          for (const auto &checkerName : getRegisteredCheckers()) {
            if (enableChecker(checkerName, diagLevel) == false) {
              assert(false &&
                     "Registered checkers have to be enabled successfully.");
            }
          }
        } else if (enableChecker(token, diagLevel) == false) {
          llvm::errs() << "Unknown checker: " << token << "\n";
          dumpRegisteredCheckers(llvm::errs());
          return false;
        }
      }
    }
    return true;
  }
  void PrintHelp(llvm::raw_ostream &ros) {
    ros << "Enable rules: [rule[,rule[,...]]]\n";
    ros << "Example for enabling the rules 0-1-8 and 0-1-9: 0-1-8,0-1-9\n";
    ros << "Prefixing a rule number with dashes allows to downgrad a specific"
           " rule to become a warning (one dash) or a remark (two dashes).\n";
    ros << "Instead of a specific rule, it is also possible to use \"all\" to "
           "enable all available checkers at once.\n";
  }
};

static FrontendPluginRegistry::Add<Action> X("misra.cpp.2008",
                                             "MISRA C++ 2008");

void RuleCheckerASTContext::setContext(ASTContext &context) {
  this->context = &context;
  this->diagEngine = &context.getDiagnostics();
}

RuleCheckerASTContext::RuleCheckerASTContext()
    : RuleChecker(), context(nullptr) {}

void RuleCheckerASTContext::doWork() {
  assert(context && "The context has to be set before calling this function.");
  assert(diagEngine);
}

RuleCheckerPreprocessor::RuleCheckerPreprocessor()
    : RuleChecker(), PPCallbacks() {}

std::set<std::string> getRegisteredCheckers() {
  std::set<std::string> registeredCheckers;

  for (RuleCheckerASTContextRegistry::iterator
           it = RuleCheckerASTContextRegistry::begin(),
           ie = RuleCheckerASTContextRegistry::end();
       it != ie; ++it) {
    const std::string checkerName =
        RuleCheckerASTContextRegistry::traits::nameof(*it);
    registeredCheckers.insert(checkerName);
  }
  for (RuleCheckerPreprocessorRegistry::iterator
           it = RuleCheckerPreprocessorRegistry::begin(),
           ie = RuleCheckerPreprocessorRegistry::end();
       it != ie; ++it) {
    const std::string checkerName =
        RuleCheckerPreprocessorRegistry::traits::nameof(*it);
    registeredCheckers.insert(checkerName);
  }

  return registeredCheckers;
}
}
