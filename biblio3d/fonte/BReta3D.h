//---------------------------------------------------------------------------
#ifndef BReta3DH
#define BReta3DH
//---------------------------------------------------------------------------
#include "BObjeto3D.h"
#include "BPonto3D.h"
#include "BVetor3D.h"
//---------------------------------------------------------------------------
namespace BBib
{

namespace Biblio3D
{

class BReta3D : public BObjeto3D
{
    private:
        BPonto3D aPonto;
        BVetor3D aVetor;
        static const char* MENSAGEM_ERRO[];

    public:
        //Construtores e destrutor
        BReta3D(void);
        BReta3D(const BReta3D& reta);
        BReta3D(const BPonto3D& p1, const BPonto3D& p2);
        BReta3D(const BPonto3D& p, const BVetor3D& v);
        virtual ~BReta3D(void);
        //Operadores
        BReta3D& operator = (const BReta3D& reta);
        //Funcoes membro
        void Def(const BPonto3D& p1, const BPonto3D& p2);
        void Def(const BPonto3D& p, const BVetor3D& v);
        const BPonto3D& LePonto(void) const;
        const BVetor3D& LeVetor(void) const;
        bool ContemPonto(const BPonto3D& Ponto) const;
        //Funcoes nao-membro
        friend bool Coincidentes(const BReta3D& reta1, const BReta3D& reta2);
        friend bool Coplanares(const BReta3D& reta1, const BReta3D& reta2);
        friend double Distancia(const BReta3D& reta, const BPonto3D& p);
        friend double Distancia(const BPonto3D& p, const BReta3D& reta);
        friend BPonto3D Intersecao(const BReta3D& reta1, const BReta3D& reta2);
        friend bool Ortogonais(const BReta3D& reta1, const BReta3D& reta2);
        friend bool Paralelas(const BReta3D& reta1, const BReta3D& reta2);
        friend bool Perpendiculares(const BReta3D& reta1, const BReta3D& reta2);
};
//---------------------------------------------------------------------------

}; //namespace Biblio3D

}; //namespace BBib

#endif
 
