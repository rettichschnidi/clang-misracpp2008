//===-  Rule_3_9_2.cpp - Checker for MISRA C++ 2008 rule 3-9-2-------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "llvm/ADT/StringExtras.h"
#include "misracpp2008.h"

using namespace clang;

namespace misracpp2008 {

class Rule_3_9_2 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_3_9_2> {
public:
  Rule_3_9_2() : RuleCheckerASTContext() {}

  bool VisitVarDecl(const VarDecl *D) {
    // Bail out early if this location should not be checked.
    if (doIgnore(D->getLocation())) {
      return true;
    }

    const QualType qualType = D->getType();
    // Bail out if this type is either an enum or does not look like a real
    // value.
    if (qualType->isEnumeralType() || qualType->isBooleanType() ||
        qualType->isArithmeticType() == false) {
      return true;
    }

    const Type *t = qualType.getTypePtrOrNull();
    assert(t && "Type of arithmetic types has to be available.");
    const std::string typeName = qualType.getAsString();
    // If it is of the same type as "size_t" and does have "size_t" somewhere in
    // its name we can go with it.
    // Please note: This also allows a typedef for "unsigned long" to be named
    // e.g. "size_type" without any size indicator - which may or may not be a
    // good thing.
    if (context->hasSameUnqualifiedType(qualType, context->getSizeType()) &&
        typeName.find("size_t") != std::string::npos) {
      return true;
    }

    // char_t and wchar_t are not subject to this rule.
    const std::string needle = "char_t";
    if (std::equal(needle.rbegin(), needle.rend(), typeName.rbegin())) {
      return true;
    }

    const uint64_t typeSize = context->getTypeSize(t);
    const std::string sizeStr = llvm::utostr(typeSize);
    // For all remaining types, the number of occupied bits must be embedded in
    // the typename.
    if (typeName.rfind(sizeStr) == std::string::npos) {
      reportError(D->getLocation());
    }

    return true;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_3_9_2> X("3-9-2", "");
}
