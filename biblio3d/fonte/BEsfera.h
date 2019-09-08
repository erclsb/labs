//---------------------------------------------------------------------------
#ifndef BEsferaH
#define BEsferaH
//---------------------------------------------------------------------------
#include "BObjeto3D.h"
#include "BSegmentoReta3D.h"
//---------------------------------------------------------------------------
namespace BBib
{

namespace Biblio3D
{

class BEsfera : public BObjeto3D
{
    private:
        BPonto3D aCentro;
        double   adRaio;
        static const char* MENSAGEM_ERRO[];
        
    protected:

    public:
        BEsfera(void);
        BEsfera(const BEsfera& x);
        BEsfera(const BPonto3D& Centro, double Raio);
        virtual ~BEsfera(void);
        // Operadores
        BEsfera& operator = (const BEsfera& x);
        // Funcoes membro
        bool ContemPonto(const BPonto3D& Ponto) const;
        void DefCentro(const BPonto3D& Centro);
        void DefRaio(double Raio);
        double LeArea(void) const;
        const BPonto3D& LeCentro(void) const;
        double LeRaio(void) const;
        double LeVolume(void) const;
        int SituaPonto(const BPonto3D& Ponto) const;
};


}; //namespace Biblio3D

}; //namespace BBib

//---------------------------------------------------------------------------
#endif
