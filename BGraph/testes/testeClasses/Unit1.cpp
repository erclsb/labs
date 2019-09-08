//---------------------------------------------------------------------------
#pragma hdrstop
#pragma argsused
//---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "BGraph.h"
#include "Cidade.h"
using std::string;
using std::cout;
using std::endl;
using namespace BBib;
//---------------------------------------------------------------------------
class Comparador //: public binary_function<Cidade*, Cidade*, bool>
{
    public:
        bool operator() (const Cidade* x1, const Cidade* x2) const
        {
            return x1->LeID() < x2->LeID();
        }
};
//---------------------------------------------------------------------------
typedef BGraph<Cidade*, double, Comparador> Grafo;
typedef Grafo::const_node_iterator const_no_iterator;
typedef Grafo::const_node_iterator::const_edge_iterator const_arco_iterator;
//---------------------------------------------------------------------------
ostream& operator << (ostream& os, const Grafo& grafo)
{
    const_no_iterator no;
    const_arco_iterator arco;

    no = grafo.begin();
    while(no != grafo.end())
    {
        os << **no << endl;
        arco = no.IncidentsFrom_begin();
        while(arco != no.IncidentsFrom_end())
        {
            os << "  " << (*arco) << " - para " << *(arco.incident_to()) << endl;
            arco++;
        }
        arco = no.IncidentsTo_begin();
        while(arco != no.IncidentsTo_end())
        {
            os << "  " << (*arco) << " - de " << *(arco.incident_from()) << endl;
            arco++;
        }
        no++;
    }
    return os;
}
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    Grafo grafo;

    Cidade SP(8, "Sao Paulo");
    Cidade Rio(1, "Rio de Janeiro");
    Cidade BH(3, "Belo Horizonte");
    Cidade Poa(5, "Porto Alegre");

    try
    {
        grafo.insert(&SP);
        grafo.insert(&Rio);
        grafo.insert(&BH);
        grafo.insert(&Poa);
        grafo.insert(&SP, &Rio, 400);
        grafo.insert(&Poa, &Rio, 1600);
        grafo.insert(&BH, &Rio, 600);
        grafo.insert(&SP, &Poa, 1200);
        grafo.insert(&BH, &Poa, 2000);
        grafo.insert(&Poa, &BH, 2002);
        cout << grafo << endl;
        cout << **grafo.find(&Rio) << endl;
        cout << grafo.find_edge(&SP, &Rio) << endl;
        grafo.erase(&SP);
        grafo.erase(&SP);
        grafo.erase(&Rio);
        cout << grafo << endl;
        return 0;
    }
    catch(BExcecao& e)
    {
        cout << e.Mensagem() << endl;
        return -1;
    }
}
//---------------------------------------------------------------------------

