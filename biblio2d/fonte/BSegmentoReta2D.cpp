#include <math.h>
#pragma hdrstop

#include "BSegmentoReta2D.h"
#include "BVetor2D.h"

namespace BBib {

namespace Biblio2D {

BSegmentoReta2D::BSegmentoReta2D(void)
        : BObjeto2D() {
    /**
     * Cria um segmento de reta sem definir seus pontos.
     */
}

BSegmentoReta2D::BSegmentoReta2D(const BSegmentoReta2D& x)
        : BObjeto2D(x) {
    /**
     * Cria uma cópia de x.
     */
    *this = x;
}

BSegmentoReta2D::BSegmentoReta2D(BPonto2D p1, BPonto2D p2)
        : BObjeto2D() {
    /**
     * Cria um segmento de reta entre os pontos p1 e p2.
     */
    aPonto1 = p1;
    aPonto2 = p2;
}

BSegmentoReta2D::BSegmentoReta2D(double x1, double y1, double x2, double y2)
        : BObjeto2D() {
    /**
     * Cria um segmento de reta entre os pontos (x1, y1) e (x2, y2).
     */
    aPonto1.DefCoordenadas(x1, y1);
    aPonto2.DefCoordenadas(x2, y2);
}

BSegmentoReta2D::~BSegmentoReta2D(void) {
    /**
     * Libera a memória ocupada pelo segmento de reta.
     */
}

BSegmentoReta2D& BSegmentoReta2D::operator = (const BSegmentoReta2D& x) {
    /**
     * Transforma o segmento de reta em uma cópia de x.
     */
    if(this != &x) {
        aPonto1 = x.aPonto1;
        aPonto2 = x.aPonto2;
    }
    return *this;
}

BSegmentoReta2D::operator BVetor2D(void) const {
    /**
     * Retorna o vetor do segmento de reta.
     */
    return aPonto2 - aPonto1;
}

double BSegmentoReta2D::Comprimento(void) const {
    /**
     * Retorna o comprimento do segmento de reta.
     */
    return Distancia(aPonto1, aPonto2);
}

void BSegmentoReta2D::DefPonto1(const BPonto2D& Ponto) {
    /**
     * Define o primeiro ponto do segmento de reta.
     */
    aPonto1 = Ponto;
}

void BSegmentoReta2D::DefPonto1(double x, double y) {
    /**
     * Define o primeiro ponto do segmento de reta.
     */
    aPonto1.DefCoordenadas(x, y);
}

void BSegmentoReta2D::DefPonto2(const BPonto2D& Ponto) {
    /**
     * Define o segundo ponto do segmento de reta.
     */
    aPonto2 = Ponto;
}

void BSegmentoReta2D::DefPonto2(double x, double y) {
    /**
     * Define o segundo ponto do segmento de reta.
     */
    aPonto2.DefCoordenadas(x, y);
}

double Distancia(const BSegmentoReta2D& Segmento, const BPonto2D& Ponto) {
    /**
     * Retorna a distância entre o segmento de reta e o ponto.
     */
    BVetor2D vet1, vet2;
    double aux, aux2;
    double m;

    vet1 = Segmento.aPonto2 - Segmento.aPonto1;
    aux = vet1 * vet1;
    if(aux < BSegmentoReta2D::ToleranciaAoQuadrado()) {
        return Distancia(Ponto, Segmento.aPonto1);
    }
    vet2 = Ponto - Segmento.aPonto1;
    aux2 = vet1 * vet2;
    m = aux2 / aux;
    if(m < 0) {
        return Distancia(Ponto, Segmento.aPonto1);
    }
    if(m > 1) {
        return Distancia(Ponto, Segmento.aPonto2);
    }
    return fabs(vet1.X() * vet2.Y() - vet1.Y() * vet2.X()) / sqrt(aux);
}

double Distancia(const BPonto2D& Ponto, const BSegmentoReta2D& Segmento) {
    /**
     * Retorna a distância entre o segmento de reta e o ponto.
     */
    return Distancia(Segmento, Ponto);
}

const BPonto2D& BSegmentoReta2D::LePonto1(void) const {
    /**
     * Retorna o primeiro ponto do segmento de reta.
     */
    return aPonto1;
}

const BPonto2D& BSegmentoReta2D::LePonto2(void) const {
    /**
     * Retorna o segundo ponto do segmento de reta.
     */
    return aPonto2;
}

}; //namespace Biblio3D

}; //namespace BBib

