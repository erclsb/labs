#include<fstream>
#include"BExcecao.h"
#include"fonte/modelo/Dijkstra.h"
#include"Cidade.h"
#include"Estrada.h"

#pragma option push -A

using namespace BBib;
typedef graph<Cidade,Estrada> Grafo;
typedef Triple<Cidade,float> Trio;
typedef MinPath<Cidade,float> Caminho;

void LeTopologia(Grafo& grafo);


int main(int argc, char* argv[])
{
    using std::cout;
    using std::cin;
    using std::endl;
    try
    {
        int chave;
        Grafo mapa;

        LeTopologia(mapa);
        do
        {
            cout << "\n\nEscolha uma opcao:\n1. Alterar estrada\n2."
                " Encontrar melhor caminho\n0. Sair\n\n";
            cin >> chave;
            switch(chave)
            {
                case 0:
                break;
                case 1:
                {
                    Grafo::node_iterator it;
                    Grafo::node_iterator end = mapa.end();
                    int o;
                    int d;
                    char maodupla;
                    float ped;
                    float dist;
                    int pav;
                    int alt;


                    for(it = mapa.begin(); it!=end; ++it)
                        cout << it->LeID() << ' ' << it->LeNome() << endl;
                    cout << endl << "Escolha as cidades de origem e destino.\n";
                    cin >> o >> d;
                    cout << "Alterar as duas vias? (S/N)\n";
                    cin >> maodupla;
                    if (maodupla > 90) maodupla -= 32;
                    Estrada& est = mapa.find_edge(o,d);
                    cout << "\nEscolha alterar:\n1. Distancia\n2. Pavimentacao\n3. Pedagio\n";
                    cin >>  alt;
                    switch(alt)
                    {
                        case 1:
                        {
                            cout << "\nEntre com o novo valor de distancia:\n";
                            cin >> dist;
                            est.DefDistancia(dist);
                            if(maodupla=='S')
                            {
                                Estrada& est = mapa.find_edge(d,o);
                                est.DefDistancia(dist);
                            }
                        }
                        break;
                        case 2:
                        {
                            cout << "\nEntre com o novo tipo de pavimentacao:\n";
                            cin >> pav;
                            est.DefPavimentacao(Estrada::Pavimentacao(pav));
                            if(maodupla=='S')
                            {
                                Estrada& est = mapa.find_edge(d,o);
                                est.DefPavimentacao(Estrada::Pavimentacao(pav));
                            }
                        }
                        break;
                        case 3:
                        {
                            cout << "\nEntre com o novo valor de pedagio:\n";
                            cin >> ped;
                            est.DefPedagio(ped);
                            if(maodupla=='S')
                            {
                                Estrada& est = mapa.find_edge(d,o);
                                est.DefPedagio(ped);
                            }
                        }
                        break;
                    }
                }
                break;
                case 2:
                {
                    Grafo::node_iterator it;
                    Grafo::node_iterator end = mapa.end();
                    Caminho roteiro;
                    Trio* pTrio;
                    int o;
                    int d;

                    for(it = mapa.begin(); it!=end; ++it)
                        cout << it->LeID() << ' ' << it->LeNome() << endl;
                    cout << endl << "Escolha as cidades de origem e destino.\n";
                    cin >> o >> d;
                    ShortestPath(mapa,Cidade(o),roteiro);
                    pTrio = &(*roteiro.find(Trio(d)));
                    cout << "Custo total: " << pTrio->distance << " Reais."
                        << endl;
                    while(pTrio != NULL)
                    {
                        cout << pTrio->node->LeNome() << endl;
                        pTrio = pTrio->precedent;
                    }
                }
                break;
                default:
                    cout << "Opcao nao valida.\n";
            }
        }
        while(chave != 0);
    }
    catch(const BExcecao& e)
    {
        cout << e.Mensagem();
    }
}


void LeTopologia(Grafo& grafo)
{
    std::fstream arq;
    int n;
    int de;
    int para;
    int id;
    char nome[200];
    char* pc;
    float d;
    int pav;
    float ped;
    Estrada estrada;

    arq.open("BR.txt",std::ios::in);
    arq >> n;
    for(int i=0; i<n; i++)
    {
        arq >> id;
        arq.getline(nome,200);
        pc = nome;
        while(*pc == ' ' || *pc == '\t') ++pc;
        Cidade cidade(id,pc);
        grafo.insert(cidade);
    }
    arq >> n;
    for(int i=0; i<n; i++)
    {
        arq >> de >> para >> d >> pav >> ped;
        estrada.DefDistancia(d);
        estrada.DefPavimentacao(Estrada::Pavimentacao(pav));
        estrada.DefPedagio(ped);
        grafo.insert(de,para,estrada);
    }
    arq.close();
}

#pragma option pop
