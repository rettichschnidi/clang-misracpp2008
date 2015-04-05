//===-  Rule_3_3_1.cpp - Checker for MISRA C++ 2008 rule 3-3-1-------------===//
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

class Rule_3_3_1 : public RuleCheckerASTContext,
                   public clang::RecursiveASTVisitor<Rule_3_3_1> {
public:
  Rule_3_3_1() : RuleCheckerASTContext() {}

  bool VisitDecl(Decl *D) {
    if (doIgnore(D->getLocStart())) {
      return true;
    }

    // Declarations in headers are always accepted
    if (isInMainFile(D->getLocation()) == false) {
      return true;
    }

    // The main function is allowed to be in global namespace and not having an
    // external declaration
    if (isa<FunctionDecl>(D) && static_cast<FunctionDecl *>(D)->isMain()) {
      return true;
    }

    // If linkage is strictly internal, this rule simply can not be
    // violated
    if (const VarDecl *varDecl = dyn_cast<const VarDecl>(D)) {
      if (varDecl->getFormalLinkage() <= UniqueExternalLinkage) {
        return true;
      }
    }

    // Declarations declared auto, static or in an anonymous namespace can not
    // violate this rule
    if (D->isInAnonymousNamespace() || isStorageClass<VarDecl>(D, SC_Static) ||
        isStorageClass<VarDecl>(D, SC_Auto) ||
        isStorageClass<FunctionDecl>(D, SC_Static)) {
      return true;
    }

    if (hasExternalStorageClass<FunctionDecl>(D) ||
        hasExternalStorageClass<VarDecl>(D)) {
      reportError(D->getLocation());
    }
    return true;
  }

  // At this point, if this declaration is the only declaration for this
  // function or variable, then this rule is considered violated
  template <typename DeclType> bool hasExternalStorageClass(Decl *D) {
    if (DeclType *declType = dyn_cast<DeclType>(D)) {
      if (declType->getFirstDecl() == declType) {
        return true;
      } else {
        // If there are multiple declarations for this variable or function,
        // make sure all of them are extern, either implicitly or explicitly.
        for (typename DeclType::redecl_iterator I = declType->redecls_begin();
             *I; ++I) {
          isInMainFile(I->getLocation());
        }
      }
    }
    return false;
  }

  template <typename DeclType>
  bool isStorageClass(const Decl *D, const StorageClass sc) {
    if (const DeclType *subClsObj = dyn_cast<const DeclType>(D)) {
      return subClsObj->getStorageClass() == sc;
    }
    return false;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());
  }
};

static RuleCheckerASTContextRegistry::Add<Rule_3_3_1> X("3-3-1", "");
}
