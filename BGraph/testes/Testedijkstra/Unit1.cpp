#include<fstream>
#include "BExcecao.h"
#include "Dijkstra.h"

#pragma argsused
int main(int argc, char* argv[])
{
    using std::cout;
    using std::cin;
    using std::endl;
    try
    {
        using namespace BBib;
        typedef BGraph<char,double> Grafo;
        typedef Triple<char,double> Trio;
        typedef MinPath<char,double> Caminho;
        const int MAXNOS = 8;
        const int MAXARCOS = 13;

        Grafo grafo;
        char* no = new char[MAXNOS];
        double* arco = new double[MAXARCOS];
        Caminho caminho;
                 
        for(int i=0; i<MAXNOS; i++)
        {
            no[i] = i + 65;
            grafo.insert(no[i]);
        }
        grafo.insert(no[7],no[5],1);
        grafo.insert(no[6],no[3],3);
        grafo.insert(no[6],no[5],1);
        grafo.insert(no[6],no[7],3);
        grafo.insert(no[4],no[6],0.8);
        grafo.insert(no[4],no[7],3);
        grafo.insert(no[3],no[5],2);
        grafo.insert(no[2],no[4],2);
        grafo.insert(no[1],no[2],5);
        grafo.insert(no[1],no[3],3);
        grafo.insert(no[1],no[6],4);
        grafo.insert(no[0],no[1],2);
        grafo.insert(no[0],no[2],3);

        ShortestPath(grafo,no[0],caminho);
        Caminho::iterator it = caminho.begin();
        Caminho::iterator end = caminho.end();
        while(it != end)
        {
            cout << *it->node << ' ' << it->distance << endl;
            ++it;
        }

        Trio origem;
        Trio* t;

        for(char c = 'A'; c <= 'H'; c++)
        {
            cout << endl;
            origem.node = &c;
            t = &(*caminho.find(origem));
            while(t != NULL)
            {
                cout << t->node << ' ';
                t = t->precedent;
            }
        }

        delete[] no;
        delete[] arco;
        return 0;
    }
    catch(const BExcecao& e)
    {
        cout << e.Mensagem();
        return -1;
    }
}
//---------------------------------------------------------------------------
 
