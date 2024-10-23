#include "GeneticAlgorithm.hpp"  
#include "DoubleRomanDomination.hpp"
#include "Graph.hpp"             
#include "AntColonyOptimization.hpp"

int main() {
   // order, isDirected, edgeProbability   
    Graph graph(50, false, 0.1);

    // graph, populationSize, genesSize, generations, numberOfAnts, iterations
   	DoubleRomanDomination* drd = new DoubleRomanDomination(graph, 100, graph.getOrder(), 500, 30, 10); 
    std::cout << "Double Roman Domination Number computed by Genetic Algorithm: " << drd->getGamma2rGeneticAlgorithm() << std::endl;
    std::cout << "Double Roman Domination Number computed by ACO: " << drd->getGamma2rACO() << std::endl;

    return 0;
}
