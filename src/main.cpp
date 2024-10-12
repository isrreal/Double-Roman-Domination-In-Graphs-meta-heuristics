#include "GeneticAlgorithm.hpp"
#include "DoubleRomanDomination.hpp"
#include "Graph.hpp"

int main() {
    Graph* graph = new Graph(10, false, 0.1);
    DoubleRomanDomination* drd = new DoubleRomanDomination(graph, 100, graph->getOrder(), 500);
    std::cout << drd->getGamma2R(); 
    return 0;
}
