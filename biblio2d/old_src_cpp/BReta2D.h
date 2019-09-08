#ifndef BReta2DH
#define BReta2DH

#include "BPonto2D.h"
#include "BVetor2D.h"
#include "BObjeto2D.h"
#include "BExcecao.h"

namespace BBib {

namespace Biblio2D {

class BReta2D : public BObjeto2D {
    public:
        BReta2D(void);
        BReta2D(const BReta2D& reta);
        BReta2D(const BPonto2D& p1, const BPonto2D& p2);
        BReta2D(const BPonto2D& p, const BVetor2D& v);
        virtual ~BReta2D(void);
        //Operadores
        BReta2D& operator = (const BReta2D& reta);
        //Funcoes membro
        void Def(const BPonto2D& p1, const BPonto2D& p2);
        void Def(const BPonto2D& p, const BVetor2D& v);
        const BPonto2D& LePonto(void) const;
        const BVetor2D& LeVetor(void) const;
        //Funcoes nao-membro
        friend double Distancia(const BReta2D& reta, const BPonto2D p);
        friend BPonto2D Intersecao(const BReta2D& reta1, const BReta2D& reta2);
        friend bool Ortogonais(const BReta2D& reta1, const BReta2D& reta2);
        friend bool Paralelas(const BReta2D& reta1, const BReta2D& reta2);

    private:
        BPonto2D aPonto;
        BVetor2D aVetor;

        static const char* MENSAGEM_ERRO[];
};

}; //namespace Biblio2D

}; //namespace BBib

#endif

