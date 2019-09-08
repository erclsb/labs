#ifndef BSegmentoReta2DH
#define BSegmentoReta2DH

#include "BPonto2D.h"
#include "BVetor2D.h"

namespace BBib {

namespace Biblio2D {

/**
 * Esta classe representa um segmento de reta no espaço 2D.
 */
class BSegmentoReta2D : public BObjeto2D
{
    public:
        BSegmentoReta2D(void);
        BSegmentoReta2D(const BSegmentoReta2D& x);
        BSegmentoReta2D(BPonto2D p1, BPonto2D p2);
        BSegmentoReta2D(double x1, double y1, double x2, double y2);
        virtual ~BSegmentoReta2D(void);
        //
        BSegmentoReta2D& operator = (const BSegmentoReta2D& x);
        operator BVetor2D() const;
        //
        void DefPonto1(const BPonto2D& Ponto);
        void DefPonto1(double x, double y);
        void DefPonto2(const BPonto2D& Ponto);
        void DefPonto2(double x, double y);
        //
        const BPonto2D& LePonto1(void) const;
        const BPonto2D& LePonto2(void) const;
        //
        double Comprimento(void) const;
        //
        friend double Distancia(const BSegmentoReta2D& Segmento, const BPonto2D& Ponto);
        friend double Distancia(const BPonto2D& Ponto, const BSegmentoReta2D& Segmento);

    private:
        BPonto2D aPonto1;
        BPonto2D aPonto2;
};

}; //namespace Biblio3D

}; //namespace BBib

#endif

