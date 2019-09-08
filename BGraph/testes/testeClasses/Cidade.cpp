//---------------------------------------------------------------------------
#pragma hdrstop

#include "Cidade.h"
//---------------------------------------------------------------------------
Cidade::Cidade(void)
{
    id = 0;
    nome[0] = '\0';
}
//---------------------------------------------------------------------------
Cidade::Cidade(const Cidade& c)
{
    id = c.id;
    strcpy(nome, c.nome);
}
//---------------------------------------------------------------------------
Cidade::Cidade(int ID, const char* Nome)
{
    id = ID;
    strcpy(nome, Nome);
}
//---------------------------------------------------------------------------
Cidade& Cidade::operator = (const Cidade& c)
{
    if(this != &c)
    {
        id = c.id;
        strcpy(nome, c.nome);
    }
    return *this;
}
//---------------------------------------------------------------------------
bool Cidade::operator < (const Cidade& c) const
{
    return id < c.id;
}
//---------------------------------------------------------------------------
bool Cidade::operator == (const Cidade& c) const
{
    return id == c.id;
}
//---------------------------------------------------------------------------
ostream& operator << (ostream& os, const Cidade& c)
{
    os << c.nome;
    return os;
}
//---------------------------------------------------------------------------
int Cidade::LeID(void) const
{
    return id;
}
//---------------------------------------------------------------------------

