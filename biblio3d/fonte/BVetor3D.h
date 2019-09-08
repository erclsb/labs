//---------------------------------------------------------------------------
#ifndef BVetor3DH
#define BVetor3DH
//---------------------------------------------------------------------------
#include "BObjeto3D.h"
#include "BPonto3D.h"
//---------------------------------------------------------------------------
namespace BBib
{

namespace Biblio3D
{

class BVetor3D : public BObjeto3D
{
    private:
        double x;
        double y;
        double z;
        static const char* MENSAGEM_ERRO[];
    
    protected:
    
    public:
        BVetor3D(void);
        BVetor3D(double xx, double yy, double zz);
        BVetor3D(const BVetor3D& v);
        virtual ~BVetor3D(void);
        //operadores membro
        BVetor3D& operator = (const BVetor3D& v);
        bool operator == (const BVetor3D& v) const;
        bool operator != (const BVetor3D& v) const;
        BVetor3D& operator += (const BVetor3D& v);
        BVetor3D& operator += (double d);
        BVetor3D& operator -= (const BVetor3D& v);
        BVetor3D& operator -= (double d);
        BVetor3D& operator *= (double d);
        BVetor3D& operator /= (double d);
        //operadores nao-membro
        friend BVetor3D operator + (const BVetor3D& v1, const BVetor3D& v2);
        friend BVetor3D operator + (double d, const BVetor3D& v);
        friend BVetor3D operator + (const BVetor3D& v, double d);
        friend BPonto3D operator + (const BPonto3D& p, const BVetor3D& v);
        friend BVetor3D operator - (const BVetor3D& v);
        friend BVetor3D operator - (const BPonto3D& p1, const BPonto3D& p2);
        friend BVetor3D operator - (const BVetor3D& v1, const BVetor3D& v2);
        friend BVetor3D operator - (const BVetor3D& v, double d);
        friend double   operator * (const BVetor3D& v1, const BVetor3D& v2);
        friend BVetor3D operator * (double d, const BVetor3D& p);
        friend BVetor3D operator * (const BVetor3D& v, double d);
        friend BVetor3D operator / (const BVetor3D& v, double d);
        //funcoes membro
        void DefCoordenadas(double xx, double yy, double zz);
        void DefCoordenadasCilindricas(double mod, double ang, double zz);
        void DefCoordenadasEsfericas(double mod, double Phi, double Theta);
        inline double& X(void);
        inline const double& X(void) const;
        inline double& Y(void);
        inline const double& Y(void) const;
        inline double& Z(void);
        inline const double& Z(void) const;
        //funcoes nao-membro
        friend double abs(const BVetor3D& v);
        friend double norm(const BVetor3D& v);
        friend double phi(const BVetor3D& v);
        friend double theta(const BVetor3D& v);
        friend double Angulo(const BVetor3D& v1, const BVetor3D& v2);
        friend bool Ortogonais(const BVetor3D& v1, const BVetor3D& v2);
        friend bool Paralelos(const BVetor3D& v1, const BVetor3D& v2);
        friend BVetor3D ProdutoVetorial(const BVetor3D& v1, const BVetor3D& v2);
        friend BVetor3D unit(const BVetor3D& v);
};
//---------------------------------------------------------------------------
double& BVetor3D::X(void)
{
    return x;
}
//---------------------------------------------------------------------------
const double& BVetor3D::X(void) const
{
    return x;
}
//---------------------------------------------------------------------------
double& BVetor3D::Y(void)
{
    return y;
}
//---------------------------------------------------------------------------
const double& BVetor3D::Y(void) const
{
    return y;
}
//---------------------------------------------------------------------------
double& BVetor3D::Z(void)
{
    return z;
}
//---------------------------------------------------------------------------
const double& BVetor3D::Z(void) const
{
    return z;
}
//---------------------------------------------------------------------------

}; //namespace Biblio3D

}; //namespace BBib

#endif
