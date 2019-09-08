//---------------------------------------------------------------------------
#include <math.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "BSegmentoReta3D.h"
#include "BVetor3D.h"
//---------------------------------------------------------------------------
namespace BBib
{

namespace Biblio3D
{

const char* BSegmentoReta3D::MENSAGEM_ERRO[] = {
    "",
    "Pontos são coincidentes.",                     //1
    ""
};
//---------------------------------------------------------------------------
BSegmentoReta3D::BSegmentoReta3D(void)
    : BObjeto3D(), aPonto1(0, 0, 0), aPonto2(0, 0, 1)
{
    /**
    Cria um segmento de reta entre os pontos (0, 0, 0) e (0, 0, 1).
    */
}
//---------------------------------------------------------------------------
BSegmentoReta3D::BSegmentoReta3D(const BSegmentoReta3D& Segmento)
    : BObjeto3D(Segmento), aPonto1(Segmento.aPonto1), aPonto2(Segmento.aPonto2)
{
    /**
    Cria uma cópia do segmento fornecido.
    */
}
//---------------------------------------------------------------------------
BSegmentoReta3D::BSegmentoReta3D(const BPonto3D& p1, const BPonto3D& p2)
    : BObjeto3D(), aPonto1(p1), aPonto2(p2)
{
    /**
    Cria um segmento de reta entre os pontos p1 e p2.
    */
    if(norm(aPonto1 - aPonto2) < ToleranciaAoQuadrado())
    {
        throw BExcecaoMatematica(MENSAGEM_ERRO[1]);
    }
}
//---------------------------------------------------------------------------
BSegmentoReta3D::BSegmentoReta3D(double x1, double y1, double z1,
    double x2, double y2, double z2)
    : BObjeto3D(), aPonto1(x1, y1, z1), aPonto2(x2, y2, z2)
{
    /**
    Cria um segmento de reta entre os pontos (x1, y1, z1) e (x2, y2, z2).
    */
    if(norm(aPonto1 - aPonto2) < ToleranciaAoQuadrado())
    {
        throw BExcecaoMatematica(MENSAGEM_ERRO[1]);
    }
}
//---------------------------------------------------------------------------
BSegmentoReta3D::~BSegmentoReta3D(void)
{
    /**
    Libera a memória ocupada pelo segmento de reta.
    */
}
//---------------------------------------------------------------------------
BSegmentoReta3D& BSegmentoReta3D::operator = (const BSegmentoReta3D& Segmento)
{
    /**
    Transforma o segmento em uma cópia do segmento fornecido.
    */
    if(this != &Segmento)
    {
        aPonto1 = Segmento.aPonto1;
        aPonto2 = Segmento.aPonto2;
    }
    return *this;
}
//---------------------------------------------------------------------------
BSegmentoReta3D::operator BVetor3D(void) const
{
    /**
    Converte o segmento de reta em um vetor entre os pontos do segmento.
    */
    return aPonto2 - aPonto1;
}
//---------------------------------------------------------------------------
bool BSegmentoReta3D::ContemPonto(const BPonto3D& Ponto) const
{
    /**
    Retorna true se o ponto pertencer ao segmento de reta.
    Caso contrário, retorna false.
    */
    BVetor3D v1 = aPonto2 - aPonto1;
    BVetor3D v2 = Ponto - aPonto1;
    BVetor3D v3 = ProdutoVetorial(v1, v2);
    double mod = abs(v1);
    double aux;

    if(mod < Tolerancia()) return false;
    if(abs(v3) > 0) return false;
    aux = (v1 * v2) / (v1 * v1);
    return (aux >= 0) && (aux <= 1);
}
//---------------------------------------------------------------------------
bool BSegmentoReta3D::ContemPonto(double x, double y, double z) const
{
    /**
    Retorna true se o ponto (x, y, z) pertencer ao segmento de reta.
    Caso contrário, retorna false.
    */
    return ContemPonto(BPonto3D(x, y, z));
}
//---------------------------------------------------------------------------
void BSegmentoReta3D::DefPontos(const BPonto3D& p1, const BPonto3D& p2)
{
    /**
    Define o segmento de reta entre os pontos p1 e p2.
    */
    if(norm(p2 - p1) < ToleranciaAoQuadrado())
    {
        throw BExcecaoMatematica(MENSAGEM_ERRO[1]);
    }
    aPonto1 = p1;
    aPonto2 = p2;
}
//---------------------------------------------------------------------------
void BSegmentoReta3D::DefPontos(double x1, double y1, double z1,
    double x2, double y2, double z2)
{
    /**
    Define o segmento de reta entre os pontos (x1, y1, z1) e (x2, y2, z2).
    */
    if((fabs(x2 - x1) < Tolerancia()) &&
        (fabs(y2 - y1) < Tolerancia()) &&
        (fabs(z2 - z1) < Tolerancia()))
    {
        throw BExcecaoMatematica(MENSAGEM_ERRO[1]);
    }
    aPonto1.DefCoordenadas(x1, y1, z1);
    aPonto2.DefCoordenadas(x2, y2, z2);
}
//---------------------------------------------------------------------------
double Distancia(const BSegmentoReta3D& Segmento, const BPonto3D& Ponto)
{
    /**
    Retorna a distância do segmento de reta ao ponto.
    */
    BVetor3D vet1, vet2;
    double aux, aux2;
    double m;

    vet1 = Segmento.aPonto2 - Segmento.aPonto1;
    aux = vet1 * vet1;
    if(aux < BObjeto3D::Tolerancia())
    {
        return Distancia(Ponto, Segmento.aPonto1);
    }
    vet2 = Ponto - Segmento.aPonto1;
    aux2 = vet1 * vet2;
    m = aux2 / aux;
    if(m < 0)
    {
        return Distancia(Ponto, Segmento.aPonto1);
    }
    if(m > 1)
    {
        return Distancia(Ponto, Segmento.aPonto2);
    }
    return sqrt(vet2 * vet2 + m * (m * aux - 2 * aux2));
}
//---------------------------------------------------------------------------
double Distancia(const BPonto3D& Ponto, const BSegmentoReta3D& Segmento)
{
    /**
    Retorna a distância do segmento de reta ao ponto.
    */
    return Distancia(Segmento, Ponto);
}
//---------------------------------------------------------------------------
double BSegmentoReta3D::LeComprimento(void) const
{
    /**
    Retorna o comprimento do segmento de reta ao ponto.
    */
    return Distancia(aPonto1, aPonto2);
}
//---------------------------------------------------------------------------
const BPonto3D& BSegmentoReta3D::LePonto1(void) const
{
    /**
    Retorna o primeiro ponto do segmento de reta.
    */
    return aPonto1;
}
//---------------------------------------------------------------------------
const BPonto3D& BSegmentoReta3D::LePonto2(void) const
{
    /**
    Retorna o segundo ponto do segmento de reta.
    */
    return aPonto2;
}
//---------------------------------------------------------------------------

}; //namespace Biblio3D

}; //namespace BBib

