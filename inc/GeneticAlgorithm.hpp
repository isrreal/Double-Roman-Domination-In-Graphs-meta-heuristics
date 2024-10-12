#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#include <iostream>
#include <random>
#include <vector>
#include "Cromossome.hpp"

class GeneticAlgorithm {
	private:
		size_t populationSize;
		size_t genesSize;
		std::vector<Cromossome*> population;
	    size_t generations;	
		void createPopulation(Cromossome*(*heuristic)(Graph*), Graph* graph);
		Cromossome* selectionMethod(Cromossome*(*selectionHeuristic)(std::vector<Cromossome*>));
		Cromossome* chooseBestSolution(Cromossome* cromossome1, Cromossome* cromossome2);
		Cromossome* crossOver(Cromossome* cromossome1, Cromossome* cromossomo2,
                Cromossome*(*crossOverHeuristic)(Cromossome*, Cromossome*)); 
		Cromossome* feasibilityCheck(Cromossome* cromossome);
		std::vector<Cromossome*> createNewPopulation();
	public:
		GeneticAlgorithm(size_t populationSize, size_t genesSize, size_t generations):
        				populationSize(populationSize), genesSize(genesSize),
                        generations(generations), population(populationSize, nullptr) {}
        ~GeneticAlgorithm();
        std::vector<Cromossome*> getPopulation();     
        size_t getPopulationSize();    
        size_t getGenesSize();
        size_t getGenerations();          
		Cromossome* run(size_t generations, 
                Cromossome*(*selectionMethod)(std::vector<Cromossome*>),
                Cromossome*(*heuristic)(Graph*), Graph* graph);
       
        static std::pair<Cromossome*, int> fitness(Cromossome*);
        static Cromossome* tournamentSelection(std::vector<Cromossome*> population);
        static Cromossome* rouletteWheelSelection(std::vector<Cromossome*> population);                                                                                                     
};	

#endif
