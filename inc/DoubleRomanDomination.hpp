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
		size_t gamma2r;	
		void fiabilityCheck();
	public:
	DoubleRomanDomination(Graph* graph, size_t tamanhoDaPopulacao, size_t quantidadeDeGenes,
                      float taxaDeMutacao, float taxaDeElitismo) 
    : AlgoritmoGenetico(tamanhoDaPopulacao, quantidadeDeGenes, taxaDeMutacao, taxaDeElitismo),
      graph(graph), gamma2r(0) {}

	    Cromossomo* heuristic1();
	    Cromossomo* heuristic2();
        Cromossomo* heuristic3();
        void criarPopulacao(size_t quantidadeDeCromossomos) override;
        // void criarCromossomo(size_t quantidadeDeCromossomos, Graph* graph) override;
        
//        Cromossomo* rodarAG(size_t quantidadeDeGeracoes) override; 

	// std::pair<Cromossomo*, int> fitness(Cromossomo*) override;
};
#endif
