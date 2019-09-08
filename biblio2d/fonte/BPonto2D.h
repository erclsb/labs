#ifndef BPonto2DH
#define BPonto2DH

#include "BObjeto2D.h"

namespace BBib {

namespace Biblio2D {

/**
 * Esta classe representa um ponto no espaço 2D.
 */
class BPonto2D : public BObjeto2D {
    public:
        BPonto2D(void);
        BPonto2D(double xx, double yy);
        BPonto2D(const BPonto2D& p);
        virtual ~BPonto2D(void);
        //Operadores
        BPonto2D& operator = (const BPonto2D& p);
        bool operator == (const BPonto2D &p) const;
        bool operator != (const BPonto2D &p) const;
        //Definicoes
        void DefCoordenadas(double xx, double yy);
        void DefCoordenadasPolares(double dist, double ang);
        inline double& X(void);
        inline const double& X(void) const;
        inline double& Y(void);
        inline const double& Y(void) const;
        //Funcoes nao-membro
        friend double Distancia(const BPonto2D& p1, const BPonto2D& p2);
        friend BPonto2D PontoMedio(const BPonto2D& p1, const BPonto2D& p2);
        friend bool Colineares(const BPonto2D& p1, const BPonto2D& p2, const BPonto2D& p3);
        friend double arg(const BPonto2D& p);

    private:
        double x;
        double y;
};

double& BPonto2D::X(void) {
    /**
     * Retorna a coordenada X do ponto.
     */
    return x;
}

const double& BPonto2D::X(void) const {
    /**
     * Retorna a coordenada X do ponto.
     */
    return x;
}

double& BPonto2D::Y(void) {
    /**
     * Retorna a coordenada Y do ponto.
     */
    return y;
}

const double& BPonto2D::Y(void) const {
    /**
     * Retorna a coordenada Y do ponto.
     */
    return y;
}

}; //namespace Biblio2D

}; //namespace BBib

#endif

