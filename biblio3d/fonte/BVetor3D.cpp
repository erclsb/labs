//---------------------------------------------------------------------------
#include <math.h>
#pragma hdrstop
//-------------------------------------------------------------------------
#include "BVetor3D.h"
//---------------------------------------------------------------------------
namespace BBib
{

namespace Biblio3D
{

const char* BVetor3D::MENSAGEM_ERRO[] = {
    "",
    "Divisão por zero.",                                        //1
    "Impossível criar vetor unitário a partir do vetor nulo.",  //2
    ""
};
//---------------------------------------------------------------------------
BVetor3D::BVetor3D(void)
    : BObjeto3D(), x(0), y(0), z(0)
{
    /**
    Cria um vetor com coordenadas (0, 0, 0).
    */
}
//---------------------------------------------------------------------------
BVetor3D::BVetor3D(double xx, double yy, double zz)
    : BObjeto3D(), x(xx), y(yy), z(zz)
{
    /**
    Cria um vetor com coordenadas (xx, yy, zz).
    */
}
//---------------------------------------------------------------------------
BVetor3D::BVetor3D(const BVetor3D& v)
    : BObjeto3D(v), x(v.x), y(v.y), z(v.z)
{
    /**
    Cria uma cópia de v.
    */
}
//---------------------------------------------------------------------------
BVetor3D::~BVetor3D(void)
{
    /**
    Libera a memória ocupada pelo vetor.
    */
}
//---------------------------------------------------------------------------
BVetor3D& BVetor3D::operator = (const BVetor3D& v)
{
    /**
    Transforma o vetor em uma cópia de v.
    */
    if(this != &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    return *this;
}
//---------------------------------------------------------------------------
bool BVetor3D::operator == (const BVetor3D& v) const
{
    /**
    Retorna true se os dois vetores tiverem as mesmas coordenadas.
    Caso contrário, retorna false.
    */
    return ((x == v.x) && (y == v.y) && (z == v.z));
}
//---------------------------------------------------------------------------
bool BVetor3D::operator != (const BVetor3D& v) const
{
    /**
    Retorna false se os dois vetores tiverem as mesmas coordenadas.
    Caso contrário, retorna true.
    */
    return ((x != v.x) || (y != v.y) || (z != v.z));
}
//---------------------------------------------------------------------------
BVetor3D& BVetor3D::operator += (const BVetor3D& v)
{
    /**
    Acrescenta v ao vetor.
    */
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}
//---------------------------------------------------------------------------
BVetor3D& BVetor3D::operator += (double d)
{
    /**
    Acrescenta o vetor (d, d, d) ao vetor.
    */
    x += d;
    y += d;
    z += d;
    return *this;
}
//---------------------------------------------------------------------------
BVetor3D& BVetor3D::operator -= (const BVetor3D& v)
{
    /**
    Subtrai v do vetor.
    */
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}
//---------------------------------------------------------------------------
BVetor3D& BVetor3D::operator -= (double d)
{
    /**
    Subtrai o vetor (d, d, d) do vetor.
    */
    x -= d;
    y -= d;
    z -= d;
    return *this;
}
//---------------------------------------------------------------------------
BVetor3D& BVetor3D::operator *= (double d)
{
    /**
    Multiplica o vetor pelo escalar d.
    */
    x *= d;
    y *= d;
    z *= d;
    return *this;
}
//---------------------------------------------------------------------------
BVetor3D& BVetor3D::operator /= (double d)
{
    /**
    Divide o vetor pelo escalar d.
    */
    if(d == 0)
    {
        throw BExcecaoMatematica(MENSAGEM_ERRO[1]);
    }
    x /= d;
    y /= d;
    z /= d;
    return *this;
}
//---------------------------------------------------------------------------
BVetor3D operator + (const BVetor3D& v1, const BVetor3D& v2)
{
    /**
    Retorna a soma dos vetores v1 e v2.
    */
    return BVetor3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
//---------------------------------------------------------------------------
BVetor3D operator + (double d, const BVetor3D& v)
{
    /**
    Retorna a soma dos vetores v e (d, d, d).
    */
    return BVetor3D(v.x + d, v.y + d, v.z + d);
}
//---------------------------------------------------------------------------
BVetor3D operator + (const BVetor3D& v, double d)
{
    /**
    Retorna a soma dos vetores v e (d, d, d).
    */
    return BVetor3D(v.x + d, v.y + d, v.z + d);
}
//---------------------------------------------------------------------------
BPonto3D operator + (const BPonto3D& p, const BVetor3D& v)
{
    /**
    Retorna o ponto resultante da soma do ponto p
    com o vetor v.
    */
    return BPonto3D(v.x + p.X(), v.y + p.Y(), v.z + p.Z());
}
//---------------------------------------------------------------------------
BVetor3D operator - (const BVetor3D& v)
{
    /**
    Retorna o simétrico de v.
    */
    return BVetor3D(-v.x, -v.y, -v.z);
}
//---------------------------------------------------------------------------
BVetor3D operator - (const BPonto3D& p1, const BPonto3D& p2)
{
    /**
    Retorna o vetor entre os pontos p1 e p2.
    */
    return BVetor3D(p1.X() - p2.X(), p1.Y() - p2.Y(), p1.Z() - p2.Z());
}
//---------------------------------------------------------------------------
BVetor3D operator - (const BVetor3D& v1, const BVetor3D& v2)
{
    /**
    Retorna a diferença entre os vetores v1 e v2.
    */
    return BVetor3D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
//---------------------------------------------------------------------------
BVetor3D operator - (const BVetor3D& v, double d)
{
    /**
    Retorna a diferença entre os vetores v e (d, d, d).
    */
    return BVetor3D(v.x - d, v.y - d, v.z - d);
}
//---------------------------------------------------------------------------
double operator * (const BVetor3D& v1, const BVetor3D& v2)
{
    /**
    Retorna o produto escalar entre os vetores v1 e v2.
    */
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
//---------------------------------------------------------------------------
BVetor3D operator * (double d, const BVetor3D& v)
{
    /**
    Retorna o produto do vetor v pelo escalar d.
    */
    return BVetor3D(v.x * d, v.y * d, v.z * d);
}
//---------------------------------------------------------------------------
BVetor3D operator * (const BVetor3D& v, double d)
{
    /**
    Retorna o produto do vetor v pelo escalar d.
    */
    return BVetor3D(v.x * d, v.y * d, v.z * d);
}
//---------------------------------------------------------------------------
BVetor3D operator / (const BVetor3D& v, double d)
{
    /**
    Retorna a divisão do vetor v pelo escalar d.
    */
    if(d == 0)
    {
        throw BObjeto3D::BExcecaoMatematica(BVetor3D::MENSAGEM_ERRO[1]);
    }
    return BVetor3D(v.x / d, v.y / d, v.z / d);
}
//---------------------------------------------------------------------------
void BVetor3D::DefCoordenadas(double xx, double yy, double zz)
{
    /**
    Define as coordenadas retangulares do vetor.
    */
    x = xx;
    y = yy;
    z = zz;
}
//---------------------------------------------------------------------------
void BVetor3D::DefCoordenadasCilindricas(double mod, double ang, double zz)
{
    /**
    Define as coordenadas cilíndricas do vetor.
    */
    x = mod * cos(ang);
    y = mod * sin(ang);
    z = zz;
}
//---------------------------------------------------------------------------
void BVetor3D::DefCoordenadasEsfericas(double mod, double Phi, double Theta)
{
    /**
    Define as coordenadas esféricas do vetor.
    */
    double aux = mod * cos(Theta);

    x = aux * cos(Phi);
    y = aux * sin(Phi);
    z = mod * sin(Theta);
}
//---------------------------------------------------------------------------
double Angulo(const BVetor3D& v1, const BVetor3D& v2)
{
    /**
    Retorna o ângulo, em radianos, entre dois vetores. O ângulo sesultante
    está compreendido entre 0 e PI.

    Se um ou mais vetores forem nulos, a função retorna 0. 
    */
    double mod1 = abs(v1);
    double mod2 = abs(v2);

    if((mod1 == 0) || (mod2 == 0))
    {
        return 0;
    }
    return acos((v1 * v2) / (mod1 * mod2)); 
}
//---------------------------------------------------------------------------
double abs(const BVetor3D& v)
{
    /**
    Retorna o módulo do vetor v.
    */
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
//---------------------------------------------------------------------------
double norm(const BVetor3D& v)
{
    /**
    Retorna o quadrado do módulo do vetor v.
    */
    return v.x * v.x + v.y * v.y + v.z * v.z;
}
//---------------------------------------------------------------------------
bool Ortogonais(const BVetor3D& v1, const BVetor3D& v2)
{
    /**
    Retorna true se os dois vetores forem ortogonais.
    Caso contrário, retorna false.
    */
    return fabs(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z) <
        BObjeto3D::ToleranciaAoQuadrado();
}
//---------------------------------------------------------------------------
bool Paralelos(const BVetor3D& v1, const BVetor3D& v2)
{
    /**
    Retorna true se os dois vetores forem paralelos.
    Caso contrário, retorna false.
    */
    const double ZERO2 = BObjeto3D::ToleranciaAoQuadrado();

    return (fabs(v1.x * v2.y - v1.y * v2.x) < ZERO2) &&
        (fabs(v1.y * v2.z - v1.z * v2.y) < ZERO2) &&
        (fabs(v1.z * v2.x - v1.x * v2.z) < ZERO2);
}
//---------------------------------------------------------------------------
double phi(const BVetor3D& v)
{
    /**
    Retorna ângulo entre o vetor v e o plano XY.
    */
    return atan2(v.z, sqrt(v.x * v.x + v.y * v.y));
}
//---------------------------------------------------------------------------
BVetor3D ProdutoVetorial(const BVetor3D& v1, const BVetor3D& v2)
{
    /**
    Retorna o produto vetorial entre os vetores v1 e v2.
    */
    BVetor3D vetor;

    vetor.x = v1.y * v2.z - v1.z * v2.y;
    vetor.y = v1.z * v2.x - v1.x * v2.z;
    vetor.z = v1.x * v2.y - v1.y * v2.x;
    return vetor;
}
//---------------------------------------------------------------------------
double theta(const BVetor3D& v)
{
    /**
    Retorna ângulo entre a projeção do vetor v no plano XY e o eixo X.
    */
    return atan2(v.y, v.x);
}
//---------------------------------------------------------------------------
BVetor3D unit(const BVetor3D& v)
{
    /**
    Retorna o vetor unitário de mesma direção e sentido que o vetor v.
    */
    double mod = abs(v);

    if(mod == 0)
    {
        throw BObjeto3D::BExcecaoMatematica(BVetor3D::MENSAGEM_ERRO[2]);
    }
    return BVetor3D(v.x / mod, v.y / mod, v.z / mod);
}
//---------------------------------------------------------------------------

}; //namespace Biblio3D

}; //namespace BBib

