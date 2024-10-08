#include "Cromossomo.hpp"

Cromossomo::~Cromossomo() {}

Cromossomo::Cromossomo(std::vector<int> genes) {
	this->quantidadeDeGenes = genes.size();
	this->genes = genes;
}

Cromossomo::Cromossomo(size_t quantidadeDeGenes) {
    this->quantidadeDeGenes = quantidadeDeGenes;
    this->genes = std::vector<int>(quantidadeDeGenes, -1);
} 

Cromossomo::Cromossomo(std::vector<int> primeiraMetade, std::vector<int> segundaMetade) {
    this->quantidadeDeGenes = primeiraMetade.size() + segundaMetade.size(); 
    this->genes = primeiraMetade;
    this->genes.insert(this->genes.end(), segundaMetade.begin(), segundaMetade.end());
}

std::ostream& operator<<(std::ostream& os, Cromossomo* cromossomo) {
    for (size_t i = 0; i < cromossomo->quantidadeDeGenes; ++i) 
        std::cout << cromossomo->genes[i] << " ";
    return os;
}




