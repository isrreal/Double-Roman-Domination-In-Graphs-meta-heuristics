#include "Cromossome.hpp"

Cromossome::~Cromossome() {
    delete this->graph;
}

Cromossome::Cromossome(std::vector<int> genes, Graph* graph) {
	this->genesSize = genes.size();
	this->genes = genes;
	this->graph = graph;
	this->indexRemove = 0;
}

Cromossome::Cromossome(size_t genesSize, Graph* graph) {
    this->genesSize = genesSize;
    this->genes = std::vector<int>(genesSize, -1);
    this->graph = graph;
    this->indexRemove = 0;
} 

Cromossome::Cromossome(std::vector<int> firstHalf, std::vector<int> secondHalf, Graph* graph) {
    this->genesSize = firstHalf.size() + secondHalf.size(); 
    this->genes = firstHalf;
    this->genes.insert(this->genes.end(), secondHalf.begin(), secondHalf.end());
    this->graph = nullptr;
    this->indexRemove = 0;	
}

Cromossome::Cromossome(Cromossome* cromossome) {
    this->genesSize = cromossome->genesSize;
    this->genes = cromossome->genes;
    this->graph = cromossome->graph;
    this->indexRemove = cromossome->indexRemove;
}

std::ostream& operator<<(std::ostream& os, const Cromossome& cromossome) {
    for (const auto& it: cromossome.genes)
        os << it << " ";
    return os;
}
