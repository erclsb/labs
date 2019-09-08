#include <math.h>
#pragma hdrstop

#include "BPonto2D.h"

namespace BBib {

namespace Biblio2D {

BPonto2D::BPonto2D(void) {
    /**
     * Cria um ponto com as coordenadas (0, 0).
     */
    x = 0;
    y = 0;
}

BPonto2D::BPonto2D(double xx, double yy) {
    /**
     * Cria um ponto com as coordenadas (xx, yy).
     */
    x = xx;
    y = yy;
}

BPonto2D::BPonto2D(const BPonto2D& p) {
    /**
     * Cria uma cópia de p.
     */
    x = p.x;
    y = p.y;
}

BPonto2D::~BPonto2D(void) {
    /**
     * Libera a memória ocupada pelo ponto.
     */
}

BPonto2D& BPonto2D::operator = (const BPonto2D& p) {
    /**
     * Transforma o ponto em uma cópia de p.
     */
    x = p.x;
    y = p.y;
    return *this;
}

bool BPonto2D::operator == (const BPonto2D &p) const {
    /**
     * Retorna true se os dois pontos tiverem as mesmas coordenadas.
     * Caso contrário, retorna false.
     */
    return ((x == p.x) && (y == p.y));
}

bool BPonto2D::operator != (const BPonto2D &p) const {
    /**
     * Retorna false se os dois pontos tiverem as mesmas coordenadas.
     * Caso contrário, retorna true.
     */
    return ((x != p.x) || (y != p.y));
}

void BPonto2D::DefCoordenadas(double xx, double yy) {
    /**
     * Define as coordenadas retangulares do ponto.
     */
    x = xx;
    y = yy;
}

void BPonto2D::DefCoordenadasPolares(double dist, double ang) {
    /**
     * Define as coordenadas polares do ponto.
     */
    x = dist * cos(ang);
    y = dist * sin(ang);
}

double Distancia(const BPonto2D& p1, const BPonto2D& p2) {
    /**
     * Retorna a distância entre os dois pontos fornecidos.
     */
    double x = p2.x - p1.x;
    double y = p2.y - p1.y;

    return sqrt(x*x + y*y);
}

double arg(const BPonto2D& p)
{
    /**
     * Retorna o ângulo formado pela reta que liga a origem
     * até o ponto com o eixo X.
     */
    return atan2(p.y, p.x);
}

BPonto2D PontoMedio(const BPonto2D& p1, const BPonto2D& p2) {
    /**
     * Retorna o ponto médio entre os pontos p1 e p2.
     */
    return BPonto2D(0.5 * (p1.x + p2.x), 0.5 * (p1.y + p2.y));
}

bool Colineares(const BPonto2D& p1, const BPonto2D& p2, const BPonto2D& p3) {
    /**
     * Retorna true se os três pontos forem colineares.
     * Caso contrário, retorna false.
     */
    double x1 = p2.X() - p1.X();
    double y1 = p2.Y() - p1.Y();
    double x2 = p3.X() - p1.X();
    double y2 = p3.Y() - p1.Y();
    double det = x1 * y2 - x2 * y1;

    return (fabs(det) < BPonto2D::Tolerancia());
}

}; //namespace Biblio2D

}; //namespace BBib

