//---------------------------------------------------------------------------
#include <boost/test/minimal.hpp>
#pragma hdrstop
//---------------------------------------------------------------------------
int test_main(int, char**)
{
    //TesteSimples
    if(system("testeSimples\\testeSimples.exe > simples.txt"))
    {
        BOOST_FAIL("error executing testeSimples\\testeSimples.exe");
    }
    if(system("diff simples.txt simples.ref > simples.log"))
    {
        BOOST_FAIL("simples.txt and simples.ref differ.");
    }
    //TesteClasses
    if(system("testeClasses\\testeClassesGraph.exe > classes.txt"))
    {
        BOOST_FAIL("error executing testeClasses\\testeClassesGraph.exe");
    }
    if(system("diff classes.txt classes.ref > classes.log"))
    {
        BOOST_FAIL("classes.txt and classes.ref differ.");
    }
    //Dijkstra
    if(system("Testedijkstra\\Testedijkstra.exe > dijkstra.txt"))
    {
        BOOST_ERROR("error executing Testedijkstra\\Testedijkstra.exe");
    }
    if(system("diff dijkstra.txt dijkstra.ref > dijkstra.log"))
    {
        BOOST_ERROR("dijkstra.txt and dijkstra.ref differ.");
    }
    //Minimal spanning tree
    if(system("testedesempenho\\testedesempenho.exe > desempenho.txt"))
    {
        BOOST_ERROR("error executing testedesempenho\\testedesempenho.exe");
    }
    if(system("diff desempenho.txt desempenho.ref > desempenho.log"))
    {
        BOOST_ERROR("desempenho.txt and desempenho.ref differ.");
    }
    return 0;
}
//---------------------------------------------------------------------------
