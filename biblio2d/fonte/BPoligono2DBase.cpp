#include <stdlib.h>
#include <math.h>
#pragma hdrstop

#include "BPoligono2DBase.h"
#include "BVetor2D.h"

namespace BBib {

namespace Biblio2D {

BPoligono2DBase::BPoligono2DBase(void)
        : BObjeto2D() {
    /**
     * Cria um polígono sem que seja definido o número
     * de vértices.
     */
}

BPoligono2DBase::BPoligono2DBase(const BPoligono2DBase& x)
        : BObjeto2D(x) {
    /**
     * Cria uma cópia de x
     */
    aVertice = x.aVertice;
}

BPoligono2DBase::BPoligono2DBase(int NumVertices)
        : BObjeto2D() {
    /**
     * Cria um polígono com o número de vértices definido.
     */
    aVertice.resize(NumVertices);
}

BPoligono2DBase::~BPoligono2DBase(void) {
    /**
     * Libera a memória ocupada pelo polígono.
     */
}

BPoligono2DBase& BPoligono2DBase::operator = (const BPoligono2DBase& x) {
    /**
     * Transforma o objeto em uma cópia de x.
     */
    if(this != &x) {
        aVertice = x.aVertice;
    }
    return *this;
}

double BPoligono2DBase::Area(void) const {
    /**
     * Retorna a área do polígono.
     */
    int i;
    int j;
    double area = 0;
    int n = aVertice.size();

    for (i = 0; i < n; i++) {
        j = (i + 1) % n;
        area += aVertice[i].X() * aVertice[j].Y();
        area -= aVertice[i].Y() * aVertice[j].X();
    }
    area /= 2;
    return fabs(area);
}

bool BPoligono2DBase::ContemPonto(const BPonto2D& Ponto) const {
    /**
     * Retorna true se o ponto estiver no interior ou na superfície
     * do cilindro. Caso contrário, retorna false.
     */
    int i;
    int j;
    bool right;
    bool inside = false;
    int n = aVertice.size();

    for (i = 0, j = n - 1; i < n; j = i++) {
        if ((aVertice[i].Y() <= Ponto.Y()) != (aVertice[j].Y()<= Ponto.Y())) {
            right = aVertice[i].X();
            if ((aVertice[i].X() >= Ponto.X()) != (aVertice[j].X() >= Ponto.X())) {
	            if ((Ponto.X() - aVertice[i].X())
                        * (aVertice[j].Y() - aVertice[i].Y())
                        < (aVertice[j].X() - aVertice[i].X())
                        * (Ponto.Y() - aVertice[i].Y())) {
	                inside = !inside;
                }
            }
            else if (right) {
                inside = !inside;
            }
        }
    }
    return inside;
}

void BPoligono2DBase::DefNumeroVertices(int NumVertices) {
    /**
     * Define o número de vértices do polígono.
     */
    aVertice.resize(NumVertices);
}

void BPoligono2DBase::DefVertice(unsigned int Indice, const BPonto2D& Vertice) {
    /**
     * Define o vértice de índice fornecido.
     */
    if(Indice >= aVertice.size()) {
        throw BExcecaoValorForaFaixa("Índice do vértice fora da faixa.");
    }
    aVertice[Indice] = Vertice;
}

void BPoligono2DBase::DefVertices(const BPonto2D* Vertice) {
    /**
     * Define todos os vértices do polígono a partir de um vetor fornecido.
     */
    int n = aVertice.size();

    for(int i = 0; i < n; i++) {
        aVertice[i] = Vertice[i];
    }
}

void BPoligono2DBase::DefVertices(const float* X, const float* Y) {
    /**
     * Define todos os vértices do polígono a partir das coordenadas
     * fornecidas.
     */
    int n = aVertice.size();

    for(int i = 0; i < n; i++) {
        aVertice[i].DefCoordenadas(X[i], Y[i]);
    }
}

void BPoligono2DBase::DefVertices(const double* X, const double* Y) {
    /**
     * Define todos os vértices do polígono a partir das coordenadas
     * fornecidas.
     */
    int n = aVertice.size();

    for(int i = 0; i < n; i++) {
        aVertice[i].DefCoordenadas(X[i], Y[i]);
    }
}

double Distancia(const BPoligono2DBase& Poligono, const BPonto2D& Ponto) {
    /**
     * Retorna a distância entre o polígono e o ponto.
     */
    if(Poligono.ContemPonto(Ponto)) {
        return 0;
    }

    int n = Poligono.aVertice.size();
    /* TODO : Rever DistanciaPontoSegmento */
    double DistanciaPontoSegmento = 1;
    double distancia = DistanciaPontoSegmento;
    //(Ponto, Poligono.aVertice[n - 1], Poligono.aVertice[0])

    for(int i = 1; i < n; i++)
    {
        distancia = min(distancia, DistanciaPontoSegmento);
        //(Ponto, Poligono.aVertice[i-1], Poligono.aVertice[i])
    }
    return distancia;
}

double Distancia(const BPonto2D& Ponto, const BPoligono2DBase& Poligono) {
    /**
     * Retorna a distância entre o polígono e o ponto.
     */
    return Distancia(Poligono, Ponto);
}

bool BPoligono2DBase::InterceptaSegmento(const BPonto2D& A, const BPonto2D& B) const {
    /**
     * Retorna true se o polígono intercepta o segmento de reta formado
     * pelos pontos A e B. Caso contrário, retorna false.
     */
    int n = aVertice.size();
    double denom;
    double r;
    double s;

    for (int i = 0; i < n; i++) {
        const BPonto2D& C = aVertice[i];
        const BPonto2D& D = aVertice[(i+1) % n];

        denom = ((B.X() - A.X()) * (D.Y() - C.Y()) - (B.Y() - A.Y()) * (D.X() - C.X()));
        r = ((A.Y() - C.Y()) * (D.X() - C.X()) - (A.X() - C.X()) * (D.Y() - C.Y()));
        s = ((A.Y() - C.Y()) * (B.X() - A.X()) - (A.X() - C.X()) * (B.Y() - A.Y()));
        if(fabs(denom) > ZERO) {
            r /= denom;
            s /= denom;
            if (0 < r && r < 1 && 0 < s && s < 1) {
                return true;
            }
        }
    }
    return false;
}

int BPoligono2DBase::LeNumeroVertices(void) const {
    return aVertice.size();
}

const BPonto2D& BPoligono2DBase::LeVertice(unsigned int Indice) const {
    /**
     * Retorna o vértice referente ao índice fornecido.
     */
    if(Indice >= aVertice.size()) {
        throw BExcecaoValorForaFaixa("Índice do vértice fora da faixa.");
    }
    return aVertice[Indice];
}

bool BPoligono2DBase::Valido(void) const {
    /**
     * Retorna true se o polígono for válido. Caso contrário, retorna
     * false. Um polígono é válido se nenhum de seus lados se cruzarem. 
     */
    int i, j;
    int aux;
    double dx, dy;
    int n = aVertice.size();

    for(i = 1; i < n; i++) {
        aux = i - 1;
        if(InterceptaSegmento(aVertice[aux], aVertice[i])) {
            return false;
        }
        for(j = i; j < n; j++) {
            dx = aVertice[aux].X() - aVertice[j].X();
            dy = aVertice[aux].Y() - aVertice[j].Y();
            if((dx*dx + dy*dy) < ZERO) {
                return false;
            }
        }
    }
    return true;
}

bool LadosCoincidentes(const BPoligono2DBase& P1, const BPoligono2DBase& P2) {
    /**
     * Retorna true se os polígonos tiverem um lado coincidente.
     * Caso contrário, retorna false.
     */
    int i, j;
    int n1 = P1.aVertice.size();
    int n2 = P2.aVertice.size();
    double denom;
    double r, s;
    double razao1, razao2;
    BVetor2D AB, CD, AC, AD;
    const double ZERO = BPoligono2DBase::ZERO;

    for (i = 0; i < n1; i++) {
        const BPonto2D& A = P1.aVertice[i];
        const BPonto2D& B = P1.aVertice[(i+1) % n1];
        AB = B - A;
        for (j = 0; j < n2; j++) {
            const BPonto2D& C = P2.aVertice[j];
            const BPonto2D& D = P2.aVertice[(j+1) % n2];

            if((A == C) && (B == D)) return true;
            if((A == D) && (B == C)) return true;
            CD = D - C;
            denom = AB.X() * CD.Y() - AB.Y() * CD.X();
            if(fabs(denom) < BPoligono2DBase::ZERO) {
                AC = C - A;
                AD = D - A;
                r = AC.Y() * CD.X() - AC.X() * CD.Y();
                s = AD.Y() * CD.X() - AD.X() * CD.Y();
                if((fabs(r) < ZERO) && (fabs(s) < ZERO)) {
                    if(fabs(AB.X()) > ZERO) {
                        razao1 = AC.X() / AB.X();
                        razao2 = AD.X() / AB.X();
                    } else if(fabs(AB.Y()) > ZERO) {
                        razao1 = AC.Y() / AB.Y();
                        razao2 = AD.Y() / AB.Y();
                    } else {
                        razao1 = 0;
                        razao2 = 0;
                    }
                    if(razao1 > 0 && razao1 < 1) {
                        return true;
                    }
                    if(razao2 > 0 && razao2 < 1) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

}; //namespace Biblio2D

}; //namespace BBib

