#include "AlgoritmoGenetico.hpp"
#include "DoubleRomanDomination.hpp"
#include "Graph.hpp"

int main() {
	// AlgoritmoGenetico a(10, 30, 0.35, 0.75);
	Graph* graph = new Graph(10, false, 0.1); 
	std::random_device randomNumber;
	std::mt19937 seed(randomNumber());
	std::uniform_int_distribution<int> gap(0, graph->getOrder() - 1);

        DoubleRomanDomination* drd = new DoubleRomanDomination(graph);
        drd->heuristic1();
  
	
	return 0;
}
