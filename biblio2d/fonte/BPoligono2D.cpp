#pragma hdrstop

#include "BPoligono2D.h"

namespace BBib {

namespace Biblio2D {

BPoligono2D::BPoligono2D(void)
        : BPoligono2DBase() {
    /**
     * Cria um pol�gono gen�rico.
     */
}

BPoligono2D::BPoligono2D(const BPoligono2D& x)
        : BPoligono2DBase(x) {
    /**
     * Cria uma c�pia de x.
     */
}

BPoligono2D::~BPoligono2D(void) {
    /**
     * Libera a mem�ria ocupada pelo objeto.
     */
}

BPoligono2D& BPoligono2D::operator = (const BPoligono2D& Poligono2D) {
    /**
     * Transforma o objeto em uma c�pia de x.
     */
    if(this != &Poligono2D) {
        BPoligono2DBase::operator= (Poligono2D);
    }
    return *this;
}

void BPoligono2D::DefNumeroVertices(int n) {
    /**
     * Define o n�mero de v�rtices do pol�gono.
     */
    BPoligono2DBase::DefNumeroVertices(n);
}

}; //namespace Biblio2D

}; //namespace BBib

