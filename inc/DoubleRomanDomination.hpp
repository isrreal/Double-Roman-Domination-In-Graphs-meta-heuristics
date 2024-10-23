#ifndef DOUBLE_ROMAN_DOMINATION_HPP
#define DOUBLE_ROMAN_DOMINATION_HPP

#include "Graph.hpp"
#include "GeneticAlgorithm.hpp"
#include "Chromosome.hpp"
#include "AntColonyOptimization.hpp"
#include <vector>
#include <random>

class DoubleRomanDomination {
	private:
		Graph graph;
    	GeneticAlgorithm* geneticAlgorithm;
    	AntColonyOptimization* ACO;
		std::vector<int> solution;
        size_t gamma2rGeneticAlgorithm;		
        size_t gamma2rACO;        
	public:
		DoubleRomanDomination(Graph& graph, size_t populationSize, size_t genesSize, size_t generations,
                size_t numberOfAnts, size_t iterations) 
    			: graph(graph), gamma2rGeneticAlgorithm(0), gamma2rACO(0),   
                geneticAlgorithm(new GeneticAlgorithm(graph, populationSize, genesSize, generations)),
    		    ACO(new AntColonyOptimization(graph, iterations, numberOfAnts)) {
                    this->runGeneticAlgorithm();                    
                    this->runACO();
                }

        ~DoubleRomanDomination();
        Graph& getGraph();
        std::vector<int> getSolution();
        void runGeneticAlgorithm();
        void runACO();
        
        size_t getGamma2rGeneticAlgorithm();
        size_t getGamma2rACO();

        static Chromosome* heuristic1(Graph graph);
        static Chromosome* heuristic2(Graph graph);
        static Chromosome* heuristic3(Graph graph);   
};
#endif
