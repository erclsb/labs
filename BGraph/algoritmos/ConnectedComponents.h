#ifndef CONNECTEDCOMPONENTSH
#define CONNECTEDCOMPONENTSH

#pragma option push -A-

#include <set>
#include <queue>
#include "BGraph.h"

namespace BBib
{

using std::set;
using std::queue;

template <class Node, class Compare = less<Node> >
struct PairNodeComponent
{
    private:
        static Compare compare;

    public:
        const Node* node;
        int component;
        PairNodeComponent(void){};
        bool operator<(const PairNodeComponent& pair) const
        {
            return compare(*node,*pair.node);
        }
};

template<class Node,class Compare>
Compare PairNodeComponent<Node,Compare>::compare;

template <class Node,class Compare = less<Node> >
class ComponentMap : public set<PairNodeComponent<Node, Compare> > {};

template <class Node, class Edge, class Compare>
void FindConnectedComponents(const BGraph<Node,Edge,Compare>& Graph,
    ComponentMap<Node>& Map, int& nComponents)
{
    BGraph<Node,Edge,Compare>::const_node_iterator node_it;
    BGraph<Node,Edge,Compare>::const_node_iterator node_end;
    BGraph<Node,Edge,Compare>::const_node_iterator::const_edge_iterator edge_it;
    BGraph<Node,Edge,Compare>::const_node_iterator::const_edge_iterator edge_end;
    queue<const Node*> Nodes;
    PairNodeComponent<Node> pair;
    ComponentMap<Node>::iterator aux_map_it;
    BGraph<Node,Edge,Compare>::const_node_iterator aux_node_it;
    const Node* node;
    const Node* adjnode;

    nComponents = 0;
    node_it = Graph.begin();
    node_end = Graph.end();
    while(node_it != node_end)
    {
        pair.node = &*node_it;
        pair.component = -1;
        Map.insert(pair);
        ++node_it;
    }
    node_it = Graph.begin();
    node_end = Graph.end();
    while(node_it != node_end)
    {
        pair.node = &*node_it;
        aux_map_it = Map.find(pair);
        if(aux_map_it->component == -1)
        {
            aux_map_it->component = nComponents;
            Nodes.push(&*node_it);
            while(! Nodes.empty())
            {
                node = Nodes.front();
                Nodes.pop();
                aux_node_it = Graph.find(*node);
                edge_it = aux_node_it.IncidentsFrom_begin();
                edge_end = aux_node_it.IncidentsFrom_end();
                while(edge_it != edge_end)
                {
                    adjnode = &(edge_it.incident_to());
                    pair.node = adjnode;
                    aux_map_it = Map.find(pair);
                    if(aux_map_it->component == -1)
                    {
                        aux_map_it->component = nComponents;
                        Nodes.push(adjnode);
                    }
                    ++edge_it;
                }
            }
            ++nComponents;
        }
        ++node_it;
    }
}

} // namespace BBib

#pragma option pop
#endif
