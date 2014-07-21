//===-  misracpp2008.h - A MISRA C++ 2008 rules checker--------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
// Copyright (C) 2014 Reto Schneider <code@reto-schneider.ch>
//
//===----------------------------------------------------------------------===//

#ifndef MISRA_CPP_2008_H
#define MISRA_CPP_2008_H

#include <map>
#include <set>
#include <string>
#include <memory>
#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Lex/PPCallbacks.h"
#include "llvm/Support/Registry.h"
#include "RuleHeadlineTexts.h"

namespace clang {
class CompilerInstance;
class IdentifierTable;
class ASTContext;
}

namespace llvm {
class raw_ostream;
}

namespace misracpp2008 {

class RuleChecker {
protected:
  clang::DiagnosticsEngine *diagEngine;
  clang::DiagnosticsEngine::Level diagLevel;
  bool doIgnoreSystemHeaders;
  RuleChecker();
  bool isInSystemHeader(clang::SourceLocation loc);
  bool isBuiltIn(clang::SourceLocation loc);
  bool isCommandLine(clang::SourceLocation loc);

public:
  virtual ~RuleChecker() {}
  void setDiagLevel(clang::DiagnosticsEngine::Level diagLevel);
  void setDiagEngine(clang::DiagnosticsEngine &diagEngine);
  bool doIgnore(clang::SourceLocation loc);
  template <unsigned N>
  void reportError(const char (&FormatString)[N], clang::SourceLocation loc) {
    unsigned diagID = diagEngine->getCustomDiagID(diagLevel, FormatString);
    diagEngine->Report(loc, diagID);
  }
};

class RuleCheckerASTContext : public virtual RuleChecker {
protected:
  clang::ASTContext *context;
  RuleCheckerASTContext();

public:
  void setContext(clang::ASTContext &context);
  virtual void doWork() = 0;
};

typedef llvm::Registry<RuleCheckerASTContext> RuleCheckerASTContextRegistry;

class RuleCheckerPreprocessor : public virtual RuleChecker,
                                public clang::PPCallbacks {
protected:
  RuleCheckerPreprocessor();

public:
  virtual ~RuleCheckerPreprocessor() {}
};

typedef llvm::Registry<RuleCheckerPreprocessor> RuleCheckerPreprocessorRegistry;

class Consumer : public clang::ASTConsumer {
public:
  Consumer() {}
  virtual void HandleTranslationUnit(clang::ASTContext &ctx);
};

class Action : public clang::PluginASTAction {
protected:
  clang::ASTConsumer *CreateASTConsumer(clang::CompilerInstance &CI,
                                        llvm::StringRef);
  bool ParseArgs(const clang::CompilerInstance &CI,
                 const std::vector<std::string> &args);
  void PrintHelp(llvm::raw_ostream &ros);
};

typedef std::map<std::string, clang::DiagnosticsEngine::Level> DiagLevelMap;
DiagLevelMap &getDiagnosticLevels();
std::set<std::string> &getEnabledCheckers();
std::set<std::string> getRegisteredCheckers();
bool enableChecker(const std::string &name,
                   clang::DiagnosticsEngine::Level diagLevel);
void dumpRegisteredCheckers(llvm::raw_ostream &OS);
void dumpActiveCheckers(llvm::raw_ostream &OS);
}

#endif
