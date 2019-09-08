//---------------------------------------------------------------------------
#ifndef BGraphH
#define BGraphH
//---------------------------------------------------------------------------
#include <set>
#include "BExcecao.h"
//#pragma option push -A
//---------------------------------------------------------------------------
namespace BBib
{

using std::set;
using std::less;
using std::binary_function;
using std::pair;

//---------------------------------------------------------------------------
/**
Classe que representa um grafo direto. Possui métodos para inserir e
remover nós e arcos, além de localizar um determinado nó ou um arco a
partir de dois nós. Possui quatro iterators, (node_iterator,
const_node_iterator, edge_iterator, const_edge_iterator) para trabalhar
com os nós e arcos.
*/
template <class Node, class Edge, class Compare = less<Node> >
class BGraph
{
    private:
        class BNode
        {
    	    private:
            	Compare comp;

		        class PairpNodeEdge
                {
                    private:
                        Node* _node;
                        Edge  _edge;

                    public:
                        PairpNodeEdge() {}
                        PairpNodeEdge(const PairpNodeEdge& x) {_node = x._node; _edge = x._edge;}
                        PairpNodeEdge(Node* n, const Edge& a) {_node = n; _edge = a;}
                        bool operator == (const PairpNodeEdge& x) const
                        {
                            return *_node == *(x._node);
                        }
                        bool operator < (const PairpNodeEdge& x) const
                        {
                            return comp(*_node, *(x._node));
                        }
                        inline Node* node(void)
                        {
                            return _node;
                        }
                        inline const Node* node(void) const
                        {
                            return _node;
                        }
                        inline Edge* edge(void)
                        {
                            return &_edge;
                        }
                        inline const Edge* edge(void) const
                        {
                            return &_edge;
                        }
                };

                class PairpNodepEdge
                {
                    private:
                        Node* _node;
                        Edge* _edge;

                    public:
                        PairpNodepEdge() {}
                        PairpNodepEdge(const PairpNodepEdge& x) {_node = x._node; _edge = x._edge;}
                        PairpNodepEdge(Node* n, Edge* a) {_node = n; _edge = a;}
                        bool operator == (const PairpNodepEdge& x) const
                        {
                            return *_node == *(x._node);
                        }
                        bool operator < (const PairpNodepEdge& x) const
                        {
                            return *_node < *(x._node);
                        }
                        inline Node* node(void)
                        {
                            return _node;
                        }
                        inline const Node* node(void) const
                        {
                            return _node;
                        }
                        inline Edge* edge(void)
                        {
                            return _edge;
                        }
                        inline const Edge* edge(void) const
                        {
                            return _edge;
                        }
                };

                struct ComparePairpNodeEdge : public binary_function<PairpNodeEdge, PairpNodeEdge, bool>
                {
                    bool operator() (const PairpNodeEdge& x1, const PairpNodeEdge& x2) const
                    {
                        Compare comp;
                        return comp(*(x1.node()), *(x2.node()));
                    }
                };

                struct ComparePairpNodepEdge : public binary_function<PairpNodepEdge, PairpNodepEdge, bool>
                {
                    bool operator() (const PairpNodepEdge& x1, const PairpNodepEdge& x2) const
                    {
                        Compare comp;
                        return comp(*(x1.node()), *(x2.node()));
                    }
                };

                typedef set<PairpNodeEdge, ComparePairpNodeEdge>   setPairpNodeEdge;
                typedef set<PairpNodepEdge, ComparePairpNodepEdge> setPairpNodepEdge;

            public:
                friend class BGraph;
                friend class node_iterator;
                friend class const_node_iterator;

                BNode(const Node& x) {_node = x;}

                bool operator == (const BNode& x) const
                {
                    return _node == x._node;
                }

                bool operator < (const BNode& x) const
                {
                    return comp(_node, x._node);
                }

                Node& node(void) {return _node; }
                const Node& node(void) const {return _node; }
                setPairpNodeEdge& EdgesFrom(void) {return _EdgesFrom; };
                const setPairpNodeEdge& EdgesFrom(void) const {return _EdgesFrom; };
                setPairpNodepEdge& EdgesTo(void) {return _EdgesTo; };
                const setPairpNodepEdge& EdgesTo(void) const {return _EdgesTo; };

            private:

                Node _node;

                setPairpNodeEdge  _EdgesFrom;
                setPairpNodepEdge _EdgesTo;
        };

        struct CompareNodes : public binary_function<BNode, BNode, bool>
        {
            bool operator() (const BNode& x1, const BNode& x2) const
            {
                Compare comp;
                return comp(x1.node(), x2.node());
            }
        };

        typedef set<BNode, CompareNodes> setNodes;

        static const char*   MENSAGEM[];
        bool                 abSubstituiArcosIguais;
        setNodes             asetNodes;

    protected:

    public:
        /**
        Iterator para representar um nó do grafo. Pode-se obter
        todos os arcos incidentes, tanto deste nó quanto para ele.
        */
        class node_iterator
        {
            private:
                setNodes::iterator it;

            protected:
				node_iterator(setNodes::iterator x) {it = x;};
        		void clear_edges_from(void) const
				{
        		    it->EdgesFrom.clear();
				}

        		void clear_edges_to(void) const
				{
        		    it->EdgesTo.clear();
        		}

				void erase_edge_from(const Node& node) const
				{
				    Node n(node);
				    it->EdgesFrom().erase(BNode::PairpNodeEdge(&n, Edge()));
				}

				void erase_edge_to(const Node& node) const
				{
				    Node n(node);
				    it->EdgesTo().erase(BNode::PairpNodepEdge(&n, 0));
				}

            public:
				friend class BGraph;

                /**
                Iterator para representar um arco do grafo.
                */
				class edge_iterator
				{
                    private:
  	  			        BNode::setPairpNodeEdge::iterator itFrom;
    			        BNode::setPairpNodepEdge::iterator itTo;
    			        bool abEdgeFrom;

			        protected:
			            edge_iterator(BNode::setPairpNodeEdge::iterator x) {abEdgeFrom = 1; itFrom = x;};
    			        edge_iterator(BNode::setPairpNodepEdge::iterator x) {abEdgeFrom = 0; itTo = x;};

	    		    public:
			            friend class BGraph;
    			        friend class node_iterator;

	    		        edge_iterator()
                        {
                            /**
                            Cria um objeto vazio.
                            */
                        }
		    	        edge_iterator(const edge_iterator& x)
                        {
                            /**
                            Construtor de cópia. Cria uma cópia de x.
                            */
                            abEdgeFrom = x.abEdgeFrom;
                            itFrom = x.itFrom;
                            itTo = x.itTo;
                        }
			            bool operator== (const edge_iterator& x) const
			            {
                            /**
                            Retorna true se o objeto for igual a x.
                            */
			                return (abEdgeFrom) ? itFrom == x.itFrom : itTo == x.itTo;
    			        }
	    		        bool operator!= (const edge_iterator& x) const
                        {
                            /**
                            Retorna true se o objeto for diferente de x.
                            */
                            return !(*this == x);
                        }
		    	        Edge& operator* () const
                        {
                            /**
                            Retorna o arco apontado pelo iterator.
                            */
                            return (abEdgeFrom) ? *itFrom->edge() : *itTo->edge();
                        }
			            Edge* operator-> () const
                        {
                            /**
                            Retorna um ponteiro para o arco apontado
                            pelo iterator.
                            */
                            return (abEdgeFrom) ? itFrom->edge() : itTo->edge();
                        }
			            edge_iterator& operator++ ()
			            {
                            /**
                            Aponta para o próximo nó.
                            */
			                if(abEdgeFrom) ++itFrom;
    			            else ++itTo;
	    		            return *this;
		    	        }
			            edge_iterator operator++ (int)
			            {
                            /**
                            Aponta para o próximo nó.
                            */
			                edge_iterator tmp = *this;
                            ++*this;
                            return tmp;
	    		        }
    			        edge_iterator& operator-- ()
		    	        {
                            /**
                            Aponta para o nó anterior.
                            */
			                if(abEdgeFrom) --itFrom;
			                else --itTo;
			                return *this;
    			        }
	    		        edge_iterator operator-- (int)
		    	        {
                            /**
                            Aponta para o nó anterior.
                            */
			                edge_iterator tmp = *this;
                            --*this;
                            return tmp;
			            }
			            Node& incident_from() const
    			        {
                            /**
                            Retorna o nó de onde o arco incide.
                            */
	    		            if(abEdgeFrom)
		    	            {
			                    throw BExcecaoEstruturaDados("Referência circular");
			                }
			                else
			                {
			                    return *(itTo->node());
    			            }
	    		        }
		    	        Node& incident_to() const
			            {
                            /**
                            Retorna o nó para onde o arco incide.
                            */
			                if(abEdgeFrom)
			                {
			                    return *(itFrom->node());
    			            }
	    		            else
		    	            {
			                    throw BExcecaoEstruturaDados("Referência circular");
			                }
			            }
                };

				node_iterator()
                {
                    /**
                    Cria um objeto vazio.
                    */
                }
				node_iterator(const node_iterator& x)
                {
                    /**
                    Construtor de cópia. Cria uma cópia de x.
                    */
                    it = x.it;
                }
				bool operator== (const node_iterator& x) const
                {
                    /**
                    Retorna true se o iterator for o mesmo que x.
                    */
                    return it == x.it;
                }
				bool operator!= (const node_iterator& x) const
                {
                    /**
                    Retorna true se o iterator for diferente de x.
                    */
                    return !(*this == x);
                }
				Node& operator* () const
                {
                    /**
                    Retorna o nó apontado pelo iterator.
                    */
                    return it->node();
                }
				Node* operator-> () const
                {
                    /**
                    Retorna o endereço do nó apontado pelo iterator.
                    */
                    return &(it->node());
                }
				node_iterator& operator++ ()
                {
                    /**
                    Aponta para o próximo nó.
                    */
                    ++it;
                    return *this;
                }
				node_iterator operator++ (int)
				{
                    /**
                    Aponta para o próximo nó.
                    */
				    node_iterator tmp = *this;
                    ++*this;
                    return tmp;
				}
				node_iterator& operator-- ()
                {
                    /**
                    Aponta para o nó anterior.
                    */
                    --it;
                    return *this;
                }
				node_iterator operator-- (int)
				{
                    /**
                    Aponta para o nó anterior.
                    */
				    node_iterator tmp = *this;
                    --*this;
                    return tmp;
				}

				edge_iterator IncidentsFrom_begin(void) const
				{
                    /**
                    Retorna um iterator para o primeiro
                    dos arcos incidentes do nó.
                    */
				    return edge_iterator(it->EdgesFrom().begin());
				}

				edge_iterator IncidentsFrom_end(void) const
				{
                    /**
                    Retorna um iterator para depois do último
                    dos arcos incidentes do nó.
                    */
				    return edge_iterator(it->EdgesFrom().end());
				}

				edge_iterator IncidentsTo_begin(void) const
				{
                    /**
                    Retorna um iterator para o primeiro dos
                    arcos que incidem no nó.
                    */
				    return edge_iterator(it->EdgesTo().begin());
				}

				edge_iterator IncidentsTo_end(void) const
				{
                    /**
                    Retorna um iterator para depois do último
                    dos arcos que incidem no nó.
                    */
				    return edge_iterator(it->EdgesTo().end());
				}
        };

        /**
        Iterator para representar um nó constante do grafo.
        Pode-se obter todos os arcos incidentes, tanto deste
        nó quanto para ele.
        */
        class const_node_iterator
        {
			private:
			    setNodes::const_iterator it;

			protected:
        		const_node_iterator(setNodes::iterator x) {it = x;};
			    const_node_iterator(setNodes::const_iterator x) {it = x;};

			public:
			    friend class BGraph;

                /**
                Iterator constante para representar um arco do grafo.
                */
			    class const_edge_iterator
			    {
                    private:
                        BNode::setPairpNodeEdge::const_iterator itFrom;
    		  	        BNode::setPairpNodepEdge::const_iterator itTo;
		  	            bool abEdgeFrom;

		  	        protected:
		  	            const_edge_iterator(BNode::setPairpNodeEdge::iterator x) {abEdgeFrom = 1; itFrom = x;};
    		  	        const_edge_iterator(BNode::setPairpNodepEdge::iterator x) {abEdgeFrom = 0; itTo = x;};
	    	  	        const_edge_iterator(BNode::setPairpNodeEdge::const_iterator x) {abEdgeFrom = 1; itFrom = x;};
		  	            const_edge_iterator(BNode::setPairpNodepEdge::const_iterator x) {abEdgeFrom = 0; itTo = x;};

		  	        public:
    		  	        friend class BGraph;
	    	  	        friend class const_node_iterator;

		      	        const_edge_iterator()
                        {
                            /**
                            Cria um objeto vazio.
                            */
                        }
		  	            const_edge_iterator(const const_edge_iterator& x)
		  	            {
                            /**
                            Construtor de cópia. Cria uma cópia de x.
                            */
		  	                abEdgeFrom = x.abEdgeFrom;
		  	                itFrom = x.itFrom;
    		  	            itTo = x.itTo;
	    	  	        }
		      	        bool operator== (const const_edge_iterator& x) const
		  	            {
                            /**
                            Retorna true se o iterator for o mesmo que x.
                            */
		  	                return (abEdgeFrom) ? itFrom == x.itFrom : itTo == x.itTo;
		  	            }
    		  	        bool operator!= (const const_edge_iterator& x) const
                        {
                            /**
                            Retorna true se o iterator for diferente de x.
                            */
                            return !(*this == x);
                        }
	    	  	        const Edge& operator* () const
                        {
                            /**
                            Retorna o arco apontado pelo iterator.
                            */
                            return (abEdgeFrom) ? *itFrom->edge() : *itTo->edge();
                        }
		      	        const Edge* operator-> () const
                        {
                            /**
                            Retorna um ponteiro para o arco apontado
                            pelo iterator.
                            */
                            return (abEdgeFrom) ? itFrom->edge() : itTo->edge();
                        }
		  	            const_edge_iterator& operator++ ()
		  	            {
                            /**
                            Aponta para o próximo nó.
                            */
		  	                if(abEdgeFrom) ++itFrom;
		  	                else ++itTo;
    		  	            return *this;
	    	  	        }
		      	        const_edge_iterator operator++ (int)
		  	            {
                            /**
                            Aponta para o próximo nó.
                            */
		  	                const_edge_iterator tmp = *this; ++*this; return tmp;
		  	            }
    		  	        const_edge_iterator& operator-- ()
	    	  	        {
                            /**
                            Aponta para o nó anterior.
                            */
		      	            if(abEdgeFrom) --itFrom;
		  	                else --itTo;
		  	                return *this;
		  	            }
    		  	        const_edge_iterator operator-- (int)
	    	  	        {
                            /**
                            Aponta para o nó anterior.
                            */
		      	            const_edge_iterator tmp = *this;
                            --*this;
                            return tmp;
		  	            }
		  	            const Node& incident_from() const
		  	            {
                            /**
                            Retorna o nó de onde o arco incide.
                            */
		  	                if(abEdgeFrom)
    		  	            {
	    	  	                throw BExcecaoEstruturaDados("Referência circular");
		      	            }
		  	                else
		  	                {
		  	                    return *(itTo->node());
		  	                }
    		  	        }
	    	  	        const Node& incident_to() const
		      	        {
                            /**
                            Retorna o nó para onde o arco incide.
                            */
		  	                if(abEdgeFrom)
		  	                {
		  	                    return *(itFrom->node());
		  	                }
    		  	            else
	    	  	            {
		      	                throw BExcecaoEstruturaDados("Referência circular");
		  	                }
		  	            }
		  	    };

			    const_node_iterator()
                {
                    /**
                    Cria um objeto vazio.
                    */
                }
			    const_node_iterator(const const_node_iterator& x)
                {
                    /**
                    Construtor de cópia. Cria uma cópia de x.
                    */
                    it = x.it;
                }
			    bool operator== (const const_node_iterator& x) const
                {
                    /**
                    Retorna true se o iterator for o mesmo que x.
                    */
                    return it == x.it;
                }
			    bool operator!= (const const_node_iterator& x) const
                {
                    /**
                    Retorna true se o iterator for diferente de x.
                    */
                    return !(*this == x);
                }
			    const Node& operator* () const
                {
                    /**
                    Retorna o nó apontado pelo iterator.
                    */
                    return it->node();
                }
			    const Node* operator-> () const
                {
                    /**
                    Retorna o endereço do nó apontado pelo iterator.
                    */
                    return &(it->node());
                }
			    const_node_iterator& operator++ ()
                {
                    /**
                    Aponta para o próximo nó.
                    */
                    ++it;
                    return *this;
                }
			    const_node_iterator operator++ (int)
			    {
                    /**
                    Aponta para o próximo nó.
                    */
			        const_node_iterator tmp = *this;
                    ++*this;
                    return tmp;
			    }
			    const_node_iterator& operator-- ()
                {
                    /**
                    Aponta para o nó anterior.
                    */
                    --it;
                    return *this;
                }
			    const_node_iterator operator-- (int)
			    {
                    /**
                    Aponta para o nó anterior.
                    */
			        const_node_iterator tmp = *this;
                    --*this;
                    return tmp;
			    }
			
			    const_edge_iterator IncidentsFrom_begin(void) const
			    {
                    /**
                    Retorna um iterator para o primeiro dos arcos
                    incidentes do nó.
                    */
			        return const_edge_iterator(it->EdgesFrom().begin());
			    }
			
			    const_edge_iterator IncidentsFrom_end(void) const
			    {
                    /**
                    Retorna um iterator para depois do último dos
                    arcos incidentes do nó.
                    */
			        return const_edge_iterator(it->EdgesFrom().end());
			    }
			
			    const_edge_iterator IncidentsTo_begin(void) const
			    {
                    /**
                    Retorna um iterator para o primeiro dos arcos
                    que incidem no nó.
                    */
			        return const_edge_iterator(it->EdgesTo().begin());
			    }

			    const_edge_iterator IncidentsTo_end(void) const
			    {
                    /**
                    Retorna um iterator para depois do último dos
                    arcos que incidem no nó.
                    */
			        return const_edge_iterator(it->EdgesTo().end());
			    }
        };

        // Constructors/Copy/Destructor
        BGraph(void);
        BGraph(const BGraph& Graph);
        virtual ~BGraph(void);
        BGraph& operator = (const BGraph& Graph);
        // iterators
        node_iterator begin(void);
        const_node_iterator begin(void) const;
        node_iterator end(void);
        const_node_iterator end(void) const;
        // Modifier
        void clear(void);
        void erase(const Node& node);
        void erase_edge(const Node& n1, const Node& n2);
        node_iterator insert(const Node& node);
        node_iterator::edge_iterator insert(const Node& no1, const Node& no2, const Edge& edge);
        // Observers
        bool empty(void) const;
        unsigned long size(void) const;
        node_iterator find(const Node& node);
        const_node_iterator find(const Node& node) const;
        Edge& find_edge(const Node& no1, const Node& no2);
        const Edge& find_edge(const Node& no1, const Node& no2) const;
        // Exceptions
        class BExcecaoEstruturaDados;
};
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
class BGraph<Node, Edge, Compare>::BExcecaoEstruturaDados : public BExcecao
{
    public:
        BExcecaoEstruturaDados(void) : BExcecao("Erro na estrutura de dados.") {};
        BExcecaoEstruturaDados(const BExcecaoEstruturaDados& e) : BExcecao(e) {};
        BExcecaoEstruturaDados(const char* msg) : BExcecao(msg) {};
        virtual ~BExcecaoEstruturaDados(void) {};
};
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
BGraph<Node, Edge, Compare>::BGraph(void)
{
    /**
    Cria um grafo vazio, sem nos ou arcos.
    */
}
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
BGraph<Node, Edge, Compare>::BGraph(const BGraph& Graph)
{
    /**
    Construtor de cópia. Cria uma cópia de x.
    */
    if(this != &Graph)
    {
        abSubstituiArcosIguais = Graph.abSubstituiArcosIguais;
        asetNodes = Graph.asetNodes;
    }
}
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
BGraph<Node, Edge, Compare>::~BGraph(void)
{
    /**
    Desaloca a memória alocada pelo próprio grafo.
    */
}
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
BGraph<Node, Edge, Compare>& BGraph<Node, Edge, Compare>::operator = (const BGraph<Node, Edge, Compare>& Graph)
{
    /**
    Copia x e retorna uma referência para o próprio grafo.
    */
    if(this != &Graph)
    {
        abSubstituiArcosIguais = Graph.abSubstituiArcosIguais;
        asetNodes = Graph.asetNodes;
    }
    return *this;
}
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
BGraph<Node, Edge, Compare>::node_iterator BGraph<Node, Edge, Compare>::begin(void)
{
    /**
    Retorna um iterator que aponta para o primeiro nó do grafo.
    */
    return asetNodes.begin();
}
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
BGraph<Node, Edge, Compare>::const_node_iterator BGraph<Node, Edge, Compare>::begin(void) const
{
    /**
    Retorna um const_iterator que aponta para o primeiro nó do grafo.
    */
    return asetNodes.begin();
}
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
void BGraph<Node, Edge, Compare>::clear(void)
{
    /**
    Remove todos os nós e arcos do grafo.
    */
    asetNodes.clear();
}
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
bool BGraph<Node, Edge, Compare>::empty(void) const
{
    /**
    Retorna true se o grafo não possuir nós.
    */
    return asetNodes.empty();
}
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
BGraph<Node, Edge, Compare>::node_iterator BGraph<Node, Edge, Compare>::end(void)
{
    /**
    Retorna um iterator que aponta para depois do último nó do grafo.
    */
    return asetNodes.end();
}
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
BGraph<Node, Edge, Compare>::const_node_iterator BGraph<Node, Edge, Compare>::end(void) const
{
    /**
    Retorna um const_iterator que aponta para depois do último nó do grafo.
    */
    return asetNodes.end();
}
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
void BGraph<Node, Edge, Compare>::erase(const Node& node)
{
    /**
    Remove o nó node. Se o nó não existir, lança uma exceção.
    */
    node_iterator node_it = asetNodes.find(BNode(node));

    if(node_it == asetNodes.end())
    {
        return;
    }
    asetNodes.erase(node_it.it);
    node_it = asetNodes.begin();
    while(node_it != asetNodes.end())
    {
        node_it.erase_edge_from(node);
        node_it.erase_edge_to(node);
        ++node_it;
    }
}
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
void BGraph<Node, Edge, Compare>::erase_edge(const Node& n1, const Node& n2)
{
    /**
    Remove o arco entre os nós node1 e node2. Se não existir arco,
    uma exceção é lançada.
    */
    node_iterator it1 = asetNodes.find(BNode(n1));
    it1.erase_edge_from(n2);
    node_iterator it2 = asetNodes.find(BNode(n2));
    it2.erase_edge_to(n1);
}
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
BGraph<Node, Edge, Compare>::node_iterator BGraph<Node, Edge, Compare>::find(const Node& node)
{
    /**
    Retorna um iterator que aponta para o nó node. Se o nó não for
    encontrado, retorna um iterator que aponta para depois do último
    nó do grafo.
    */
    return asetNodes.find(BNode(node));
}
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
BGraph<Node, Edge, Compare>::const_node_iterator BGraph<Node, Edge, Compare>::find(const Node& node) const
{
    /**
    Retorna um const_iterator que aponta para o nó node. Se o nó não
    for encontrado, retorna um const_iterator que aponta para depois
    do último nó do grafo.
    */
    return asetNodes.find(BNode(node));
}
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
Edge& BGraph<Node, Edge, Compare>::find_edge(const Node& node1, const Node& node2)
{
    /**
    Retorna o arco entre os nós node1 e node2. Se não existir arco,
    uma exceção é lançada.
    */
    Node no2(node2);
    setNodes::iterator it = asetNodes.find(BNode(node1));

    if(it == asetNodes.end())
    {
        throw BExcecaoEstruturaDados(MENSAGEM[1]);
    }
    else
    {
        BNode& edges = *it;
        BNode::setPairpNodeEdge::iterator itPar = edges.EdgesFrom().find(BNode::PairpNodeEdge(&no2, Edge()));
        if(itPar == edges.EdgesFrom().end())
        {
            throw BExcecaoEstruturaDados(MENSAGEM[3]);
        }
        else
        {
            return *(node_iterator::edge_iterator(itPar));
        }
    }
}
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
const Edge& BGraph<Node, Edge, Compare>::find_edge(const Node& node1, const Node& node2) const
{
    /**
    Retorna o arco entre os nós node1 e node2. Se não existir arco,
    uma exceção é lançada.
    */
    Node no2(node2);
    setNodes::const_iterator it = asetNodes.find(BNode(node1));

    if(it == asetNodes.end())
    {
        throw BExcecaoEstruturaDados(MENSAGEM[1]);
    }
    else
    {
        const BNode& edges = *it;
        BNode::setPairpNodeEdge::const_iterator itPar = edges.EdgesFrom.find(PairpNodeEdge(&no2, Edge()));
        if(itPar == edges.EdgesFrom.end())
        {
            throw BExcecaoEstruturaDados(MENSAGEM[3]);
        }
        else
        {
            return *(const_edge_iterator(itPar));
        }
    }
}
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
BGraph<Node, Edge, Compare>::node_iterator BGraph<Node, Edge, Compare>::insert(const Node& node)
{
    /**
    Insere o nó node e retorna um iterator que aponta para ele.
    */
    pair<setNodes::iterator, bool> p = asetNodes.insert(BNode(node));

    if(p.second)
    {
        return node_iterator(p.first);
    }
    else
    {
        throw BExcecaoEstruturaDados(MENSAGEM[0]);
    }
}
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
BGraph<Node, Edge, Compare>::node_iterator::edge_iterator BGraph<Node, Edge, Compare>::insert(const Node& no1, const Node& no2, const Edge& edge)
{
    /**
    Insere o arco edge entre os nós node1 e node2 e retorna um iterator
    que aponta para ele.
    */
    Node* pNo1;
    Node* pNo2;
    node_iterator it1 = find(no1);
    node_iterator it2 = find(no2);
    if((it1 == end()) || (it2 == end()))
    {
        throw BExcecaoEstruturaDados(MENSAGEM[1]);
    }
    pNo1 = &(*it1);
    pNo2 = &(*it2);
    BNode& node1 = *(it1.it);
    pair<BNode::setPairpNodeEdge::iterator, bool> p = node1.EdgesFrom().insert(BNode::PairpNodeEdge(pNo2, edge));
    if(p.second)
    {
        BNode& node2 = *(it2.it);
        node2.EdgesTo().insert(BNode::PairpNodepEdge(pNo1, p.first->edge() ));
        return node_iterator::edge_iterator(p.first);
    }
    else
    {
        throw BExcecaoEstruturaDados(MENSAGEM[2]);
    }
}
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
unsigned long BGraph<Node, Edge, Compare>::size(void) const
{
    /**
    Retorna o número de nós do grafo.
    */
    return asetNodes.size();
}
//---------------------------------------------------------------------------
template <class Node, class Edge, class Compare>
const char* BGraph<Node, Edge, Compare>::MENSAGEM[] =
{
    "Nó preexistente.",                 //0
    "Nó não encontrado.",               //1
    "Arco preexistente.",               //2
    "Arco não encontrado.",             //3
    "",
    ""
};
//---------------------------------------------------------------------------
} // End namespace BBib
//---------------------------------------------------------------------------
//#pragma option pop

#endif

