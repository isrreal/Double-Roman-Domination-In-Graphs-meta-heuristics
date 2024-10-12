#ifndef CROMOSSOME_HPP
#define CROMOSSOME_HPP

#include <iostream>
#include <random>
#include <vector>
#include "Graph.hpp"

struct Cromossome {
	size_t genesSize;
    std::vector<int> genes;
    Graph* graph;
        // indice de onde se encontra no vetor de população
    size_t indexRemove;
	
	Cromossome(std::vector<int> genes, Graph* graph);

	Cromossome(size_t genesSize, Graph* graph);

	Cromossome(std::vector<int> primeiraMetade, std::vector<int> segundaMetade, Graph* graph);
    
    Cromossome(Cromossome* cromossome);
        
	~Cromossome();

    friend std::ostream& operator<<(std::ostream& os, const Cromossome& cromossome);
};

#endif
