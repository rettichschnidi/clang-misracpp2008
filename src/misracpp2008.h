//===-  misracpp2008.h - A MISRA C++ 2008 rules checker--------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
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
#include "clang/AST/RecursiveASTVisitor.h"

namespace clang {
class CompilerInstance;
class ASTConsumer;
class IdentifierTable;
class ASTContext;
}

namespace llvm {
class raw_ostream;
}

namespace misracpp2008 {

class RuleChecker {
protected:
  explicit RuleChecker(clang::ASTContext &context);
  clang::ASTContext &context;

public:
  virtual ~RuleChecker();
  virtual void doWork() = 0;
};

class RuleCheckerFactoryBase {
public:
  typedef std::shared_ptr<RuleChecker> SpRuleChecker;
  virtual SpRuleChecker create(clang::ASTContext &context) = 0;
  virtual ~RuleCheckerFactoryBase() {}
};

template <typename RuleCheckerType>
class RuleCheckerCreatorFactory : public RuleCheckerFactoryBase {
  virtual SpRuleChecker create(clang::ASTContext &context) {
    RuleChecker *p = new RuleCheckerType(context);
    return SpRuleChecker(p);
  }
};

class Consumer : public clang::ASTConsumer {
private:
  typedef std::map<std::string, std::shared_ptr<RuleCheckerFactoryBase>>
  RegCheckersMap;
  static RegCheckersMap &getRegisteredCheckers();
  static std::set<std::string> &getEnabledCheckers();

public:
  Consumer();
  virtual void HandleTranslationUnit(clang::ASTContext &ctx);
  static void dumpRegisteredCheckers(llvm::raw_ostream &OS);
  static void dumpRequestedCheckers(llvm::raw_ostream &OS);
  static void registerChecker(const std::string &name,
                              std::shared_ptr<RuleCheckerFactoryBase> factory);
  static bool enableChecker(const std::string &name);

  class RegisterChecker {
  public:
    RegisterChecker(const std::string &name,
                    std::shared_ptr<RuleCheckerFactoryBase> factory) {
      Consumer::registerChecker(name, factory);
    }
  };
};

class Action : public clang::PluginASTAction {
protected:
  clang::ASTConsumer *CreateASTConsumer(clang::CompilerInstance &CI,
                                        llvm::StringRef);
  bool ParseArgs(const clang::CompilerInstance &CI,
                 const std::vector<std::string> &args);
  void PrintHelp(llvm::raw_ostream &ros);
};
}

#endif
