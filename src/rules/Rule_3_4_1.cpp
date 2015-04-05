//===-  Rule_3_4_1.cpp - Checker for MISRA C++ 2008 rule 3-4-1-------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "misracpp2008.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/Diagnostic.h"
#include <map>

using namespace clang;

namespace misracpp2008 {

class Rule_3_4_1 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_3_4_1> {
public:
  Rule_3_4_1() : RuleCheckerASTContext() {}

  bool VisitDeclRefExpr(DeclRefExpr *D) {
    if (doIgnore(D->getLocation())) {
      return true;
    }

    assert(m_CurDeclContext.size() > 0 &&
           "Visit* must be called after Traverse*");
    m_varDecls.insert(std::make_pair(D->getDecl(), m_CurDeclContext.top()));

    return true;
  }

  bool TraverseDecl(Decl *D) {
    if (D) {
      DeclContext *dc = D->getDeclContext();
      m_CurDeclContext.push(dc);
      RecursiveASTVisitor<Rule_3_4_1>::TraverseDecl(D);
      m_CurDeclContext.pop();
    }
    return true;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());

    for (ValRefMapType::const_iterator I = m_varDecls.cbegin(),
                                       keyE = m_varDecls.cend();
         I != keyE;) {
      const ValueDecl *valDecl = I->first;
      const DeclContext *valDeclCtx = valDecl->getDeclContext();

      bool hasUsageInValDeclCtx = false;
      for (ValRefMapType::const_iterator valueE =
               m_varDecls.upper_bound(I->first);
           I != valueE; ++I) {
        const DeclContext *usageContext = I->second;
        if (valDeclCtx->Equals(usageContext)) {
          hasUsageInValDeclCtx = true;
        }
      }
      if (hasUsageInValDeclCtx == false) {
        reportError(valDecl->getLocation());
      }
    }
  }

private:
  typedef std::multimap<const ValueDecl *, const DeclContext *> ValRefMapType;
  ValRefMapType m_varDecls;
  std::stack<const DeclContext *> m_CurDeclContext;
};

static RuleCheckerASTContextRegistry::Add<Rule_3_4_1> X("3-4-1", "");
}
