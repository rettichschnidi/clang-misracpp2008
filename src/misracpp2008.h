//===-  misracpp2008.h - A MISRA C++ 2008 rules checker--------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef MISRA_CPP_2008_H
#define MISRA_CPP_2008_H

#include "clang/Basic/Diagnostic.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Frontend/CompilerInstance.h"
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
  clang::CompilerInstance *CI =
      nullptr; ///< Access to the current compiler instance. Rule checkers can
               ///assume this pointer to direct the correct instance.
  clang::DiagnosticsEngine::Level diagLevel =
      clang::DiagnosticsEngine::Error; ///< Level of the emited diagnostic in
                                       ///case of a
                                       ///  violation.
  bool doIgnoreSystemHeaders = true;   ///< Should we skip the system headers?
  std::string name = "?";              ///< Name of rule this checker enforces.
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
  /**
   * @brief Check if the element at \c loc should be ignored. Compiler-built-in
   * or command-line-specified code most likely should not be checked. Also,
   * code from the system headers is probably not even close to MISRA conformity
   * and has to be excluded as well.
   * @param loc Location to evaluate.
   * @return True if \c loc should be ignored (not checked), false if not.
   */
  bool doIgnore(clang::SourceLocation loc);
  /**
   * @brief Auxiliary helper function for derived checkers to report an error.
   * @param loc The location to be displayed to the user.
   */
  void reportError(clang::SourceLocation loc);

  /**
   * @brief Function for derived checkers to report an arbitrary error.
   * @param loc The location to be displayed to the user.
   * @param FormatString Error string. May contain place holders %0, %1, etc.
   * @return clang::DiagnosticBuilder, to be fed with values for the place
   * holders.
   */
  template <unsigned N>
  clang::DiagnosticBuilder reportError(clang::SourceLocation loc,
                                       const char (&FormatString)[N]) {
    clang::DiagnosticsEngine &diagEngine = CI->getDiagnostics();
    unsigned diagId = diagEngine.getCustomDiagID(diagLevel, FormatString);
    return diagEngine.Report(loc, diagId);
  }

public:
  virtual ~RuleChecker() {}
  /**
   * @brief Set the level of the diagnostic to be used when a violation gets
   * reported.
   * @param diagLevel New diagnostic level.
   */
  void setDiagLevel(clang::DiagnosticsEngine::Level diagLevel);
  /**
   * @brief Rule name to be printed in case of a violation.
   * @param name Name of the rule, e.g. "6-2-1".
   */
  void setName(const std::string &name);
  /**
   * @brief Set the compiler instsance to be used when a violation gets
   * reported.
   * @param CI Compiler instance to be used by the checker.
   */
  void setCompilerInstance(clang::CompilerInstance &CI);
};

/**
 * @brief Base class for all rule checkers that work on the AST.
 */
class RuleCheckerASTContext : public virtual RuleChecker {
protected:
  clang::ASTContext *context; ///< AST context of the translation unit to be
                              /// checked.
  RuleCheckerASTContext();
  /**
   * @brief Extract the source code of the token pointed at by \c start.
   * @param start Starting location of the token to extract.
   * @return String with the source code for token starting at \c start.
   */
  std::string srcLocToString(const clang::SourceLocation start);

public:
  /**
   * @brief Set the AST context to be working on when calling doWork().
   * @param context New AST context to be used by this instance.
   */
  void setContext(clang::ASTContext &context);
  /**
   * @brief To be implemented by derived classes.
   */
  virtual void doWork() = 0;
};

/**
 * @brief A global registry to register RuleCheckerASTContext-derived checkers.
 */
typedef llvm::Registry<RuleCheckerASTContext> RuleCheckerASTContextRegistry;

/**
 * @brief Base class for all rule checkers that work on the preprocessing stage.
 */
class RuleCheckerPPCallback : public virtual RuleChecker,
                              public clang::PPCallbacks {};

/**
 * @brief A global registry to register RuleCheckerPreprocessor-derived
 * checkers.
 */
typedef llvm::Registry<RuleCheckerPPCallback> RuleCheckerPreprocessorRegistry;
}

#endif
