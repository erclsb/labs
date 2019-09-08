#pragma hdrstop

#include "BPoligono2D.h"

namespace BBib {

namespace Biblio2D {

BPoligono2D::BPoligono2D(void)
        : BPoligono2DBase() {
    /**
     * Cria um polígono genérico.
     */
}

BPoligono2D::BPoligono2D(const BPoligono2D& x)
        : BPoligono2DBase(x) {
    /**
     * Cria uma cópia de x.
     */
}

BPoligono2D::~BPoligono2D(void) {
    /**
     * Libera a memória ocupada pelo objeto.
     */
}

BPoligono2D& BPoligono2D::operator = (const BPoligono2D& Poligono2D) {
    /**
     * Transforma o objeto em uma cópia de x.
     */
    if(this != &Poligono2D) {
        BPoligono2DBase::operator= (Poligono2D);
    }
    return *this;
}

void BPoligono2D::DefNumeroVertices(int n) {
    /**
     * Define o número de vértices do polígono.
     */
    BPoligono2DBase::DefNumeroVertices(n);
}

}; //namespace Biblio2D

}; //namespace BBib

