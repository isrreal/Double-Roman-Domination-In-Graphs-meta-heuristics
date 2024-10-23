#ifndef CHROMOSSOME_HPP
#define CHROMOSSOME_HPP

#include <iostream>
#include <random>
#include <vector>
#include "Graph.hpp"

struct Chromosome {
	size_t genesSize;
    std::vector<int> genes;
    size_t indexRemove;
    size_t fitnessValue;
	
	Chromosome(std::vector<int> genes);

	Chromosome(size_t genesSize);

	Chromosome(std::vector<int> primeiraMetade, std::vector<int> segundaMetade);
    
    Chromosome(Chromosome* chromosome);
        
	~Chromosome();

    friend std::ostream& operator<<(std::ostream& os, const Chromosome& chromosome);
};

#endif
