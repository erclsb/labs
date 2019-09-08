#ifndef BPoligono2DBaseH
#define BPoligono2DBaseH

#include <vector>
#include "BPonto2D.h"
#include "BObjeto2D.h"

namespace BBib {

namespace Biblio2D {

/**
 * Classe base abstrata para polígonos no espaço 2D.
 */
class BPoligono2DBase : public BObjeto2D {
    public:
        virtual ~BPoligono2DBase(void);
        BPoligono2DBase& operator = (const BPoligono2DBase& x);
        //
        void DefVertice(unsigned int Indice, const BPonto2D& Vertice);
        void DefVertices(const BPonto2D* Vertice);
        void DefVertices(const float* X, const float* Y);
        void DefVertices(const double* X, const double* Y);
        //
        int LeNumeroVertices(void) const;
        const BPonto2D& LeVertice(unsigned int Indice) const;
        //
        double Area(void) const;
        double Perimetro(void) const;
        bool Concavo(void) const;
        bool Convexo(void) const;
        bool Valido(void) const;
        bool ContemPonto(const BPonto2D& Ponto) const;
        bool InterceptaSegmento(const BPonto2D& Ponto1, const BPonto2D& Ponto2) const;
        //
        friend double Distancia(const BPoligono2DBase& Poligono, const BPonto2D& Ponto);
        friend double Distancia(const BPonto2D& Ponto, const BPoligono2DBase& Poligono);
        friend bool LadosCoincidentes(const BPoligono2DBase& P1, const BPoligono2DBase& P2);
        friend bool ExisteIntersecao(const BPoligono2DBase& P1, const BPoligono2DBase& P2);

    protected:
        BPoligono2DBase(void);
        BPoligono2DBase(const BPoligono2DBase& x);
        explicit BPoligono2DBase(int NumVertices);
        //
        void DefNumeroVertices(int NumVertices);

    private:
        static const double ZERO;
        std::vector<BPonto2D> aVertice;
};

}; //namespace Biblio2D

}; //namespace BBib

#endif

