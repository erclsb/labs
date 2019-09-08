#ifndef BGRAPHALGORITHMSAUXH
#define BGRAPHALGORITHMSAUXH

#include <functional>

namespace BBib
{

using std::less;

typedef double number;

template <class Node, class Number = number, class Compare = less<Node> >
struct Triple
{
    private:
        static Compare compare;

    public:
        const Node* node;
        Triple* precedent;
        Number distance;
        Triple(void){};
        explicit Triple(const Node& n) {node = &n;};
        bool operator<(const Triple& triple) const
        {
            return compare(*node,*triple.node);
        }
};

template<class Node,class Number,class Compare>
Compare Triple<Node,Number,Compare>::compare;


namespace Bbib
{

template<class Node,class Number,class Compare>
class CompareTriple
{
    public:
        bool operator()(const Triple<Node,Number,Compare>* t1,
            const Triple<Node,Number,Compare>* t2) const
        {
            return t1->distance < t2->distance;
        }
};

} //namespace Bbib

} // namespace BBib

#endif
