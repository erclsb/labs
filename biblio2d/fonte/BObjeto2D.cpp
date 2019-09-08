
#pragma hdrstop

#include "BObjeto2D.h"

namespace BBib
{

namespace Biblio2D
{

const double BObjeto2D::ZERO = 1e-7;

BObjeto2D::BObjeto2D(void) {
}

BObjeto2D::BObjeto2D(const BObjeto2D& x) {
    /**
    Cria uma cópia de x.
    */
}

BObjeto2D::~BObjeto2D(void) {
    /**
    Libera a memória ocupada pelo objeto.
    */
}

BObjeto2D& BObjeto2D::operator = (const BObjeto2D& x) {
    /**
    Transforma o objeto em uma cópia de x.
    */
    return *this;
}

}; //namespace Biblio3D

}; //namespace BBib

