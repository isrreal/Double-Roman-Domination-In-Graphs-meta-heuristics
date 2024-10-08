#ifndef CROMOSSOMO_HPP
#define CROMOSSOMO_HPP

#include <iostream>
#include <random>
#include <vector>

struct Cromossomo {
	size_t quantidadeDeGenes;
    std::vector<int> genes;

	Cromossomo(std::vector<int> genes);

	Cromossomo(size_t quantidadeDeGenes);

	Cromossomo(std::vector<int> primeiraMetade, std::vector<int> segundaMetade);

	~Cromossomo();
};

#endif
