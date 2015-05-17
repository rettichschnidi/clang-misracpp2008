//===-  Rule_3_9_1.cpp - Checker for MISRA C++ 2008 rule 3-9-1-------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang;

namespace misracpp2008 {

class Rule_3_9_1 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_3_9_1> {
public:
  Rule_3_9_1() : RuleCheckerASTContext() {}

  bool VisitFunctionDecl(const FunctionDecl *D) {
    if (doIgnore(D->getLocStart())) {
      return true;
    }

    // Do this check only once per declaration, regardless of how many
    // redeclarations are around
    if (D->isCanonicalDecl() == false) {
      return true;
    }

    D->dump();
    reportReturnValueViolations(D);

    unsigned numParams = D->getNumParams();
    for (auto R : D->redecls()) {
      for (unsigned int i = 0; i < numParams; i++) {
        const ParmVarDecl *c = D->getParamDecl(i);
        const ParmVarDecl *r = R->getParamDecl(i);
        const Type *cc = c->getType().getTypePtrOrNull();
        const Type *rr = r->getType().getTypePtrOrNull();
        cc->dump();
        c->dump();
        r->
        llvm::outs() << "vs\n";
        rr->dump();
        r->dump();
        llvm::outs() << "\n";
      }
    }
    return true;
  }

private:
  void reportReturnValueViolations(const FunctionDecl *D) {
    const Type *canonicalType = D->getReturnType().getTypePtrOrNull();
    bool foundError = false;
    assert(canonicalType);

    for (auto R : D->redecls()) {
      const Type *peeledType = extractUnelaboratedType(R->getReturnType());

      if (peeledType != canonicalType) {
        reportError(R->getLocation());
        foundError = true;
      }
    }
    if (foundError) {
      reportError(D->getLocation(), "Canonical declaration.");
    }
  }

  // Peel off the elaborated type to make this code work for return types
  // which are defined within nested contexes (within a class for example).
  const Type *extractUnelaboratedType(const QualType qualType) {
    const Type *retVal = qualType.getTypePtrOrNull();
    if (const auto et = dyn_cast<ElaboratedType>(retVal)) {
      retVal = et->getNamedType().getTypePtrOrNull();
    }
    assert(retVal);
    return retVal;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_3_9_1> X("3-9-1", "");
}
