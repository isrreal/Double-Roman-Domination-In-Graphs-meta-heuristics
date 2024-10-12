#ifndef DOUBLE_ROMAN_DOMINATION_HPP
#define DOUBLE_ROMAN_DOMINATION_HPP

#include "Graph.hpp"
#include "GeneticAlgorithm.hpp"
#include "Cromossome.hpp"
#include <vector>
#include <random>
#include <list>

class DoubleRomanDomination {
	private:
		Graph* graph;
        GeneticAlgorithm* geneticAlgorithm;
		size_t gamma2r;	
		void fiabilityCheck();
	public:
	DoubleRomanDomination(Graph* graph, size_t populationSize, size_t genesSize, size_t generations) 
    : geneticAlgorithm(new GeneticAlgorithm(populationSize, genesSize, generations)),
      graph(graph), gamma2r(0) {}

        ~DoubleRomanDomination();
        Graph* getGraph();
        size_t getGamma2R();
        GeneticAlgorithm* getGeneticAlgorithm();
	    static Cromossome* heuristic1(Graph* graph);
	    static Cromossome* heuristic2(Graph* graph);
        static Cromossome* heuristic3(Graph* graph);
};
#endif
