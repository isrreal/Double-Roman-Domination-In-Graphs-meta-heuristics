#include "AlgoritmoGenetico.hpp"
#include "DoubleRomanDomination.hpp"
#include "Graph.hpp"

int main() {
	// AlgoritmoGenetico a(10, 30, 0.35, 0.75);
	Graph* graph = new Graph(10, false, 0.1); 
	std::random_device randomNumber;
	std::mt19937 seed(randomNumber());
	std::uniform_int_distribution<int> gap(0, graph->getOrder() - 1);
    
    //std::cout << *graph << std::endl;
    DoubleRomanDomination* drd = new DoubleRomanDomination(graph);
    drd->heuristic3();
    
   // for (const auto& it: drd->heuristic3()->genes)
     //   std::cout << it << " ";
	
	return 0;
}
