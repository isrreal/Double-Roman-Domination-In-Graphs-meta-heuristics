#include "DoubleRomanDomination.hpp"

Cromossomo* DoubleRomanDomination::heuristic1() {
	Graph* temp = new Graph(*this->graph);
	Cromossomo* solution = new Cromossomo(temp->getOrder());
	
	std::random_device randomNumber;
	std::mt19937 seed(randomNumber());
	std::uniform_int_distribution<int> gap(0, temp->getOrder() - 1);
	
	size_t choosenVertex = -1;
	
    	while (temp->getOrder() > 0) {
	    	choosenVertex = gap(seed) % temp->getOrder();
	    	while (temp->getAdjacencyList(choosenVertex) == std::list<int>{-1}) {
		    		choosenVertex = gap(seed) % temp->getOrder();	
		    		std::cout << choosenVertex << std::endl;
		}	
	    	solution->genes[choosenVertex] = 3;
	    	
		for (const auto& it: temp->getAdjacencyList(choosenVertex)) 
    		solution->genes[it] = 0;
    		
		temp->deleteAdjacencyList(choosenVertex);
	/*    	
		if (temp->getOrder() == 1) {
		    solution->genes[choosenVertex] = 3;
	    		temp->deleteAdjacencyList(choosenVertex);
	    	}
	  */  	
    	}
    	
	for (const auto& it: solution->genes)
    		std::cout << it << " ";

    return solution;    
}

/*
Cromossomo* DoubleRomanDomination::heuristic2() {
    Graph* temp = new Graph(*this->graph);
    Cromossomo* solution = new Cromossomo(temp->getOrder());
 
    std::random_device randomNumber;
    std::mt19937 seed(randomNumber());
    std::uniform_int_distribution<int> gap(0, temp->getOrder() - 1);
 
    size_t choosenVertex = 0;
  
    while (temp->getOrder() > 0) {
    	choosenVertex = gap(seed) % temp->getOrder();	 
    	solution->genes[choosenVertex] = 3;
 
        for (const auto& it: temp->getAdjacencyList(choosenVertex))
            solution->genes[it] = 0;
 
        temp->deleteAdjacencyList(choosenVertex);
        
        for (size_t i = 0; i < temp->getOrder(); ++i) { 
            if (temp->getVertexDegree(temp->getVertices()[i]) == 0) {
                solution->genes[i] = 2;
                temp->deleteAdjacencyList(temp->getVertices()[i]);
            }
        }
    }
    
	return solution;
}


Cromossomo* DoubleRomanDomination::heuristic3() {
    Graph* temp = new Graph(*this->graph);
    Cromossomo* solution = new Cromossomo(temp->getOrder());

    std::vector<Vertex*> sortedVertices(temp->getVertices());
    Vertex* choosenVertex = nullptr;
    int cont = 0;

    std::sort(sortedVertices.begin(), sortedVertices.end(),
              [&](Vertex* a, Vertex* b) {
                  return temp->getVertexDegree(a) > temp->getVertexDegree(b);
              });

    while (temp->getOrder() > 0) {
	    choosenVertex = sortedVertices[cont++];

	    solution->genes[choosenVertex->identificator] = 3;

	    for (const auto& it: temp->getAdjacencyList(choosenVertex))
		    solution->genes[it] = 0;

	    temp->deleteAdjacencyList(choosenVertex);

	    for (size_t i = 0; i < temp->getOrder(); ++i) {
		    if (temp->getVertexDegree(temp->getVertices()[i]) == 0) {
		        solution->genes[temp->getVertices()[i]->identificator] = 2;
		        temp->deleteAdjacencyList(temp->getVertices()[i]);
		    }
	    }
    }
    
     //for (const auto& it : solution->genes)
	//	std::cout << solution->genes[it] << " ";

    return solution;
}
*/
