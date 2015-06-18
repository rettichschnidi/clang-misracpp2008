//===-  Rule_2_13_3.cpp - Checker for MISRA C++ 2008 rule 2-13-3-----------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Lex/Lexer.h"
#include "llvm/ADT/APInt.h"
#include "misracpp2008.h"
#include <algorithm>
#include <sstream>

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

    if (isUnsignedIntegerLiteral(il)) {
      dealWithUnsignedInteger(il);
    }

    return true;
  }

  bool VisitImplicitCastExpr(const ImplicitCastExpr *Node) {
    // Bail out early if this location should not be checked
    if (doIgnore(Node->getLocStart())) {
      return true;
    }

    const IntegerLiteral *il = dyn_cast<IntegerLiteral>(Node->getSubExpr());
    // Bail out if this node is not an integer literal beeing casted
    if (!il) {
      return true;
    }

    // Bail out if the source is already an unsigned integer
    if (isUnsignedIntegerLiteral(il)) {
      return true;
    }

    // Bail out if this is not an integer to integer casting operation
    if (Node->getCastKind() != CK_IntegralCast) {
      return true;
    }

    // Bail out if the integer simply gets truncated to a smaller integral type
    // of the same signedness
    if (Node->getSubExpr()->getType()->isSignedIntegerOrEnumerationType() ==
        Node->getType()->isSignedIntegerOrEnumerationType()) {
      return true;
    }

    // Figure out if the parent is an explicit casting operation which would
    // legalizes this implicit one.
    const auto &parents = context->getParents(*Node);
    assert(parents.size() == 1 && "Expect exactly one parent node.");

    // Bail out if this is not the first if in a if...else-if clause
    if (parents[0].get<ExplicitCastExpr>() != nullptr) {
      return true;
    }

    // At this point we can be fairly sure that this casting is the result of
    // a rule violation.
    reportError(il->getLocation());
    return true;
  }

private:
  static bool isUnsignedType(const CastExpr *ce) {
    if (const Type *type = ce->getType().getTypePtrOrNull()) {
      return type->isSignedIntegerType() == false;
    }
    assert(false &&
           "The argument to this function is expected to have a type defined.");
    return true;
  }

  bool isUnsignedIntegerLiteral(const IntegerLiteral *il) {
    llvm::APSInt result;
    il->EvaluateAsInt(result, *context, Expr::SE_NoSideEffects);
    return result.isUnsigned();
  }

  /// \brief Make sure the suffix 'U' exists.
  /// \param il Unsigned integer literal.
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
