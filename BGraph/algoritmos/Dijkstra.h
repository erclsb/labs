#ifndef DIJKSTRAH
#define DIJKSTRAH

#pragma option push -A-

#include "BGraph.h"
#include "BGraphAlgorithmsAux.h"
#include <limits>
#include <list>

namespace BBib
{

using std::set;
using std::numeric_limits;

template <class Node, class Number = number, class Compare = less<Node> >
class MinPath : public set< Triple<Node,Number,Compare> > {};

template <class Node, class Edge, class Number, class Compare>
void ShortestPath(const BGraph<Node,Edge,Compare>& Graph, const Node& Source,
    MinPath<Node,Number,Compare>& minPath)
{
    using Bbib::CompareTriple;
    using std::list;

    typedef Triple<Node, Number,Compare> Tri;

    Number Infinity;
    BGraph<Node,Edge,Compare>::const_node_iterator it;
    BGraph<Node,Edge,Compare>::const_node_iterator end;
    BGraph<Node,Edge,Compare>::const_node_iterator aux;
    BGraph<Node,Edge,Compare>::const_node_iterator::const_edge_iterator edge_it;
    BGraph<Node,Edge,Compare>::const_node_iterator::const_edge_iterator edge_end;
    list<Tri*> priority;
    list<Tri*>::iterator pri_it;
    list<Tri*>::iterator pri_end;
    Tri triple;
    Tri* pAdjacentTriple;
    Number distance;
    CompareTriple<Node,Number,Compare> compareTriple;

    if(numeric_limits<Number>::has_infinity)
        Infinity = numeric_limits<Number>::infinity();
    else throw;
    minPath.clear();
    it = Graph.begin();
    end = Graph.end();
    triple.precedent = NULL;
    triple.distance = Infinity;
    while(it != end)
    {
        triple.node = &(*(it));
        priority.push_back(&(*minPath.insert(triple).first));
        ++it;
    }
    triple.node = &Source;
    minPath.find(triple)->distance = 0;
    priority.sort(compareTriple);
    while(!priority.empty())
    {
        Tri* pTriple = priority.front();
        priority.pop_front();
        aux = Graph.find(*pTriple->node);
        edge_it = aux.IncidentsFrom_begin();
        edge_end = aux.IncidentsFrom_end();
        while(edge_it != edge_end)
        {
            distance = pTriple->distance + (Number) *edge_it;
            const Node& adjacent = edge_it.incident_to();
            triple.node = &adjacent;
            pAdjacentTriple = &(*minPath.find(triple));
            if(pAdjacentTriple->distance > distance)
            {
                pAdjacentTriple->distance = distance;
                pAdjacentTriple->precedent = pTriple;
                priority.sort(compareTriple);
            }
            ++edge_it;
        }
    }
}

} // namespace BBib

#pragma option pop
#endif
