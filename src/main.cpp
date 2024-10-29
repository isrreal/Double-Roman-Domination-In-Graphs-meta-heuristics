#include "GeneticAlgorithm.hpp"  
#include "DoubleRomanDomination.hpp"
#include "Graph.hpp"             
#include "AntColonyOptimization.hpp"


int main(int argc, char** argv) {
    if (argc > 4) {
        Graph graph("graph.txt", false);
        // graph, populationSize, genesSize, generations, numberOfAnts, iterations
        DoubleRomanDomination* drd = new DoubleRomanDomination(graph, std::stoi(argv[1]), graph.getOrder(), std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4])); 
        std::cout << "Double Roman Domination Number computed by Genetic Algorithm: " << drd->getGamma2rGeneticAlgorithm() << std::endl;
        std::cout << "Double Roman Domination Number computed by ACO: " << drd->getGamma2rACO() << std::endl;
        delete drd;
    }

	return 0;
}
