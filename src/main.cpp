#include "AlgoritmoGenetico.hpp"
#include "DoubleRomanDomination.hpp"
#include "Graph.hpp"

int main() {
	Graph* graph = new Graph(10, false, 0.1);
   // std::cout << *graph << "\n\n";

    
   // graph->deleteAdjacencyList(9);
   // std::cout << *graph << "\n\n";
   // DoubleRomanDomination* drd = new DoubleRomanDomination(graph, 100, graph->getOrder(), 0.35, 0.75);
    std::cout << *(DoubleRomanDomination::heuristic1(graph));
//    std::cout << drd->getGamma2R(); 
    return 0;
}
