#include "DoubleRomanDomination.hpp"

void DoubleRomanDomination::criarPopulacao(size_t quantidadeDeCromossomos) {
    for (size_t i = 0; i < quantidadeDeCromossomos; ++i)        
        this->populacao.push_back(heuristic3());
}


Cromossomo* DoubleRomanDomination::heuristic1() {
	Graph* temp = new Graph(*this->graph);
	Cromossomo* solution = new Cromossomo(temp->getOrder(), temp);
	
	std::random_device randomNumber;
	std::mt19937 seed(randomNumber());
	std::uniform_int_distribution<int> gap(0, temp->getOrder() - 1);
	
	size_t choosenVertex = -1;
                             
    while (temp->getOrder() > 0) {
	    choosenVertex = gap(seed);
	    while (temp->getAdjacencyList(choosenVertex) == std::list<int>{-1})
		    choosenVertex = gap(seed);	
	    solution->genes[choosenVertex] = 3;
	    	
	    for (const auto& it: temp->getAdjacencyList(choosenVertex)) {
		    if (solution->genes[it] == -1)
			    solution->genes[it] = 0;
	    }
	
   	    temp->deleteAdjacencyList(choosenVertex);
    	
	    if (temp->getOrder() == 1) {
		    while (temp->getAdjacencyList(choosenVertex) == std::list<int>{-1})
		        choosenVertex = gap(seed);
	        solution->genes[choosenVertex] = 3;
            temp->deleteAdjacencyList(choosenVertex);
        }
   }  
    	
    return solution;    
}



Cromossomo* DoubleRomanDomination::heuristic2() {
    Graph* temp = new Graph(*this->graph);
    Cromossomo* solution = new Cromossomo(temp->getOrder(), temp); 
    std::random_device randomNumber;
    std::mt19937 seed(randomNumber());
    std::uniform_int_distribution<int> gap(0, temp->getOrder() - 1);
    
    size_t choosenVertex = 0;
    size_t tempOrder = temp->getOrder();

    while (temp->getOrder() > 0) {
        choosenVertex = gap(seed);
        while (temp->getAdjacencyList(choosenVertex) == std::list<int>{-1})
            choosenVertex = gap(seed);

    	solution->genes[choosenVertex] = 3;
 
        for (const auto& it: temp->getAdjacencyList(choosenVertex)) {
            if (solution->genes[it] == -1)
                solution->genes[it] = 0;
        }
 
        temp->deleteAdjacencyList(choosenVertex);

        for (size_t i = 0; i < tempOrder; ++i) {
           if (temp->getAdjacencyList(i).front() != -1) {
                if (temp->getVertexDegree(i) == 0) {
                    solution->genes[i] = 2;
                    temp->deleteVertex(i);
                }
            }
        }
    }

	return solution;
}


Cromossomo* DoubleRomanDomination::heuristic3() {
    Graph* temp = new Graph(*this->graph);
    Cromossomo* solution = new Cromossomo(temp->getOrder(), temp);
    std::vector<size_t> sortedVertices(temp->getOrder());
    size_t tempOrder = temp->getOrder();

    for (size_t i = 0; i < temp->getOrder(); ++i)
        sortedVertices[i] = i;

    std::sort(sortedVertices.begin(), sortedVertices.end(),
        [&](size_t a, size_t b) {
            return temp->getVertexDegree(a) > temp->getVertexDegree(b);
    });

    size_t choosenVertex = 0;

    while ((temp->getOrder() > 0) && (choosenVertex < sortedVertices.size())) {

        if (choosenVertex >= sortedVertices.size()) break;

        while (choosenVertex < sortedVertices.size() && 
               temp->getAdjacencyList(sortedVertices[++choosenVertex]) == std::list<int>{-1});

        if (choosenVertex >= sortedVertices.size()) break;

        solution->genes[sortedVertices[choosenVertex]] = 3;

        for (const auto& it : temp->getAdjacencyList(sortedVertices[choosenVertex])) {
            if (solution->genes[it] == -1)
                solution->genes[it] = 0;
        }

    	temp->deleteAdjacencyList(sortedVertices[choosenVertex++]);

        for (size_t i = 0; i < tempOrder; ++i) {
           if (temp->getAdjacencyList(i).front() != -1) {
                if (temp->getVertexDegree(i) == 0) {
                    solution->genes[i] = 2;
                    temp->deleteVertex(i);
                }
            }
        }
    }

    return solution;
}
