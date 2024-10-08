#ifndef ROMANDOMINATION_HPP
#define ROMANDOMINATION_HPP

#include "Graph.hpp"
#include "AlgoritmoGenetico.hpp"
#include "Cromossomo.hpp"
#include <vector>
#include <random>
#include <list>

class DoubleRomanDomination: public AlgoritmoGenetico {
	private:
		Graph* graph;
		std::vector<std::vector<int>> solutions;
		size_t gamma2r;	
		void fiabilityCheck();
	public:
	DoubleRomanDomination(Graph* graph): graph(graph), gamma2r(0), solutions(),
		AlgoritmoGenetico(tamanhoDaPopulacao, quantidadeDeGenes, taxaDeMutacao, taxaDeElitismo) {}

	    Cromossomo* heuristic1();
	    Cromossomo* heuristic2();
        Cromossomo* heuristic3(); 							
	// std::pair<Cromossomo*, int> fitness(Cromossomo*) override;
};
#endif
