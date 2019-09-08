//---------------------------------------------------------------------------
#ifndef Funcoes3DH
#define Funcoes3DH
//---------------------------------------------------------------------------
#include "BPonto3D.h"
#include "BVetor3D.h"
//---------------------------------------------------------------------------
bool GeraNovoSistema(BVetor3D& zz, BVetor3D& xx, BVetor3D& yy);
int PontoDentroDoCilindro(const BPonto3D& pto, const BPonto3D& base1, const BPonto3D& base2, double raio);
//---------------------------------------------------------------------------
#endif
