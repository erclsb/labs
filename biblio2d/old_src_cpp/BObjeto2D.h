#ifndef BObjeto2DH
#define BObjeto2DH

#include "BExcecao.h"

namespace BBib {

namespace Biblio2D {

class BObjeto2D {
    public:
        virtual ~BObjeto2D(void);
        //Operadores
        BObjeto2D& operator = (const BObjeto2D& x);
        //Excecoes
        class BExcecaoMatematica;
        class BExcecaoValorForaFaixa;

    protected:
        BObjeto2D(void);
        BObjeto2D(const BObjeto2D& x);

        static const double Tolerancia(void) {return ZERO; };
        static const double ToleranciaAoQuadrado(void) {return ZERO * ZERO; };

    private:
        static const double ZERO;
};

class BObjeto2D::BExcecaoMatematica : public BExcecao {
    public:
        BExcecaoMatematica(void) : BExcecao("Erro matemático.") {}
        BExcecaoMatematica(const BExcecaoMatematica& e) : BExcecao(e) {}
        BExcecaoMatematica(const char* msg) : BExcecao(msg) {}
        virtual ~BExcecaoMatematica(void) {}
};

class BObjeto2D::BExcecaoValorForaFaixa : public BExcecao {
    public:
        BExcecaoValorForaFaixa(void) : BExcecao("Valor fora da faixa.") {}
        BExcecaoValorForaFaixa(const BExcecaoValorForaFaixa& e) : BExcecao(e) {}
        BExcecaoValorForaFaixa(const char* msg) : BExcecao(msg) {}
        virtual ~BExcecaoValorForaFaixa(void) {}
};

}; //namespace Biblio2D

}; //namespace BBib

#endif

