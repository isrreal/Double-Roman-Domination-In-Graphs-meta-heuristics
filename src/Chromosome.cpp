#include "Chromosome.hpp"

Chromosome::~Chromosome() {
    delete this->graph;
}

Chromosome::Chromosome(std::vector<int> genes, Graph* graph = nullptr) {
	this->genesSize = genes.size();
	this->genes = genes;
	this->graph = graph;
	this->indexRemove = 0;
	this->fitnessValue = 0;
}

Chromosome::Chromosome(size_t genesSize, Graph* graph = nullptr) {
    this->genesSize = genesSize;
    this->genes = std::vector<int>(genesSize, -1);
    this->graph = graph;
    this->indexRemove = 0;
    this->fitnessValue = 0;
} 

Chromosome::Chromosome(std::vector<int> firstHalf, std::vector<int> secondHalf, Graph* graph = nullptr) {
    this->genesSize = firstHalf.size() + secondHalf.size(); 
    this->genes = firstHalf;
    this->genes.insert(this->genes.end(), secondHalf.begin(), secondHalf.end());
    this->graph = nullptr;
    this->indexRemove = 0;	
    this->fitnessValue = 0;
}

Chromosome::Chromosome(Chromosome* chromosome) {
    this->genesSize = chromosome->genesSize;
    this->genes = chromosome->genes;
    this->graph = chromosome->graph;
    this->indexRemove = chromosome->indexRemove;
    this->fitnessValue = chromosome->fitnessValue;
}

std::ostream& operator<<(std::ostream& os, const Chromosome& chromosome) {
    for (const auto& it: chromosome.genes)
        os << it << " ";
    return os;
}
