//---------------------------------------------------------------------------
#include <iostream>
#include <time.h>
#pragma hdrstop
#include "Prim.h"
#include "Dijkstra.h"
#include "ConnectedComponents.h"
//---------------------------------------------------------------------------
using namespace BBib;
typedef BGraph<int, int> Grafo;
//---------------------------------------------------------------------------
void testeConnectedComponents(const Grafo& grafo)
{
    using namespace std;
    typedef ComponentMap<int> Mapa;

    Mapa mapa;
    Mapa::iterator it;
    Mapa::iterator end;
    int nComponentes;

    cout << "Inicio Connected components" << endl;
    FindConnectedComponents(grafo, mapa, nComponentes);
    cout << "Fim Connected components" << endl;
    cout << nComponentes << " componentes" << endl;
    it = mapa.begin();
    end = mapa.end();
    while(it != end)
    {
        cout << *(it->node) << ' ' << it->component << endl;
        ++it;
    }
    cout << endl;
}
//---------------------------------------------------------------------------
void testeDijkstra(const Grafo& grafo)
{
    using namespace std;
    typedef MinPath<int> Caminho;

    Caminho caminho;
    Caminho::iterator it;
    Caminho::iterator end;

    cout << "Inicio Shortest Path" << endl;
    ShortestPath(grafo, 0, caminho);
    cout << "Fim Shortest Path" << endl;
    it = caminho.begin();
    end = caminho.end();

    while(it != end)
    {
        if(it->precedent)
        {
            cout << *(it->node) << ' ' << *(it->precedent->node) << ' ' <<
                it->distance << endl;
        }
        else
        {
            cout << *(it->node) << " - " << it->distance << endl;
        }
        ++it;
    }
    cout << endl;
}
//---------------------------------------------------------------------------
void testeMST(const Grafo& grafo)
{
    using namespace std;
    typedef SpanningTree<int> Arvore;

    Arvore arvore;
    Arvore::iterator it;
    Arvore::iterator end;

    cout << "Inicio Minimal Spanning Tree" << endl;
    MinimalSpanningTree(grafo, 0, arvore);
    cout << "Fim Minimal Spanning Tree" << endl;
    it = arvore.begin();
    end = arvore.end();

    while(it != end)
    {
        if(it->precedent)
        {
            cout << *(it->node) << ' ' << *(it->precedent->node) << ' ' <<
                it->distance << endl;
        }
        else
        {
            cout << *(it->node) << " - " << it->distance << endl;
        }
        ++it;
    }
    cout << endl;
}
//---------------------------------------------------------------------------
void ImprimeInstante(void)
{
    using namespace std;

    time_t agora;
    agora = time(NULL);
    //cout << ctime(&agora);
}
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    Grafo grafo;
    const int N = 100;

    ImprimeInstante();
    for(int i = 0; i < N; i++)
    {
        grafo.insert(i);
    }
    for(int i = 0; i < N; i++)
    {
        for(int j = i + 1; j < N; j++)
        {
            grafo.insert(i, j, i + j);
            grafo.insert(j, i, i + j);
        }
    }

    ImprimeInstante();
    testeDijkstra(grafo);
    ImprimeInstante();
    testeMST(grafo);
    ImprimeInstante();
    testeConnectedComponents(grafo);
    ImprimeInstante();
    return 0;
}
//---------------------------------------------------------------------------
