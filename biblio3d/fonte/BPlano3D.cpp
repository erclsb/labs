//---------------------------------------------------------------------------
#include <math.h>
#pragma hdrstop
//-------------------------------------------------------------------------
#include "BPlano3D.h"
//---------------------------------------------------------------------------
namespace BBib
{

namespace Biblio3D
{

const char* BPlano3D::MENSAGEM_ERRO[] = {
    "",
    "O vetor normal ao plano não pode ser nulo.",               //1
    "Os três pontos são colineares e não definem um plano.",    //2
    ""
};
//---------------------------------------------------------------------------
BPlano3D::BPlano3D(void)
    : BObjeto3D(), aNormal(0, 0, 1), adD(0)
{
}
//---------------------------------------------------------------------------
BPlano3D::BPlano3D(const BPlano3D& plano)
    : BObjeto3D(plano), aNormal(plano.aNormal), adD(plano.adD)
{
}
//---------------------------------------------------------------------------
BPlano3D::BPlano3D(double a, double b, double c, double d)
    : BObjeto3D(), aNormal(a, b, c), adD(d)
{
    if(abs(aNormal) < Tolerancia())
    {
        throw BExcecaoMatematica(MENSAGEM_ERRO[1]);
    }
}
//---------------------------------------------------------------------------
BPlano3D::BPlano3D(const BVetor3D& n, double d)
    : aNormal(n), adD(d)
{
    if(abs(aNormal) < Tolerancia())
    {
        throw BExcecaoMatematica(MENSAGEM_ERRO[1]);
    }
}
//---------------------------------------------------------------------------
BPlano3D::BPlano3D(const BVetor3D& n, const BPonto3D& pto)
    : aNormal(n)
{
    if(abs(aNormal) < Tolerancia())
    {
        throw BExcecaoMatematica(MENSAGEM_ERRO[1]);
    }
    adD = - n.X() * pto.X() - n.Y() * pto.Y() - n.Z() * pto.Z();
}
//---------------------------------------------------------------------------
BPlano3D::BPlano3D(const BPonto3D& p1, const BPonto3D& p2, const BPonto3D& p3)
{
    BVetor3D Normal = ProdutoVetorial(p2 - p1, p3 - p1);

    if(abs(Normal) < Tolerancia())
    {
        throw BExcecaoMatematica(MENSAGEM_ERRO[2]);
    }
    Def(Normal, p1);
}
//---------------------------------------------------------------------------
BPlano3D::~BPlano3D(void)
{
}
//---------------------------------------------------------------------------
BPlano3D& BPlano3D::operator = (const BPlano3D& plano)
{
    if(this != &plano)
    {
        aNormal = plano.aNormal;
        adD = plano.adD;
    }
    return *this;
}
//---------------------------------------------------------------------------
bool BPlano3D::ContemPonto(const BPonto3D& Ponto) const
{
    return SituaPonto(Ponto) == 0;
}
//---------------------------------------------------------------------------
void BPlano3D::Def(double a, double b, double c, double d)
{
    aNormal.DefCoordenadas(a, b, c);
    if(abs(aNormal) < Tolerancia())
    {
        throw BExcecaoMatematica(MENSAGEM_ERRO[1]);
    }
    adD = d;
}
//---------------------------------------------------------------------------
void BPlano3D::Def(const BVetor3D& Normal, const BPonto3D& pto)
{
    if(abs(Normal) < Tolerancia())
    {
        throw BExcecaoMatematica(MENSAGEM_ERRO[1]);
    }
    aNormal = Normal;
    adD = - Normal.X() * pto.X() - Normal.Y() * pto.Y() - Normal.Z() * pto.Z();
}
//---------------------------------------------------------------------------
void BPlano3D::Def(const BVetor3D& Normal, double d)
{
    if(abs(Normal) < Tolerancia())
    {
        throw BExcecaoMatematica(MENSAGEM_ERRO[1]);
    }
    aNormal = Normal;
    adD = d;
}
//---------------------------------------------------------------------------
void BPlano3D::Def(const BPonto3D& p1, const BPonto3D& p2, const BPonto3D& p3)
{
    BVetor3D Normal = ProdutoVetorial(p2 - p1, p3 - p1);

    if(abs(Normal) < Tolerancia())
    {
        throw BExcecaoMatematica(MENSAGEM_ERRO[2]);
    }
    Def(Normal, p1);
}
//---------------------------------------------------------------------------
double Distancia(const BPlano3D& Plano, const BPonto3D& p)
{
    BVetor3D v(p.X(), p.Y(), p.Z());

    return fabs(Plano.aNormal * v + Plano.adD) / abs(Plano.aNormal);
}
//---------------------------------------------------------------------------
const BVetor3D& BPlano3D::LeNormal(void) const
{
    return aNormal;
}
//---------------------------------------------------------------------------
BPonto3D BPlano3D::LePonto(void) const
{
    // Esta função retorna um ponto qualquer pertencente ao plano
    
    BPonto3D pt;

    if(aNormal.Z() == 0)
    {
        if(aNormal.Y() == 0)
        {
            if(aNormal.X() == 0)
            {
                throw BExcecaoMatematica(MENSAGEM_ERRO[1]);
            }
            else
            {
                pt.DefCoordenadas(-adD / aNormal.X(), 0, 0);
            }
        }
        else
        {
            pt.DefCoordenadas(0, -adD / aNormal.Y(), 0);
        }
    }
    else
    {
        pt.DefCoordenadas(0, -adD / aNormal.Y(), 0);
    }
    return pt;
}
//---------------------------------------------------------------------------
bool Ortogonais(const BPlano3D& Plano1, const BPlano3D& Plano2)
{
    return Ortogonais(Plano1.aNormal, Plano2.aNormal);
}
//---------------------------------------------------------------------------
bool Paralelos(const BPlano3D& Plano1, const BPlano3D& Plano2)
{
    return Paralelos(Plano1.aNormal, Plano2.aNormal);
}
//---------------------------------------------------------------------------
int BPlano3D::SituaPonto(const BPonto3D& pto) const
{
/*
      Esta função retorna:
      1 se o ponto estiver acima do plano
      0 se o ponto estiver na superfície do plano
     -1 se o ponto estiver abaixo do plano

      Entende-se por "acima do plano", na direção do vetor aNormal.
*/
   BPonto3D pt = LePonto();
   double m;

   m = aNormal * (pto - pt);
   if(fabs(m) < Tolerancia()) return 0;
   if(m < 0) return -1;
   return 1;
}
//---------------------------------------------------------------------------


}; //namespace Biblio3D

}; //namespace BBib

