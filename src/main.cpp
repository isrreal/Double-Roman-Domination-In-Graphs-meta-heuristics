#include "GeneticAlgorithm.hpp"  
#include "DoubleRomanDomination.hpp"
#include "Graph.hpp"             
#include "AntColonyOptimization.hpp"


int main() {
	Graph graph("graph.txt", false);
    // graph, populationSize, genesSize, generations, numberOfAnts, iterations
    DoubleRomanDomination* drd = new DoubleRomanDomination(graph, 1000, graph.getOrder(), 100, 20, 10); 
    std::cout << "Double Roman Domination Number computed by Genetic Algorithm: " << drd->getGamma2rGeneticAlgorithm() << std::endl;
    std::cout << "Double Roman Domination Number computed by ACO: " << drd->getGamma2rACO() << std::endl;
    delete drd;
	return 0;
}
