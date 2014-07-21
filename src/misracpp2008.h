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

/**
 * @brief Base class for all rule checker implementations.
 */
class RuleChecker {
protected:
  clang::DiagnosticsEngine *diagEngine; ///< Needed to report errors. Rule
  /// checkers can assume this pointer to
  /// direct the correct instance.
  clang::DiagnosticsEngine::Level diagLevel; ///< level of the diagnostic in
  /// case of a violation.
  bool doIgnoreSystemHeaders; ///< Should we skip the system headers?
  RuleChecker();
  /**
   * @brief Check whether or not \c loc is within a system header.
   * @param loc Location within the translation unit to be tested.
   * @return True if \c loc is within a system header, false if not.
   */
  bool isInSystemHeader(clang::SourceLocation loc);
  /**
   * @brief Check whether or not \c loc is a built in, e.g. defined by the
   * compiler itself.
   * @param loc Location within the translation unit to be tested.
   * @return True if \c loc is within a built-in, false if not.
   */
  bool isBuiltIn(clang::SourceLocation loc);
  /**
   * @brief Check whether or not \c loc has been specified at the command line.
   * For example, passing -DMY_MACRO_VALUE=36 to the Clang would cause the
   * return value for the \c loc value of MY_MACRO_VALUE to be true.
   * @param loc Location within the translation unit to be tested.
   * @return True if \c loc was defined at the command line, false if not.
   */
  bool isCommandLine(clang::SourceLocation loc);

public:
  virtual ~RuleChecker() {}
  /**
   * @brief Set the level of the diagnostic to be used when a violation gets
   * reported.
   * @param diagLevel
   */
  void setDiagLevel(clang::DiagnosticsEngine::Level diagLevel);
  /**
   * @brief Set the diagnostic engine to be used when a violation gets reported.
   * @param diagEngine
   */
  void setDiagEngine(clang::DiagnosticsEngine &diagEngine);
  /**
   * @brief Check if the element at \c loc should be ignored. Compiler-built-in
   * or command-line-specified code most likely should not be checked. Also,
   * code from the system headers probably not even close to MISRA conformity
   * and have to be excluded as well.
   * @param loc
   * @return
   */
  bool doIgnore(clang::SourceLocation loc);
  template <unsigned N>
  /**
   * @brief Auxiliary helper function for derived checkers to report an error.
   * @param FormatString The error message to be displayed to the user.
   * @param loc The location to be displayed to the user.
   */
  void reportError(const char (&FormatString)[N], clang::SourceLocation loc) {
    unsigned diagID = diagEngine->getCustomDiagID(diagLevel, FormatString);
    diagEngine->Report(loc, diagID);
  }
};

/**
 * @brief Base class for all rule checkers that work on the AST.
 */
class RuleCheckerASTContext : public virtual RuleChecker {
protected:
  clang::ASTContext *context;
  RuleCheckerASTContext();

public:
  void setContext(clang::ASTContext &context);
  virtual void doWork() = 0;
};

/**
 * @brief A global registry to register RuleCheckerASTContext-derived checkers.
 */
typedef llvm::Registry<RuleCheckerASTContext> RuleCheckerASTContextRegistry;

/**
 * @brief Base class for all rule checkers that work on the preprocessing stage.
 */
class RuleCheckerPreprocessor : public virtual RuleChecker,
                                public clang::PPCallbacks {
protected:
  RuleCheckerPreprocessor();

public:
  virtual ~RuleCheckerPreprocessor() {}
};

/**
 * @brief A global registry to register RuleCheckerPreprocessor-derived checkers.
 */
typedef llvm::Registry<RuleCheckerPreprocessor> RuleCheckerPreprocessorRegistry;

}

#endif

