//---------------------------------------------------------------------------
#include <math.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "BCilindro.h"
//---------------------------------------------------------------------------
namespace BBib
{

namespace Biblio3D
{

//---------------------------------------------------------------------------
const char* BCilindro::MENSAGEM_ERRO[] = {
    "",
    "Raio deve ser positivo.",                  //1
    ""
};
//---------------------------------------------------------------------------
BCilindro::BCilindro(void)
    : BObjeto3D(), aEixo(0, 0, 0, 0, 0, 1), adRaio(1)
{
    /**
    Cria um cilindro com eixo entre os pontos (0, 0, 0) e (0, 0, 1)
    e raio 1.
    */
}
//---------------------------------------------------------------------------
BCilindro::BCilindro(const BCilindro& x)
    : BObjeto3D(x), aEixo(x.aEixo), adRaio(x.adRaio)
{
    /**
    Cria uma cópia de x.
    */
}
//---------------------------------------------------------------------------
BCilindro::BCilindro(const BSegmentoReta3D& Eixo, double Raio)
    : BObjeto3D(), aEixo(Eixo), adRaio(Raio)
{
    /**
    Cria um cilindro a partir do eixo e do raio fornecidos. O raio
    deve saer positivo. Caso contrário, uma exceção do tipo
    BCilindro::BExcecaoValorForaFaixa é lançada.
    */
    if(Raio <= 0)
    {
        throw BExcecaoValorForaFaixa(MENSAGEM_ERRO[1]);
    }
}
//---------------------------------------------------------------------------
BCilindro::BCilindro(const BPonto3D& CentroBase1, const BPonto3D& CentroBase2, double Raio)
    : BObjeto3D(), aEixo(CentroBase1, CentroBase2), adRaio(Raio)
{
    /**
    Cria um cilindro com eixo entre os pontos fornecidos e raio fornecido.
    O raio deve saer positivo. Caso contrário, uma exceção do tipo
    BCilindro::BExcecaoValorForaFaixa é lançada.
    */
    if(Raio <= 0)
    {
        throw BExcecaoValorForaFaixa(MENSAGEM_ERRO[1]);
    }
}
//---------------------------------------------------------------------------
BCilindro::~BCilindro(void)
{
    /**
    Libera a memória ocupada pelo cilindro.
    */
}
//---------------------------------------------------------------------------
BCilindro& BCilindro::operator = (const BCilindro& x)
{
    /**
    Transforma o cilindro em uma cópia de x.
    */
    if(this != &x)
    {
        aEixo  = x.aEixo;
        adRaio = x.adRaio;
    }
    return *this;
}
//---------------------------------------------------------------------------
bool BCilindro::ContemPonto(const BPonto3D& Ponto) const
{
    /**
    Retorna true se o ponto se situar na superfície ou no interior
    do cilindro. Caso contrário, retorna false.
    */
    return SituaPonto(Ponto) <= 0;
}
//---------------------------------------------------------------------------
bool BCilindro::ContemPonto(double x, double y, double z) const
{
    /**
    Retorna true se o ponto (x, y, z) se situar na superfície ou no interior
    do cilindro. Caso contrário, retorna false.
    */
    return SituaPonto(BPonto3D(x, y, z)) <= 0;
}
//---------------------------------------------------------------------------
void BCilindro::DefCentrosBases(const BPonto3D& Centro1, const BPonto3D& Centro2)
{
    /**
    Define os centros das bases do cilindro.
    */
    aEixo.DefPontos(Centro1, Centro2);
}
//---------------------------------------------------------------------------
void BCilindro::DefCentrosBases(double x1, double y1, double z1,
    double x2, double y2, double z2)
{
    /**
    Define os centros das bases do cilindro como os pontos (x1, y1, z1) e
    (x2, y2, z2).
    */
    aEixo.DefPontos(x1, y1, z1, x2, y2, z2);
}
//---------------------------------------------------------------------------
void BCilindro::DefRaio(double Raio)
{
    /**
    Define o raio do cilindro.
    O raio deve saer positivo. Caso contrário, uma exceção do tipo
    BCilindro::BExcecaoValorForaFaixa é lançada.
    */
    if(Raio <= 0)
    {
        throw BExcecaoValorForaFaixa(MENSAGEM_ERRO[1]);
    }
    adRaio = Raio;
}
//---------------------------------------------------------------------------
double BCilindro::LeAltura(void) const
{
    /**
    Retorna a altura do cilindro, ou seja, a distância entre as suas bases.
    */
    return aEixo.LeComprimento();
}
//---------------------------------------------------------------------------
double BCilindro::LeAreaBase(void) const
{
    /**
    Retorna a área da base do cilindro.
    */
    return M_PI * adRaio * adRaio;
}
//---------------------------------------------------------------------------
double BCilindro::LeAreaLateral(void) const
{
    /**
    Retorna a área lateral do cilindro.
    */
    return 2 * M_PI * adRaio * aEixo.LeComprimento();
}
//---------------------------------------------------------------------------
double BCilindro::LeAreaTotal(void) const
{
    /**
    Retorna a área total do cilindro.
    */
    return LeAreaLateral() + 2 * LeAreaBase();
}
//---------------------------------------------------------------------------
const BPonto3D& BCilindro::LeCentroBase1(void) const
{
    /**
    Retorna o centro da base 1.
    */
    return aEixo.LePonto1();
}
//---------------------------------------------------------------------------
const BPonto3D& BCilindro::LeCentroBase2(void) const
{
    /**
    Retorna o centro da base 2.
    */
    return aEixo.LePonto2();
}
//---------------------------------------------------------------------------
double BCilindro::LeRaio(void) const
{
    /**
    Retorna o raio do cilindro.
    */
    return adRaio;
}
//---------------------------------------------------------------------------
double BCilindro::LeVolume(void) const
{
    /**
    Retorna o volume do cilindro.
    */
    return M_PI * adRaio * adRaio * aEixo.LeComprimento();
}
//---------------------------------------------------------------------------
int BCilindro::SituaPonto(const BPonto3D& Ponto) const
{
    /**
    Esta função retorna:

      -1   se o ponto se encontra no interior do cilindro;

      0    se o ponto se encontra na superfície do cilindro;

      1    se o ponto se encontra fora do cilindro.
    */
    BVetor3D vet1, vet2;
    double aux, aux2;
    double distq;
    double m;

    vet1 = aEixo;
    aux = vet1 * vet1;
    // Verificar a linha abaixo. Se aux < ZERO, deve retornar um erro
    // de alguma maneira.
    if(aux < ToleranciaAoQuadrado()) return 1;
    vet2 = Ponto - aEixo.LePonto1();
    aux2 = vet1 * vet2;
    m = aux2 / aux;
    if((m < 0) || (m > 1)) return 1;
    distq = vet2 * vet2 + m * (m * aux - 2 * aux2) - adRaio * adRaio;
    if(fabs(distq) < Tolerancia()) return 0;
    if(distq < 0)
    {
        if((m == 0) || (m == 1))
            return 0;
        else
            return -1;
    }
    return 1;
}
//---------------------------------------------------------------------------
int BCilindro::SituaPonto(double x, double y, double z) const
{
    /**
    Esta função retorna:

      -1   se o ponto (x, y, z) se encontra no interior do cilindro;

      0    se o ponto (x, y, z) se encontra na superfície do cilindro;

      1    se o ponto (x, y, z) se encontra fora do cilindro.
    */
    return SituaPonto(BPonto3D(x, y, z));
}
//---------------------------------------------------------------------------

}; //namespace Biblio3D

}; //namespace BBib
//---------------------------------------------------------------------------

