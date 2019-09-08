//---------------------------------------------------------------------------
#ifndef BPonto3DH
#define BPonto3DH
//---------------------------------------------------------------------------
#include "BObjeto3D.h"
//---------------------------------------------------------------------------
namespace BBib
{

namespace Biblio3D
{

class BPonto3D : public BObjeto3D
{
    private:
        double x;
        double y;
        double z;

    protected:

    public:
        //Construtores e destrutor
        BPonto3D(void);
        BPonto3D(double xx, double yy, double zz);
        BPonto3D(const BPonto3D& p);
        virtual ~BPonto3D(void);
        //Operadores
        BPonto3D& operator = (const BPonto3D& p);
        bool operator == (const BPonto3D& p) const;
        bool operator != (const BPonto3D& p) const;
        //Funcoes membro
        void DefCoordenadas(double xx, double yy, double zz);
        void DefCoordenadasCilindricas(double mod, double ang, double zz);
        void DefCoordenadasEsfericas(double mod, double theta, double phi);
        inline double& X(void);
        inline const double& X(void) const;
        inline double& Y(void);
        inline const double& Y(void) const;
        inline double& Z(void);
        inline const double& Z(void) const;
        //Funcoes nao-membro
        friend double phi(const BPonto3D& p);
        friend double theta(const BPonto3D& p);
        friend double Distancia(const BPonto3D& p1, const BPonto3D& p2);
        friend BPonto3D PontoMedio(const BPonto3D& p1, const BPonto3D& p2);
        friend bool Colineares(const BPonto3D& p1, const BPonto3D& p2, const BPonto3D& p3);
        friend bool Coplanares(const BPonto3D& p1, const BPonto3D& p2, const BPonto3D& p3, const BPonto3D& p4);
};
//---------------------------------------------------------------------------
double& BPonto3D::X(void)
{
    return x;
}
//---------------------------------------------------------------------------
const double& BPonto3D::X(void) const
{
    return x;
}
//---------------------------------------------------------------------------
double& BPonto3D::Y(void)
{
    return y;
}
//---------------------------------------------------------------------------
const double& BPonto3D::Y(void) const
{
    return y;
}
//---------------------------------------------------------------------------
double& BPonto3D::Z(void)
{
    return z;
}
//---------------------------------------------------------------------------
const double& BPonto3D::Z(void) const
{
    return z;
}
//---------------------------------------------------------------------------

}; //namespace Biblio3D

}; //namespace BBib

#endif
