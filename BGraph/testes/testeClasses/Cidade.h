//---------------------------------------------------------------------------
#ifndef CidadeH
#define CidadeH
//---------------------------------------------------------------------------
#include <iostream>
using std::ostream;
//---------------------------------------------------------------------------
class Cidade
{
    private:
        int id;
        char nome[100];

    protected:

    public:
        Cidade(void);
        Cidade(const Cidade& c);
        Cidade(int ID, const char* Nome);
        Cidade& operator = (const Cidade& c);
        bool operator < (const Cidade& c) const;
        bool operator == (const Cidade& c) const;
        friend ostream& operator << (ostream& os, const Cidade& c);
        int LeID(void) const;
};
//---------------------------------------------------------------------------
#endif
 