#include "AlgoritmoGenetico.hpp"
#include "DoubleRomanDomination.hpp"
#include "Graph.hpp"

int main() {
	Graph* graph = new Graph(100, false, 0.1);
    DoubleRomanDomination* drd = new DoubleRomanDomination(graph, 100, graph->getOrder(), 0.35, 0.75);
    std::cout << drd->getGamma2R(); 
    return 0;
}
