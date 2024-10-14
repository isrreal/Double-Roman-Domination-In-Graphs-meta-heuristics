#ifndef CHROMOSSOME_HPP
#define CHROMOSSOME_HPP

#include <iostream>
#include <random>
#include <vector>
#include "Graph.hpp"

struct Chromosome {
	size_t genesSize;
    	std::vector<int> genes;
    	Graph* graph;
        // indice de onde se encontra no vetor de população
    	size_t indexRemove;
    	size_t fitnessValue;
	
	Chromosome(std::vector<int> genes, Graph* graph);

	Chromosome(size_t genesSize, Graph* graph);

	Chromosome(std::vector<int> primeiraMetade, std::vector<int> segundaMetade, Graph* graph);
    
    	Chromosome(Chromosome* chromosome);
        
	~Chromosome();

    friend std::ostream& operator<<(std::ostream& os, const Chromosome& chromosome);
};

#endif
