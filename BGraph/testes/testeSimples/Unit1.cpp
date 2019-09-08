//---------------------------------------------------------------------------
#pragma hdrstop
#pragma argsused
//---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "BGraph.h"
using std::string;
using namespace BBib;
//---------------------------------------------------------------------------
#pragma option push -A
typedef BGraph<string, double> Grafo;
typedef Grafo::node_iterator no_iterator;
typedef no_iterator::edge_iterator arco_iterator;
typedef Grafo::const_node_iterator const_no_iterator;
typedef const_no_iterator::const_edge_iterator const_arco_iterator;
//---------------------------------------------------------------------------
void ImprimeConstGrafo(const Grafo& grafo)
{
    using std::cout;
    using std::endl;
    
    const_no_iterator no;
    const_arco_iterator arco;

    no = grafo.begin();
    while(no != grafo.end())
    {
        cout << *no << endl;
        arco = no.IncidentsFrom_begin();
        while(arco != no.IncidentsFrom_end())
        {
            cout << "  " << (*arco) << " - vai para " << arco.incident_to() << endl;
            arco++;
        }
        arco = no.IncidentsTo_begin();
        while(arco != no.IncidentsTo_end())
        {
            cout << "  " << (*arco) << " - vem de " << arco.incident_from() << endl;
            arco++;
        }
        no++;
    }
    cout << grafo.size() << " nos" << endl;
    cout << endl;
}
//---------------------------------------------------------------------------
void ImprimeGrafo(Grafo& grafo)
{
    using std::cout;
    using std::endl;

    no_iterator no;
    arco_iterator arco;

    no = grafo.begin();
    while(no != grafo.end())
    {
        cout << *no << endl;
        arco = no.IncidentsFrom_begin();
        while(arco != no.IncidentsFrom_end())
        {
            cout << "  " << (*arco) << " - vai para " << arco.incident_to() << endl;
            arco++;
        }
        arco = no.IncidentsTo_begin();
        while(arco != no.IncidentsTo_end())
        {
            cout << "  " << (*arco) << " - vem de " << arco.incident_from() << endl;
            arco++;
        }
        no++;
    }
    cout << grafo.size() << " nos" << endl;
    cout << endl;
}
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    using std::cout;
    using std::endl;
    Grafo grafo;

    try
    {
        grafo.insert("SP");
        grafo.insert("Rio");
        grafo.insert("SP", "Rio", 400);
        ImprimeConstGrafo(grafo);
        grafo.insert("BH");
        grafo.insert("Porto Alegre");
        grafo.insert("Porto Alegre", "Rio", 1600);
        grafo.insert("BH", "Rio", 600);
        ImprimeGrafo(grafo);
        return 0;
    }
    catch(BExcecao& e)
    {
        cout << e.Mensagem() << endl;
        return -1;
    }
}
//---------------------------------------------------------------------------
#pragma option pop

