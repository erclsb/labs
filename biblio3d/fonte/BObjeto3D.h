//---------------------------------------------------------------------------
#ifndef BObjeto3DH
#define BObjeto3DH
//---------------------------------------------------------------------------
#include "BExcecao.h"
//---------------------------------------------------------------------------
namespace BBib
{

namespace Biblio3D
{

class BObjeto3D
{
    private:
        static const double ZERO;

    protected:
        BObjeto3D(void);
        BObjeto3D(const BObjeto3D& x);

        static const double Tolerancia(void) {return ZERO; };
        static const double ToleranciaAoQuadrado(void) {return ZERO * ZERO; };

    public:
        virtual ~BObjeto3D(void);
        //Operadores
        BObjeto3D& operator = (const BObjeto3D& x);
        //Excecoes
        class BExcecaoMatematica;
        class BExcecaoValorForaFaixa;
};
//---------------------------------------------------------------------------
class BObjeto3D::BExcecaoMatematica : public BExcecao
{
    public:
        BExcecaoMatematica(void) : BExcecao("Erro matemático.") {}
        BExcecaoMatematica(const BExcecaoMatematica& e) : BExcecao(e) {}
        BExcecaoMatematica(const char* msg) : BExcecao(msg) {}
        virtual ~BExcecaoMatematica(void) {}
};
//---------------------------------------------------------------------------
class BObjeto3D::BExcecaoValorForaFaixa : public BExcecao
{
    public:
        BExcecaoValorForaFaixa(void) : BExcecao("Valor fora da faixa.") {}
        BExcecaoValorForaFaixa(const BExcecaoValorForaFaixa& e) : BExcecao(e) {}
        BExcecaoValorForaFaixa(const char* msg) : BExcecao(msg) {}
        virtual ~BExcecaoValorForaFaixa(void) {}
};
//---------------------------------------------------------------------------

}; //namespace Biblio3D

}; //namespace BBib

#endif
