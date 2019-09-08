//---------------------------------------------------------------------------
#pragma hdrstop

#include "BObjeto3D.h"
//---------------------------------------------------------------------------
namespace BBib
{

namespace Biblio3D
{

const double BObjeto3D::ZERO = 1e-7;
//---------------------------------------------------------------------------
BObjeto3D::BObjeto3D(void)
{
}
//---------------------------------------------------------------------------
BObjeto3D::BObjeto3D(const BObjeto3D& x)
{
    /**
    Cria uma c�pia de x.
    */
}
//---------------------------------------------------------------------------
BObjeto3D::~BObjeto3D(void)
{
    /**
    Libera a mem�ria ocupada pelo objeto.
    */
}
//---------------------------------------------------------------------------
BObjeto3D& BObjeto3D::operator = (const BObjeto3D& x)
{
    /**
    Transforma o objeto em uma c�pia de x.
    */
    return *this;
}
//---------------------------------------------------------------------------


}; //namespace Biblio3D

}; //namespace BBib

