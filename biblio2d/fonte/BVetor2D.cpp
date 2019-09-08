#include <math.h>
#pragma hdrstop

#include "BVetor2D.h"

namespace BBib {

namespace Biblio2D {

const char* BVetor2D::MENSAGEM_ERRO[] = {
    "Divis�o por zero.",                                        //0
    "Imposs�vel criar vetor unit�rio a partir do vetor nulo."   //1
};

BVetor2D::BVetor2D(void)
        : BObjeto2D() {
    /**
    Cria um vetor com coordenadas (0, 0).
    */
    x = 0;
    y = 0;
}

BVetor2D::BVetor2D(double xx, double yy)
        : BObjeto2D() {
    /**
    Cria um vetor com coordenadas (xx, yy).
    */
    x = xx;
    y = yy;
}

BVetor2D::BVetor2D(const BVetor2D& v)
        : BObjeto2D(v)  {
    /**
    Cria uma c�pia de v.
    */
    x = v.x;
    y = v.y;
}

BVetor2D::~BVetor2D(void) {
    /**
    Libera a mem�ria ocupada pelo vetor.
    */
}

BVetor2D& BVetor2D::operator = (const BVetor2D& v) {
    /**
    Transforma o vetor em uma c�pia de v.
    */
    x = v.x;
    y = v.y;
    return *this;
}

bool BVetor2D::operator == (const BVetor2D& v) {
    /**
    Retorna true se os dois vetores tiverem as mesmas coordenadas.
    Caso contr�rio, retorna false.
    */
    return (x == v.x) && (y == v.y);
}

bool BVetor2D::operator != (const BVetor2D& v) {
    /**
    Retorna false se os dois vetores tiverem as mesmas coordenadas.
    Caso contr�rio, retorna true.
    */
    return (x != v.x) || (y != v.y);
}

BVetor2D& BVetor2D::operator += (const BVetor2D& v) {
    /**
    Acrescenta v ao vetor.
    */
    x += v.x;
    y += v.y;
    return *this;
}

BVetor2D& BVetor2D::operator += (double d) {
    /**
    Acrescenta o vetor (d, d) ao vetor.
    */
    x += d;
    y += d;
    return *this;
}

BVetor2D& BVetor2D::operator -= (const BVetor2D& v) {
    /**
    Subtrai v do vetor.
    */
    x -= v.x;
    y -= v.y;
    return *this;
}

BVetor2D& BVetor2D::operator -= (double d) {
    /**
    Subtrai o vetor (d, d) do vetor.
    */
    x -= d;
    y -= d;
    return *this;
}

BVetor2D& BVetor2D::operator *= (double d) {
    /**
    Multiplica o vetor pelo escalar d.
    */
    x *= d;
    y *= d;
    return *this;
}

BVetor2D& BVetor2D::operator /= (double d) {
    /**
    Divide o vetor pelo escalar d.
    */
    if(d == 0) {
        throw BExcecaoMatematica(MENSAGEM_ERRO[0]);
    }
    x /= d;
    y /= d;
    return *this;
}

BVetor2D operator + (const BVetor2D& v1, const BVetor2D& v2) {
    /**
    Retorna a soma dos vetores v1 e v2.
    */
    return BVetor2D(v1.x + v2.x, v1.y + v2.y);
}

BVetor2D operator + (double d, const BVetor2D& v) {
    /**
    Retorna a soma dos vetores v e (d, d).
    */
    return BVetor2D(v.x + d, v.y + d);
}

BVetor2D operator + (const BVetor2D& v, double d) {
    /**
    Retorna a soma dos vetores v e (d, d).
    */
    return BVetor2D(v.x + d, v.y + d);
}

BPonto2D operator + (const BPonto2D& p, const BVetor2D& v) {
    /**
    Retorna o ponto resultante da soma do ponto p
    com o vetor v.
    */
    return BPonto2D(v.x + p.X(), v.y + p.Y());
}

BVetor2D operator - (const BVetor2D& v)
{
    /**
    Retorna o sim�trico de v.
    */
    return BVetor2D(-v.x, -v.y);
}

BVetor2D operator - (const BPonto2D& p1, const BPonto2D& p2) {
    /**
    Retorna o vetor entre os pontos p1 e p2.
    */
    return BVetor2D(p1.X() - p2.X(), p1.Y() - p2.Y());
}

BVetor2D operator - (const BVetor2D& v1, const BVetor2D& v2) {
    /**
    Retorna a diferen�a entre os vetores v1 e v2.
    */
    return BVetor2D(v1.x - v2.x, v1.y - v2.y);
}

BVetor2D operator - (const BVetor2D& v, double d) {
    /**
    Retorna a diferen�a entre os vetores v e (d, d).
    */
    return BVetor2D(v.x - d, v.y - d);
}

double operator * (const BVetor2D& v1, const BVetor2D& v2) {
    /**
    Retorna o produto escalar entre os vetores v1 e v2.
    */
    return v1.x * v2.x + v1.y * v2.y;
}

BVetor2D operator * (double d, const BVetor2D& v) {
    /**
    Retorna o produto do vetor v pelo escalar d.
    */
    return BVetor2D(v.x * d, v.y * d);
}

BVetor2D operator * (const BVetor2D& v, double d) {
    /**
    Retorna o produto do vetor v pelo escalar d.
    */
    return BVetor2D(v.x * d, v.y * d);
}

BVetor2D operator / (const BVetor2D& v, double d) {
    /**
    Retorna a divis�o do vetor v pelo escalar d.
    */
    if(d == 0) {
        throw BVetor2D::BExcecaoMatematica(BVetor2D::MENSAGEM_ERRO[1]);
    }
    return BVetor2D(v.x / d, v.y / d);
}

double Angulo(const BVetor2D& v1, const BVetor2D& v2)
{
    /**
    Retorna o �ngulo, em radianos, entre dois vetores. O �ngulo sesultante
    est� compreendido entre 0 e PI.

    Se um ou mais vetores forem nulos, a fun��o retorna 0.
    */
    double mod1 = abs(v1);
    double mod2 = abs(v2);

    if((mod1 == 0) || (mod2 == 0)) {
        return 0;
    }
    return acos((v1 * v2) / (mod1 * mod2));
}

void BVetor2D::DefCoordenadas(double xx, double yy) {
    /**
    Define as coordenadas retangulares do vetor.
    */
    x = xx;
    y = yy;
}

void BVetor2D::DefCoordenadasPolares(double dist, double ang) {
    /**
    Define as coordenadas polares do vetor.
    */
    x = dist * cos(ang);
    y = dist * sin(ang);
}

double abs(const BVetor2D& v) {
    /**
    Retorna o m�dulo do vetor v.
    */
    return sqrt(v.x * v.x + v.y * v.y);
}

double arg(const BVetor2D& v) {
    /**
    Retorna o �ngulo entre o vetor v e o eixo X.
    */
    return atan2(v.y, v.x);
}

double norm(const BVetor2D& v) {
    /**
    Retorna o quadrado do m�dulo do vetor v.
    */
    return v.x * v.x + v.y * v.y;
}

BVetor2D unit(const BVetor2D& v) {
    /**
    Retorna o vetor unit�rio de mesma dire��o e sentido que o vetor v.
    */
    double mod = abs(v);

    if(mod == 0) {
        throw BVetor2D::BExcecaoMatematica(BVetor2D::MENSAGEM_ERRO[1]);
    }
    return BVetor2D(v.x / mod, v.y / mod);
}

}; //namespace Biblio2D

}; //namespace BBib

