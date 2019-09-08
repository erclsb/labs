//---------------------------------------------------------------------------
#include <math.h>
#pragma hdrstop
//-------------------------------------------------------------------------
#include "BPonto3D.h"
//---------------------------------------------------------------------------
namespace BBib
{

namespace Biblio3D
{

BPonto3D::BPonto3D(void)
    : BObjeto3D(), x(0), y(0), z(0)
{
    /**
    Cria um ponto com as coordenadas (0, 0, 0).
    */
}
//---------------------------------------------------------------------------
BPonto3D::BPonto3D(double xx, double yy, double zz)
    : BObjeto3D(), x(xx), y(yy), z(zz)
{
    /**
    Cria um ponto com as coordenadas (xx, yy, zz).
    */
}
//---------------------------------------------------------------------------
BPonto3D::BPonto3D(const BPonto3D& p)
    : BObjeto3D(p), x(p.x), y(p.y), z(p.z)
{
    /**
    Cria uma cópia de p.
    */
}
//---------------------------------------------------------------------------
BPonto3D::~BPonto3D(void)
{
    /**
    Libera a memória ocupada pelo ponto.
    */
}
//---------------------------------------------------------------------------
BPonto3D& BPonto3D::operator = (const BPonto3D& p)
{
    /**
    Transforma o ponto em uma cópia de p.
    */
    if(this != &p)
    {
        x = p.x;
        y = p.y;
        z = p.z;
    }
    return *this;
}
//---------------------------------------------------------------------------
bool BPonto3D::operator == (const BPonto3D& p) const
{
    /**
    Retorna true se os dois pontos tiverem as mesmas coordenadas.
    Caso contrário, retorna false.
    */
    return ((x == p.x) && (y == p.y) && (z == p.z));
}
//---------------------------------------------------------------------------
bool BPonto3D::operator != (const BPonto3D& p) const
{
    /**
    Retorna false se os dois pontos tiverem as mesmas coordenadas.
    Caso contrário, retorna true.
    */
    return ((x != p.x) || (y != p.y) || (z != p.z));
}
//---------------------------------------------------------------------------
bool Colineares(const BPonto3D& p1, const BPonto3D& p2, const BPonto3D& p3)
{
    /**
    Retorna true se os três pontos forem colineares.
    Caso contrário, retorna false.
    */
    double x1 = p2.x - p1.x;
    double y1 = p2.y - p1.y;
    double z1 = p2.z - p1.z;
    double x2 = p3.x - p1.x;
    double y2 = p3.y - p1.y;
    double z2 = p3.z - p1.z;
    double det1 = x1 * y2 - y1 * x2;
    double det2 = y1 * z2 - z1 * y2;
    double det3 = z1 * x2 - x1 * z2;

    return (fabs(det1) < BObjeto3D::Tolerancia()) &&
        (fabs(det2) < BObjeto3D::Tolerancia()) &&
        (fabs(det3) < BObjeto3D::Tolerancia());
}
//---------------------------------------------------------------------------
bool Coplanares(const BPonto3D& p1, const BPonto3D& p2, const BPonto3D& p3, const BPonto3D& p4)
{
    /**
    Retorna true se os quatro pontos forem coplanares.
    Caso contrário, retorna false.
    */
    double x1 = p2.x - p1.x;
    double y1 = p2.y - p1.y;
    double z1 = p2.z - p1.z;
    double x2 = p3.x - p1.x;
    double y2 = p3.y - p1.y;
    double z2 = p3.z - p1.z;
    double x3 = p4.x - p1.x;
    double y3 = p4.y - p1.y;
    double z3 = p4.z - p1.z;
    double det = (x1 * y2 * z3) + (y1 * z2 * x3) + (z1 * x2 * y3) -
                 (z1 * y2 * x3) - (y1 * x2 * z3) - (x1 * z2 * y3);

    return fabs(det) < BObjeto3D::Tolerancia();
}
//---------------------------------------------------------------------------
void BPonto3D::DefCoordenadas(double xx, double yy, double zz)
{
    /**
    Define as coordenadas retangulares do ponto.
    */
    x = xx;
    y = yy;
    z = zz;
}
//---------------------------------------------------------------------------
void BPonto3D::DefCoordenadasCilindricas(double mod, double ang, double zz)
{
    /**
    Define as coordenadas cilíndricas do ponto.
    */
    x = mod * cos(ang);
    y = mod * sin(ang);
    z = zz;
}
//---------------------------------------------------------------------------
void BPonto3D::DefCoordenadasEsfericas(double mod, double theta, double phi)
{
    /**
    Define as coordenadas esféricas do ponto.
    */
    double aux = mod * cos(phi);

    x = aux * cos(theta);
    y = aux * sin(theta);
    z = mod * sin(phi);
}
//---------------------------------------------------------------------------
double Distancia(const BPonto3D& p1, const BPonto3D& p2)
{
    /**
    Retorna a distância entre os dois pontos fornecidos.
    */
    double x = p2.x - p1.x;
    double y = p2.y - p1.y;
    double z = p2.z - p1.z;

    return sqrt(x*x + y*y + z*z);
}
//---------------------------------------------------------------------------
double phi(const BPonto3D& p)
{
    /**
    Retorna o ângulo formado pela reta que liga a origem até o ponto
    com o plano XY.
    */
    return atan2(p.z, sqrt(p.x * p.x + p.y * p.y));
}
//---------------------------------------------------------------------------
double theta(const BPonto3D& p)
{
    /**
    Retorna o ângulo formado pela projeção da reta
    que liga a origem até o ponto com o eixo X.
    */
    return atan2(p.y, p.x);
}
//---------------------------------------------------------------------------
BPonto3D PontoMedio(const BPonto3D& p1, const BPonto3D& p2)
{
    /**
    Retorna o ponto médio entre os pontos p1 e p2.
    */
    return BPonto3D(
        0.5 * (p1.x + p2.x),
        0.5 * (p1.y + p2.y),
        0.5 * (p1.z + p2.z));
}
//---------------------------------------------------------------------------

}; //namespace Biblio3D

}; //namespace BBib

