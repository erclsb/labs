#ifndef BVetor2DH
#define BVetor2DH

#include "BPonto2D.h"
#include "BObjeto2D.h"

namespace BBib {

namespace Biblio2D {

/**
 * Esta classe representa um vetor no espaço 2D.
 */
class BVetor2D : public BObjeto2D {
    public:
        BVetor2D(void);
        BVetor2D(double xx, double yy);
        BVetor2D(const BVetor2D& v);
        virtual ~BVetor2D(void);
        //operadores membro
        BVetor2D& operator = (const BVetor2D& v);
        bool operator == (const BVetor2D& v);
        bool operator != (const BVetor2D& v);
        BVetor2D& operator += (const BVetor2D& v);
        BVetor2D& operator += (double d);
        BVetor2D& operator -= (const BVetor2D& v);
        BVetor2D& operator -= (double d);
        BVetor2D& operator *= (double d);
        BVetor2D& operator /= (double d);
        //operadores nao-membro
        friend BVetor2D operator + (const BVetor2D& v1, const BVetor2D& v2);
        friend BVetor2D operator + (double d, const BVetor2D& v);
        friend BVetor2D operator + (const BVetor2D& v, double d);
        friend BPonto2D operator + (const BPonto2D& p, const BVetor2D& v);
        friend BVetor2D operator - (const BVetor2D& v);
        friend BVetor2D operator - (const BPonto2D& p1, const BPonto2D& p2);
        friend BVetor2D operator - (const BVetor2D& v1, const BVetor2D& v2);
        friend BVetor2D operator - (const BVetor2D& v, double d);
        friend double   operator * (const BVetor2D& v1, const BVetor2D& v2);
        friend BVetor2D operator * (double d, const BVetor2D& p);
        friend BVetor2D operator * (const BVetor2D& v, double d);
        friend BVetor2D operator / (const BVetor2D& v, double d);
        //funcoes membro
        void DefCoordenadas(double xx, double yy);
        void DefCoordenadasPolares(double dist, double ang);
        inline double& X(void);
        inline const double& X(void) const;
        inline double& Y(void);
        inline const double& Y(void) const;
        //funcoes nao-membro
        friend double Angulo(const BVetor2D& v1, const BVetor2D& v2);
        friend double abs(const BVetor2D& v);
        friend double arg(const BVetor2D& v);
        friend double norm(const BVetor2D& v);
        friend BVetor2D unit(const BVetor2D& v);

    private:
        double x;
        double y;

        static const char* MENSAGEM_ERRO[];
};

double& BVetor2D::X(void) {
    /**
     * Retorna a coordenada X do vetor.
     */
    return x;
}

const double& BVetor2D::X(void) const {
    /**
     * Retorna a coordenada X do vetor.
     */
    return x;
}

double& BVetor2D::Y(void) {
    /**
     * Retorna a coordenada Y do vetor.
     */
    return y;
}

const double& BVetor2D::Y(void) const {
    /**
     * Retorna a coordenada Y do vetor.
     */
    return y;
}

}; //namespace Biblio2D

}; //namespace BBib

#endif

