//---------------------------------------------------------------------------
#ifndef BCilindroH
#define BCilindroH
//---------------------------------------------------------------------------
#include "BObjeto3D.h"
#include "BSegmentoReta3D.h"
//---------------------------------------------------------------------------
namespace BBib
{

namespace Biblio3D
{

class BCilindro : public BObjeto3D
{
    private:
        BSegmentoReta3D aEixo;
        double          adRaio;
        static const char* MENSAGEM_ERRO[];

    protected:

    public:
        BCilindro(void);
        BCilindro(const BCilindro& x);
        BCilindro(const BSegmentoReta3D& Eixo, double Raio);
        BCilindro(const BPonto3D& CentroBase1, const BPonto3D& CentroBase2, double Raio);
        virtual ~BCilindro(void);
        // Operadores
        BCilindro& operator = (const BCilindro& x);
        // Funcoes membro
        bool ContemPonto(const BPonto3D& Ponto) const;
        bool ContemPonto(double x, double y, double z) const;
        void DefCentrosBases(const BPonto3D& Centro1, const BPonto3D& Centro2);
        void DefCentrosBases(double x1, double y1, double z1, double x2, double y2, double z2);
        void DefRaio(double Raio);
        double LeAltura(void) const;
        double LeAreaBase(void) const;
        double LeAreaLateral(void) const;
        double LeAreaTotal(void) const;
        const BPonto3D& LeCentroBase1(void) const;
        const BPonto3D& LeCentroBase2(void) const;
        double LeRaio(void) const;
        double LeVolume(void) const;
        int SituaPonto(const BPonto3D& Ponto) const;
        int SituaPonto(double x, double y, double z) const;
}; //class BCilindro

}; //namespace Biblio3D

}; //namespace BBib
//---------------------------------------------------------------------------
#endif
