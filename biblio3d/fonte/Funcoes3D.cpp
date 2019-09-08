//---------------------------------------------------------------------------
#pragma hdrstop
//-------------------------------------------------------------------------
#include <math.h>
#include "Funcoes3D.h"
//---------------------------------------------------------------------------
bool GeraNovoSistema(BVetor3D& zz, BVetor3D& xx, BVetor3D& yy)
{
/*
      Fornecido o vetor zz (unitario ou não), esta função calcula
   os vetores xx e yy (unitários) de modo que eles, juntamente com
   o vetor zz retornado (unitário), representem um novo sistema de
   coordenadas no espaço.
   A função retorna false caso zz seja um vetor nulo.

   Entrada: zz

   Saída:   xx
            yy
            zz
*/
   double ZERO = 1e-7;
   double aux;

   aux = Modulo(zz);
   if(aux <= ZERO) return false;
   zz = zz / aux;
   if(fabs(zz.Y()) <= ZERO)
      yy.DefCoordenadas(0, 1, 0);
   else
   {
      aux = zz.X() / zz.Y();
      yy.X() = 1 / sqrt(1 + aux * aux);
      yy.Y() = - aux * yy.X();
      yy.Z() = 0;
   }
   xx = ProdutoVetorial(yy, zz);
   return true;
}
//---------------------------------------------------------------------------
int  PontoDentroDoCilindro(const BPonto3D& pto, const BPonto3D& base1, const BPonto3D& base2, double raio)
{
/*
      Fornecido o ponto pto e um cilindro definido pelos centros
   das bases, base1 e base2, e o raio, esta função retorna:

   -1    se o ponto pto se encontra no interior do cilindro;
    0    se o ponto pto se encontra na superfície do cilindro;
    1    se o ponto pto se encontra fora do cilindro.
*/

   BVetor3D vet1, vet2;
   double ZERO = 1.0e-7;
   double aux, aux2;
   double distq;
   double m;

   vet1 = base2 - base1;
   aux = vet1 * vet1;
   // Verificar a linha abaixo. Se aux < ZERO, deve retornar um erro
   // de alguma maneira.
   if(aux < ZERO) return 1;
   vet2 = pto - base1;
   aux2 = vet1 * vet2;
   m = aux2 / aux;
   if((m < 0) || (m > 1)) return 1;
   distq = vet2 * vet2 + m * (m * aux - 2 * aux2) - raio * raio;
   if(fabs(distq) < ZERO) return 0;
   if(distq < 0) return -1;
   return 1;
}
//---------------------------------------------------------------------------

