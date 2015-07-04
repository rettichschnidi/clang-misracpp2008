//===-  Rule_3_4_1.cpp - Checker for MISRA C++ 2008 rule 3-4-1-------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "misracpp2008.h"
#include <map>

using namespace clang;

namespace misracpp2008 {

class Rule_3_4_1 : public RuleCheckerASTContext,
                   public RecursiveASTVisitor<Rule_3_4_1> {
public:
  Rule_3_4_1() : RuleCheckerASTContext(), m_CurTopScope(&m_RootScope) {}

  bool VisitDeclRefExpr(DeclRefExpr *D) {
    assert(m_RootScope.m_Children.size() > 0 &&
           "Visit* must be called after Traverse*");
    m_VarUsage.insert(std::make_pair(D->getDecl(), m_CurTopScope));

    return true;
  }

  bool VisitVarDecl(VarDecl *VD) {
    assert(m_RootScope.m_Children.size() > 0 &&
           "Visit* must be called after Traverse*");
    m_VarDecls.insert(std::make_pair(VD, m_CurTopScope));
    return true;
  }

  bool TraverseCompoundStmt(CompoundStmt *CS) {
    Scope *curTopScope = m_CurTopScope;
    if (CS) {
      Scope s(CS);
      m_CurTopScope->m_Children.push_back(s);
      m_CurTopScope = &m_CurTopScope->m_Children.back();
    }
    RecursiveASTVisitor<Rule_3_4_1>::TraverseCompoundStmt(CS);
    if (CS) {
      m_CurTopScope = curTopScope;
    }
    return true;
  }

  bool TraverseDecl(Decl *D) {
    DeclContext *CD = dyn_cast_or_null<DeclContext>(D);
    Scope *curTopScope = m_CurTopScope;
    if (CD) {
      Scope s(CD);
      m_CurTopScope->m_Children.push_back(s);
      m_CurTopScope = &m_CurTopScope->m_Children.back();
    }
    RecursiveASTVisitor<Rule_3_4_1>::TraverseDecl(D);
    if (CD) {
      m_CurTopScope = curTopScope;
    }
    return true;
  }

protected:
  virtual void doWork() override {
    RuleCheckerASTContext::doWork();
    this->TraverseDecl(context->getTranslationUnitDecl());

    m_RootScope.print();
    //    for (ValRefInScope::const_iterator I = m_VarUsage.cbegin(),
    //                                       keyE = m_VarUsage.cend();
    //         I != keyE;) {
    //      const ValueDecl *valDecl = I->first;
    //      const Scope *scopeCtx = valDecl->getDeclContext();

    //      bool hasUsageInScope = false;
    //      for (ValRefInScope::const_iterator valueE =
    //               m_VarUsage.upper_bound(I->first);
    //           I != valueE; ++I) {
    //        const DeclContext *usageContext = I->second;
    //        if (scopeCtx->Equals(usageContext)) {
    //          hasUsageInScope = true;
    //        }
    //      }
    //      if (hasUsageInScope == false) {
    //        reportError(valDecl->getLocation());
    //      }
    //    }
  }

private:
  struct Scope {
    const CompoundStmt *m_CS;
    const DeclContext *m_DC;
    const enum class Type { COMPOUNDKIND, DECLCONTEXTKIND, ROOT } m_Type;

    explicit Scope() : m_CS(nullptr), m_DC(nullptr), m_Type(Type::ROOT) {}
    Scope(const CompoundStmt *cs)
        : m_CS(cs), m_DC(nullptr), m_Type(Type::COMPOUNDKIND) {}
    Scope(const DeclContext *dc)
        : m_CS(nullptr), m_DC(dc), m_Type(Type::DECLCONTEXTKIND) {}

    std::vector<Scope> m_Children;

    void print(unsigned level = 0) {
      for (unsigned i = 0; i < level; ++i) {
        llvm::outs() << " ";
      }

      if (m_Type == Type::COMPOUNDKIND) {
        llvm::outs() << "Begin CompoundStmt\n";
      } else if (m_Type == Type::DECLCONTEXTKIND) {
        llvm::outs() << "Begin DeclContext\n";
      } else {
        llvm::outs() << "Begin Root\n";
      }

      for (Scope &s : m_Children) {
        s.print(level + 1);
      }

      for (unsigned i = 0; i < level; ++i) {
        llvm::outs() << " ";
      }
      if (m_Type == Type::COMPOUNDKIND) {
        llvm::outs() << "End CompoundStmt\n";
      } else if (m_Type == Type::DECLCONTEXTKIND) {
        llvm::outs() << "End DeclContext\n";
      } else {
        llvm::outs() << "End Root\n";
      }
    }
  };

  using ValRefInScope = std::multimap<const ValueDecl *, const Scope *>;
  using ValDeclInScope = std::map<const ValueDecl *, const Scope *>;
  ValRefInScope m_VarUsage;
  ValRefInScope m_VarDecls;
  Scope m_RootScope;
  Scope *m_CurTopScope;
};

static RuleCheckerASTContextRegistry::Add<Rule_3_4_1> X("3-4-1", "");
}
