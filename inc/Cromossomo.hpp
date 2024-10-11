#ifndef CROMOSSOMO_HPP
#define CROMOSSOMO_HPP

#include <iostream>
#include <random>
#include <vector>
#include "Graph.hpp"

struct Cromossomo {
	size_t quantidadeDeGenes;
        std::vector<int> genes;
        Graph* graph;
	// size_t fitnessValue;
	
	Cromossomo(std::vector<int> genes, Graph* graph);

	Cromossomo(size_t quantidadeDeGenes, Graph* graph);

	Cromossomo(std::vector<int> primeiraMetade, std::vector<int> segundaMetade, Graph* graph);
    
    	Cromossomo(Cromossomo* cromossomo);
        
	~Cromossomo();

    friend std::ostream& operator<<(std::ostream& os, const Cromossomo& cromossomo);
};

#endif
