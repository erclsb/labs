#ifndef BPoligono2DH
#define BPoligono2DH

#include "BPoligono2DBase.h"


namespace BBib {

namespace Biblio2D {

/**
 * Representa um polígono genérico.
 */
class BPoligono2D : public BPoligono2DBase {
    public:
        BPoligono2D(void);
        BPoligono2D(const BPoligono2D& x);
        virtual ~BPoligono2D(void);
        //
        BPoligono2D& operator = (const BPoligono2D& x);
        //
        void DefNumeroVertices(int n);
};

}; //namespace Biblio2D

}; //namespace BBib

#endif

