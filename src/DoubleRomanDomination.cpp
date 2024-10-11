#include "DoubleRomanDomination.hpp"

DoubleRomanDomination::~DoubleRomanDomination() {
    delete this->geneticAlgorithm;
    delete this->graph;
}
AlgoritmoGenetico* DoubleRomanDomination::getGeneticAlgorithm() {
    return this->geneticAlgorithm;
}

Graph* DoubleRomanDomination::getGraph() {
    return this->graph;
}

size_t DoubleRomanDomination::getGamma2R() {
    size_t summation = 0;
    Cromossomo* temp = this->geneticAlgorithm->rodarAG(100, DoubleRomanDomination::heuristic1, this->graph);

    std::for_each(temp->genes.begin(), temp->genes.end(), [&summation](int element) {
        summation += element;
    });

    return summation;                                                                                                                             
}

Cromossomo* DoubleRomanDomination::heuristic1(Graph* graph) {
	Cromossomo* solution = new Cromossomo(graph->getOrder(), graph);
	std::random_device randomNumber;
	std::mt19937 seed(randomNumber());
	std::uniform_int_distribution<int> gap(0, graph->getOrder() - 1);
	
	size_t choosenVertex = 0;
                             
    while (graph->getOrder() > 0) {
	    choosenVertex = gap(seed);
	    while (!graph->vertexExists(choosenVertex))
	   	    choosenVertex = gap(seed);
	    	    
	    solution->genes[choosenVertex] = 3;
	    for (const auto& it: graph->getAdjacencyList(choosenVertex)) {
		    if (solution->genes[it] == -1)
		        solution->genes[it] = 0;
	    }	
        
   	    graph->deleteAdjacencyList(choosenVertex);
    	
	    if (graph->getOrder() == 1) {
	    	choosenVertex = graph->getAdjacencyList().begin()->first;
	        solution->genes[choosenVertex] = 3;
                graph->deleteVertex(choosenVertex);
        }
   }  
    return solution;    
}



Cromossomo* DoubleRomanDomination::heuristic2(Graph* graph) {
    Cromossomo* solution = new Cromossomo(graph->getOrder(), graph); 
    std::random_device randomNumber;
    std::mt19937 seed(randomNumber());
    std::uniform_int_distribution<int> gap(0, graph->getOrder() - 1);
    
    size_t choosenVertex = 0;
    size_t graphOrder = graph->getOrder();

    while (graph->getOrder() > 0) {
        choosenVertex = gap(seed);
        while (!graph->vertexExists(choosenVertex))
    	    choosenVertex = gap(seed);

        solution->genes[choosenVertex] = 3; 
        for (const auto& it: graph->getAdjacencyList(choosenVertex)) {
            if (solution->genes[it] == -1)
                solution->genes[it] = 0;
        }
 
        graph->deleteAdjacencyList(choosenVertex);

        for (size_t i = 0; i < graphOrder; ++i) {
           if (graph->vertexExists(i)) {
                if (graph->getVertexDegree(i) == 0) {
                    solution->genes[i] = 2;
                    graph->deleteVertex(i);
                }
            }
        }
    }

	return solution;
}


Cromossomo* DoubleRomanDomination::heuristic3(Graph* graph) {
    Cromossomo* solution = new Cromossomo(graph->getOrder(), graph);
    std::vector<size_t> sortedVertices(graph->getOrder());
    size_t graphOrder = graph->getOrder();

    for (size_t i = 0; i < graph->getOrder(); ++i)
        sortedVertices[i] = i;

    std::sort(sortedVertices.begin(), sortedVertices.end(),
        [&](size_t a, size_t b) {
            return graph->getVertexDegree(a) > graph->getVertexDegree(b);
    });

    size_t choosenVertex = 0;

    while ((graph->getOrder() > 0) && (choosenVertex < sortedVertices.size())) {

        if (choosenVertex >= sortedVertices.size()) break;

        while (choosenVertex < sortedVertices.size() && 
                (!graph->vertexExists(sortedVertices[choosenVertex]))) {
               ++choosenVertex;
        }

        if (choosenVertex >= sortedVertices.size()) break;

        solution->genes[sortedVertices[choosenVertex]] = 3;
        
        for (const auto& it : graph->getAdjacencyList(sortedVertices[choosenVertex])) {
            if (solution->genes[it] == -1)
                solution->genes[it] = 0;
        }

    	graph->deleteAdjacencyList(sortedVertices[choosenVertex++]);

        for (size_t i = 0; i < graphOrder; ++i) {
           if (graph->vertexExists(i)) {
                if (graph->getVertexDegree(i) == 0) {
                    solution->genes[i] = 2;
                    graph->deleteVertex(i);
                }
            }
        }
    }

    return solution;
}
