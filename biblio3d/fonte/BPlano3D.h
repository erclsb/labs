//---------------------------------------------------------------------------
#ifndef BPlano3DH
#define BPlano3DH
//---------------------------------------------------------------------------
#include "BVetor3D.h"
#include "BObjeto3D.h"
//---------------------------------------------------------------------------
namespace BBib
{

namespace Biblio3D
{

class BPlano3D : public BObjeto3D
{
    private:
        BVetor3D aNormal;
        double adD;
        static const char* MENSAGEM_ERRO[];

    protected:
    
    public:
        BPlano3D(void);
        BPlano3D(double a, double b, double c, double d);
        BPlano3D(const BVetor3D& n, const BPonto3D& pto);
        BPlano3D(const BVetor3D& n, double d);
        BPlano3D(const BPonto3D& p1, const BPonto3D& p2, const BPonto3D& p3);
        BPlano3D(const BPlano3D& plano);
        virtual ~BPlano3D(void);
        //Operadores
        BPlano3D& operator = (const BPlano3D& plano);
        //Funcoes membro
        bool ContemPonto(const BPonto3D& Ponto) const;
        void Def(double a, double b, double c, double d);
        void Def(const BVetor3D& Normal, const BPonto3D& pto);
        void Def(const BVetor3D& Normal, double d);
        void Def(const BPonto3D& p1, const BPonto3D& p2, const BPonto3D& p3);
        const BVetor3D& LeNormal(void) const;
        BPonto3D LePonto(void) const;
        int SituaPonto(const BPonto3D& Ponto) const;
        //Funcoes nao membro
        friend double Distancia(const BPlano3D& Plano, const BPonto3D& p);
        friend bool Ortogonais(const BPlano3D& Plano1, const BPlano3D& Plano2);
        friend bool Paralelos(const BPlano3D& Plano1, const BPlano3D& Plano2);
};
//---------------------------------------------------------------------------

}; //namespace Biblio3D

}; //namespace BBib

#endif
