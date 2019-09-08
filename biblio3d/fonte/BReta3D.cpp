//---------------------------------------------------------------------------
#include <math.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "BReta3D.h"
//---------------------------------------------------------------------------
namespace BBib
{

namespace Biblio3D
{

const char* BReta3D::MENSAGEM_ERRO[] = {
    "",
    "Os dois pontos são coincidentes.",             //1
    "As duas retas não são concorrentes.",          //2
    "O vetor nulo não define uma reta.",            //3
    ""
};
//---------------------------------------------------------------------------
BReta3D::BReta3D(void)
    : BObjeto3D(), aPonto(0, 0, 0), aVetor(0, 0, 1)
{
}
//---------------------------------------------------------------------------
BReta3D::BReta3D(const BReta3D& reta)
    : BObjeto3D(reta), aPonto(reta.aPonto), aVetor(reta.aVetor)
{
    if(abs(aVetor) < Tolerancia())
    {
        throw BExcecaoMatematica(MENSAGEM_ERRO[3]);
    }
}
//---------------------------------------------------------------------------
BReta3D::BReta3D(const BPonto3D& p, const BVetor3D& v)
    : BObjeto3D(), aPonto(p), aVetor(v)
{
    if(abs(aVetor) < Tolerancia())
    {
        throw BExcecaoMatematica(MENSAGEM_ERRO[3]);
    }
}
//---------------------------------------------------------------------------
BReta3D::BReta3D(const BPonto3D& p1, const BPonto3D& p2)
    : BObjeto3D(), aPonto(p1)
{
    BVetor3D v = p2 - p1;
    double mod = abs(v);

    if(mod > Tolerancia())
    {
        aVetor = v / mod;
    }
    else
    {
        throw BExcecaoMatematica(MENSAGEM_ERRO[1]);
    }
}
//---------------------------------------------------------------------------
BReta3D::~BReta3D(void)
{
}
//---------------------------------------------------------------------------
BReta3D& BReta3D::operator = (const BReta3D& reta)
{
    if(this != &reta)
    {
        aPonto = reta.aPonto;
        aVetor = reta.aVetor;
    }
    return *this;
}
//---------------------------------------------------------------------------
void BReta3D::Def(const BPonto3D& p1, const BPonto3D& p2)
{
    BVetor3D v = p2 - p1;
    double mod = abs(v);

    if(mod > Tolerancia())
    {
        aPonto = p1;
        aVetor = v / mod;
    }
    else
    {
        throw BExcecaoMatematica(MENSAGEM_ERRO[1]);
    }
}
//---------------------------------------------------------------------------
void BReta3D::Def(const BPonto3D& p, const BVetor3D& v)
{
    if(abs(v) < Tolerancia())
    {
        throw BExcecaoMatematica(MENSAGEM_ERRO[3]);
    }
    aPonto = p;
    aVetor = v;
}
//---------------------------------------------------------------------------
const BPonto3D& BReta3D::LePonto(void) const
{
    return aPonto;
}
//---------------------------------------------------------------------------
const BVetor3D& BReta3D::LeVetor(void) const
{
    return aVetor;
}
//---------------------------------------------------------------------------
bool Coplanares(const BReta3D& reta1, const BReta3D& reta2)
{
    BVetor3D v1 = reta1.aPonto - reta2.aPonto;
    const BVetor3D& v2 = reta1.aVetor;
    const BVetor3D& v3 = reta2.aVetor;
    double det = (v1.X() * v2.Y() * v3.Z()) +
                 (v1.Y() * v2.Z() * v3.X()) +
                 (v1.Z() * v2.X() * v3.Y()) -
                 (v1.Z() * v2.Y() * v3.X()) -
                 (v1.Y() * v2.X() * v3.Z()) -
                 (v1.X() * v2.Z() * v3.Y());

    return fabs(det) < BObjeto3D::Tolerancia();
}
//---------------------------------------------------------------------------
double Distancia(const BReta3D& reta, const BPonto3D& p)
{
    const BVetor3D& v1 = reta.aVetor;
    BVetor3D v2 = p - reta.aPonto;

    return abs(ProdutoVetorial(v1, v2) / abs(v1));
}
//---------------------------------------------------------------------------
double Distancia(const BPonto3D& p, const BReta3D& reta)
{
    return Distancia(reta, p);
}
//---------------------------------------------------------------------------
bool Ortogonais(const BReta3D& reta1, const BReta3D& reta2)
{
    return fabs(reta1.aVetor * reta2.aVetor) < BObjeto3D::ToleranciaAoQuadrado();
}
//---------------------------------------------------------------------------
bool Paralelas(const BReta3D& reta1, const BReta3D& reta2)
{
    double x1 = reta1.aVetor.X();
    double y1 = reta1.aVetor.Y();
    double z1 = reta1.aVetor.Z();
    double x2 = reta2.aVetor.X();
    double y2 = reta2.aVetor.Y();
    double z2 = reta2.aVetor.Z();
    const double ZERO2 = BObjeto3D::ToleranciaAoQuadrado();

    return (fabs(x1*y2 - y1*x2) < ZERO2) && (fabs(x1*z2 - z1*x2) < ZERO2);
}
//---------------------------------------------------------------------------
bool Perpendiculares(const BReta3D& reta1, const BReta3D& reta2)
{
    return Ortogonais(reta1, reta2) && Coplanares(reta1, reta2);
}
//---------------------------------------------------------------------------
bool BReta3D::ContemPonto(const BPonto3D& Ponto) const
{
    return (abs(ProdutoVetorial(aVetor, Ponto - aPonto)) < Tolerancia());
}
//---------------------------------------------------------------------------
bool Coincidentes(const BReta3D& reta1, const BReta3D& reta2)
{
    return reta1.ContemPonto(reta2.aPonto) && Paralelos(reta1.aVetor,reta2.aVetor);
}
//---------------------------------------------------------------------------

}; //namespace Biblio3D

}; //namespace BBib

