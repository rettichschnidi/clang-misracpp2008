//===-  Rule_2_13_3.cpp - Checker for MISRA C++ 2008 rule 2-13-3-----------===//
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
#include "llvm/ADT/APInt.h"
#include "clang/Lex/Lexer.h"
#include <sstream>
#include <algorithm>

using namespace clang;

namespace misracpp2008 {

class Rule_2_13_3 : public RuleCheckerASTContext,
                    public RecursiveASTVisitor<Rule_2_13_3> {
public:
  Rule_2_13_3() : RuleCheckerASTContext() {}

  bool VisitIntegerLiteral(const IntegerLiteral *il) {
    // Bail out early if this location should not be checked
    if (doIgnore(il->getLocStart())) {
      return true;
    }

    llvm::APSInt result;
    il->EvaluateAsInt(result, *context, Expr::SE_NoSideEffects);
    // Decide which logic has to be used
    if (result.isSigned()) {
      dealWithSignedInteger(il);
    } else {
      dealWithUnsignedInteger(il);
    }

    return true;
  }

  bool TraverseStmt(Stmt *S) {
    outerScopes.push_back(S);
    RecursiveASTVisitor<Rule_2_13_3>::TraverseStmt(S);
    outerScopes.pop_back();
    return true;
  }

private:
  std::vector<Stmt *> outerScopes;

  static bool isUnsignedType(const CastExpr *ce) {
    if (const Type *type = ce->getType().getTypePtrOrNull()) {
      return type->isSignedIntegerType() == false;
    }
    assert(false);
    return true;
  }

  /**
   * @brief Make sure the signed integer literal does not get casted to
   * unsigned.
   * @param il Signed integer literal.
   * @todo Simplify this horribly 3:30AM code!
   */
  void dealWithSignedInteger(const IntegerLiteral *il) {
    assert(outerScopes.size() > 0 &&
           "At least the integer literal itself must be on the stack.");
    // Check if there is just this integral literal on the stack
    if (outerScopes.size() == 1) {
      return;
    }
    // Check if this integer gets implicitly casted right away. Any other,
    // explicit cast is is ok.
    bool isError = false;
    for (auto RI = outerScopes.rbegin(); RI != outerScopes.rend(); ++RI) {
      // Check if we have a implicit cast.
      const auto *ice = dyn_cast<ImplicitCastExpr>(*RI);
      if (!ice) {
        continue;
      }

      if (isUnsignedType(ice)) {
        isError = true;
        // There is probably an exlicit cast waiting for us which would
        // legalize the last one.
        RI++;
        if (RI == outerScopes.rend()) {
          break;
        }

        if (const auto *outerCe = dyn_cast<CastExpr>(*RI)) {
          if (isUnsignedType(outerCe)) {
            isError = false;
          }
        }
      }
      break;
    }
    if (isError) {
      reportError(il->getLocation());
    }
  }
  /**
   * @brief Make sure the suffix 'U' exists.
   * @param il Unsigned integer literal.
   */
  void dealWithUnsignedInteger(const IntegerLiteral *il) {
    // See if one char after the integer literal is a "U"
    std::string lexem = srcLocToString(il->getLocStart());
    if (lexem.rfind("U") == std::string::npos) {
      reportError(il->getLocation());
    }
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_2_13_3> X("2-13-3", "");
}
