//---------------------------------------------------------------------------
#ifndef BSegmentoReta3DH
#define BSegmentoReta3DH
//---------------------------------------------------------------------------
#include "BObjeto3D.h"
#include "BPonto3D.h"
#include "BVetor3D.h"
//---------------------------------------------------------------------------
namespace BBib
{

namespace Biblio3D
{

class BSegmentoReta3D : public BObjeto3D
{
    private:
        BPonto3D aPonto1;
        BPonto3D aPonto2;
        static const char* MENSAGEM_ERRO[];

    protected:

    public:
        BSegmentoReta3D(void);
        BSegmentoReta3D(const BSegmentoReta3D& Segmento);
        BSegmentoReta3D(const BPonto3D& p1, const BPonto3D& p2);
        BSegmentoReta3D(double x1, double y1, double z1,
            double x2, double y2, double z2);
        virtual ~BSegmentoReta3D(void);
        //Operadores
        BSegmentoReta3D& operator = (const BSegmentoReta3D& Segmento);
        operator BVetor3D() const;
        //Funcoes membro
        void DefPontos(const BPonto3D& p1, const BPonto3D& p2);
        void DefPontos(double x1, double y1, double z1,
            double x2, double y2, double z2);
        double LeComprimento(void) const;
        const BPonto3D& LePonto1(void) const;
        const BPonto3D& LePonto2(void) const;
        bool ContemPonto(const BPonto3D& Ponto) const;
        bool ContemPonto(double x, double y, double z) const;
        //Funcoes nao membro
        friend double Distancia(const BSegmentoReta3D& Segmento, const BPonto3D& Ponto);
        friend double Distancia(const BPonto3D& Ponto, const BSegmentoReta3D& Segmento);
};
//---------------------------------------------------------------------------

}; //namespace Biblio3D

}; //namespace BBib

#endif
