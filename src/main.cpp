#include "AlgoritmoGenetico.hpp"
#include "DoubleRomanDomination.hpp"
#include "Graph.hpp"

int main() {
	// AlgoritmoGenetico a(10, 30, 0.35, 0.75);
	Graph* graph = new Graph(10, false, 0.1); 
	
    	std::cout << *graph << std::endl;
    	
	DoubleRomanDomination* drd = new DoubleRomanDomination(graph);
	drd->heuristic1();
	
	// std::cout << graph->getOrder() << std::endl;

    	
    	//graph->deleteAdjacencyList(4);
    	
    	//std::cout << *graph << std::endl;
    	
    	// std::cout << *graph << std::endl;
    	// std::cout << graph->getVertexDegree(3) << std::endl;
    	
	/*for (size_t i = 0; i < teste; ++i) {
		graph->deleteAdjacencyList(i);
		std::cout << *graph << std::endl;
	}*/

	
	
	
	//std::random_device randomNumber;
	//std::mt19937 seed(randomNumber());
	//std::uniform_int_distribution<int> gap(0, graph->getOrder() - 1);
	
	/*while (graph->getOrder() > 0) {
		graph->deleteAdjacencyList(graph->getVertices()[gap(seed) % graph->getOrder()]);
		std::cout << "size: " << graph->getSize() << std::endl;
		std::cout << "order: " << graph->getOrder() << std::endl;
		std::cout << *graph << std::endl;
	} */
	

	
   //	std::cout << *graph << std::endl;
	
	return 0;
}
