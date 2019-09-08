//---------------------------------------------------------------------------
#include <math.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "BEsfera.h"
//---------------------------------------------------------------------------
namespace BBib
{

namespace Biblio3D
{

//---------------------------------------------------------------------------
const char* BEsfera::MENSAGEM_ERRO[] = {
    "",
    "Raio deve ser positivo.",                  //1
    ""
};
//---------------------------------------------------------------------------
BEsfera::BEsfera(void)
    : BObjeto3D(), aCentro(0, 0, 0), adRaio(1)
{
    /**
    Cria uma esfera com centro em (0, 0, 0) e raio 1.
    */
}
//---------------------------------------------------------------------------
BEsfera::BEsfera(const BEsfera& x)
    : BObjeto3D(x), aCentro(x.aCentro), adRaio(x.adRaio)
{
    /**
    Cria uma cópia de x.
    */
}
//---------------------------------------------------------------------------
BEsfera::BEsfera(const BPonto3D& Centro, double Raio)
    : BObjeto3D(), aCentro(Centro), adRaio(Raio)
{
    /**
    Cria uma esfera com centro e raio fornecidos.
    O raio deve saer positivo. Caso contrário, uma exceção do tipo
    BEsfera::BExcecaoValorForaFaixa é lançada.
    */
    if(Raio <= 0)
    {
        throw BExcecaoValorForaFaixa(MENSAGEM_ERRO[1]);
    }
}
//---------------------------------------------------------------------------
BEsfera::~BEsfera(void)
{
    /**
    Libera o espaço ocupado pela esfera.
    */
}
//---------------------------------------------------------------------------
BEsfera& BEsfera::operator = (const BEsfera& x)
{
    /**
    Transforma a esfera em uma cópia de x.
    */
    if(this != &x)
    {
        aCentro = x.aCentro;
        adRaio  = x.adRaio;
    }
    return *this;
}
//---------------------------------------------------------------------------
bool BEsfera::ContemPonto(const BPonto3D& Ponto) const
{
    /**
    Retorna true se o ponto se encontra na superfície ou no interior
    da esfera. Caso contrário, retorna false.
    */
    return Distancia(Ponto, aCentro) <= adRaio;
}
//---------------------------------------------------------------------------
void BEsfera::DefCentro(const BPonto3D& Centro)
{
    /**
    Define o centro da esfera.
    */
    aCentro = Centro;
}
//---------------------------------------------------------------------------
void BEsfera::DefRaio(double Raio)
{
    /**
    Define o raio da esfera.
    O raio deve saer positivo. Caso contrário, uma exceção do tipo
    BEsfera::BExcecaoValorForaFaixa é lançada.
    */
    if(Raio <= 0)
    {
        throw BExcecaoValorForaFaixa(MENSAGEM_ERRO[1]);
    }
    adRaio = Raio;
}
//---------------------------------------------------------------------------
double BEsfera::LeArea(void) const
{
    /**
    Retorna a área da esfera.
    */
    return 4 * M_PI * adRaio * adRaio;
}
//---------------------------------------------------------------------------
const BPonto3D& BEsfera::LeCentro(void) const
{
    /**
    Retorna o centro da esfera.
    */
    return aCentro;
}
//---------------------------------------------------------------------------
double BEsfera::LeRaio(void) const
{
    /**
    Retorna o raio da esfera.
    */
    return adRaio;
}
//---------------------------------------------------------------------------
double BEsfera::LeVolume(void) const
{
    /**
    Retorna o volume da esfera.
    */
    return 4 * M_PI * adRaio * adRaio * adRaio / 3;
}
//---------------------------------------------------------------------------
int BEsfera::SituaPonto(const BPonto3D& Ponto) const
{
/*
      Esta função retorna:

   -1    se o ponto se encontra no interior da esfera;

    0    se o ponto se encontra na superfície da esfera;
    
    1    se o ponto se encontra fora da esfera.
*/
    double dif = Distancia(Ponto, aCentro) - adRaio;

    if(dif > Tolerancia()) return 1;
    if(dif < -Tolerancia()) return -1;
    return 0;
}
//---------------------------------------------------------------------------


}; //namespace Biblio3D

}; //namespace BBib
//---------------------------------------------------------------------------

