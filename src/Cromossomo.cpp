#include "Cromossomo.hpp"

Cromossomo::~Cromossomo() {}

Cromossomo::Cromossomo(std::vector<int> genes, Graph* graph) {
	this->quantidadeDeGenes = genes.size();
	this->genes = genes;
	this->graph = graph;
}

Cromossomo::Cromossomo(size_t quantidadeDeGenes, Graph* graph) {
    this->quantidadeDeGenes = quantidadeDeGenes;
    this->genes = std::vector<int>(quantidadeDeGenes, -1);
    this->graph = graph;
} 

Cromossomo::Cromossomo(std::vector<int> primeiraMetade, std::vector<int> segundaMetade, Graph* graph) {
    this->quantidadeDeGenes = primeiraMetade.size() + segundaMetade.size(); 
    this->genes = primeiraMetade;
    this->genes.insert(this->genes.end(), segundaMetade.begin(), segundaMetade.end());
    this->graph = nullptr;	
}

Cromossomo::Cromossomo(Cromossomo* cromossomo) {
    this->quantidadeDeGenes = cromossomo->quantidadeDeGenes;
    this->genes = cromossomo->genes;
    this->graph = cromossomo->graph;
}

std::ostream& operator<<(std::ostream& os, const Cromossomo& cromossomo) {
    for (const auto& it: cromossomo.genes)
        os << it << " ";
    return os;
}
