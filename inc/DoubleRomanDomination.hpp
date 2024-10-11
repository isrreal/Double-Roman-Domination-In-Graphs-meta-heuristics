#ifndef DOUBLE_ROMAN_DOMINATION_HPP
#define DOUBLE_ROMAN_DOMINATION_HPP

#include "Graph.hpp"
#include "AlgoritmoGenetico.hpp"
#include "Cromossomo.hpp"
#include <vector>
#include <random>
#include <list>

class DoubleRomanDomination {
	private:
		Graph* graph;
        AlgoritmoGenetico* geneticAlgorithm;
		size_t gamma2r;	
		void fiabilityCheck();
	public:
	DoubleRomanDomination(Graph* graph, size_t tamanhoDaPopulacao, size_t quantidadeDeGenes,
                      float taxaDeMutacao, float taxaDeElitismo) 
    : geneticAlgorithm(new AlgoritmoGenetico(tamanhoDaPopulacao, quantidadeDeGenes, taxaDeMutacao, taxaDeElitismo)),
      graph(graph), gamma2r(0) {}

        ~DoubleRomanDomination();
        Graph* getGraph();
        size_t getGamma2R();
        AlgoritmoGenetico* getGeneticAlgorithm();
	    static Cromossomo* heuristic1(Graph* graph);
	    static Cromossomo* heuristic2(Graph* graph);
        static Cromossomo* heuristic3(Graph* graph);
};
#endif
