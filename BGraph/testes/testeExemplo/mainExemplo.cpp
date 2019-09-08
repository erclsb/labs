//---------------------------------------------------------------------------

#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused

#include <iostream>
#include <string>
#include "BGraph.h"
#pragma option push -A
using namespace std;
using namespace BBib;

int main(int argc, char* argv[])
{
  typedef BGraph<string, double>        Grafo;
  typedef Grafo::node_iterator          node_iterator;
  typedef node_iterator::edge_iterator  edge_iterator;

  Grafo grafo;
  node_iterator no;
  edge_iterator arco;

  try
  {
    grafo.insert("SP");
    grafo.insert("Rio");
    grafo.insert("BH");
    grafo.insert("Porto Alegre");
    grafo.insert("SP", "Rio", 400.0);
    grafo.insert("Porto Alegre", "Rio", 1600.0);
    grafo.insert("BH", "Rio", 600.0);
    no = grafo.begin();
    while(no != grafo.end())
    {
      cout << *no << endl;
      arco = no.IncidentsFrom_begin();
      while(arco != no.IncidentsFrom_end())
      {
        cout << " " << (*arco) << " - vai para " << arco.incident_to() << endl;
        arco++;
      }
      arco = no.IncidentsTo_begin();
      while(arco != no.IncidentsTo_end())
      {
        cout << " " << (*arco) << " - vem de " << arco.incident_from() << endl;
        arco++;
      }
      no++;
    }
  }
  catch(BExcecao& e)
  {
    cout << e.Mensagem() << endl;
  }
  return 0;
}
//---------------------------------------------------------------------------

 
