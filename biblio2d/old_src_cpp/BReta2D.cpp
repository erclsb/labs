#include <math.h>
#pragma hdrstop

#include "BReta2D.h"

namespace BBib {

namespace Biblio2D {

const char* BReta2D::MENSAGEM_ERRO[] = {
    "Os dois pontos são coincidentes.",             //0
    "As duas retas não são concorrentes."           //1
};

BReta2D::BReta2D(void)
        : aPonto(0, 0), aVetor(1, 0) {
}

BReta2D::BReta2D(const BReta2D& reta)
        : aPonto(reta.aPonto), aVetor(reta.aVetor) {
}

BReta2D::BReta2D(const BPonto2D& p, const BVetor2D& v)
        : aPonto(p), aVetor(v) {
}

BReta2D::BReta2D(const BPonto2D& p1, const BPonto2D& p2)
        : aPonto(p1) {
    double mod = abs(p2 - p1);

    if(mod > Tolerancia()) {
        aVetor.DefCoordenadas((p2.X() - p1.X()) / mod, (p2.Y() - p1.Y()) / mod);
    } else {
        throw BExcecaoMatematica(MENSAGEM_ERRO[0]);
    }
}

BReta2D::~BReta2D(void) {
}

BReta2D& BReta2D::operator = (const BReta2D& reta) {
    if(this != &reta) {
        aPonto = reta.aPonto;
        aVetor = reta.aVetor;
    }
    return *this;
}

void BReta2D::Def(const BPonto2D& p1, const BPonto2D& p2) {
    double mod = abs(p2 - p1);

    if(mod > Tolerancia()) {
        aPonto = p1;
        aVetor.DefCoordenadas((p2.X() - p1.X()) / mod, (p2.Y() - p1.Y()) / mod);
    } else {
        throw BExcecaoMatematica(MENSAGEM_ERRO[0]);
    }
}

void BReta2D::Def(const BPonto2D& p, const BVetor2D& v) {
    aPonto = p;
    aVetor = v;
}

const BPonto2D& BReta2D::LePonto(void) const {
    return aPonto;
}

const BVetor2D& BReta2D::LeVetor(void) const {
    return aVetor;
}

double Distancia(const BReta2D& reta, const BPonto2D p) {
    double x1 = p.X() - reta.aPonto.X();
    double y1 = p.Y() - reta.aPonto.Y();
    double x2 = reta.aVetor.X();
    double y2 = reta.aVetor.Y();

    return fabs(x1 * y2 - x2 * y1) / abs(reta.aVetor);
}

BPonto2D Intersecao(const BReta2D& reta1, const BReta2D& reta2) {
    const double ZERO2 = BReta2D::ToleranciaAoQuadrado();
    double x1 = reta1.aVetor.X();
    double y1 = reta1.aVetor.Y();
    double x2 = reta2.aVetor.X();
    double y2 = reta2.aVetor.Y();
    double aux1 = x1*y2 - y1*x2;
    double aux2;
    BPonto2D p;

    if(fabs(aux1) < ZERO2) {
        throw BReta2D::BExcecaoMatematica(BReta2D::MENSAGEM_ERRO[1]);
    }
    double px1 = reta1.aPonto.X();
    double py1 = reta1.aPonto.Y();
    double px2 = reta2.aPonto.X();
    double py2 = reta2.aPonto.Y();
    aux2 = ((py1 - py2) - (px1 - px2)) / aux1;
    p.X() = aux2 * (x1 * x2);
    p.Y() = aux2 * (y1 * y2);
    return p;
}

bool Ortogonais(const BReta2D& reta1, const BReta2D& reta2) {
    return fabs(reta1.aVetor * reta2.aVetor) < BReta2D::ToleranciaAoQuadrado();
}

bool Paralelas(const BReta2D& reta1, const BReta2D& reta2) {
    double x1 = reta1.aVetor.X();
    double y1 = reta1.aVetor.Y();
    double x2 = reta2.aVetor.X();
    double y2 = reta2.aVetor.Y();

    return fabs(x1*y2 - y1*x2) < BReta2D::ToleranciaAoQuadrado();
}

}; //namespace Biblio2D

}; //namespace BBib

