#include "GeneticAlgorithm.hpp"  
#include "DoubleRomanDomination.hpp"
#include "Graph.hpp"             
#include "AntColonyOptimization.hpp"


int main(int argc, char** argv) {
    if (argc > 5) {
        Graph graph("graph.txt", false);
        // graph, populationSize, genesSize, generations, heuristic, numberOfAnts, iterations
        DoubleRomanDomination* drd = new DoubleRomanDomination(graph, std::stoi(argv[1]), graph.getOrder(), std::stoi(argv[2]),
                std::stoi(argv[3]),
                std::stoi(argv[4]), std::stoi(argv[5])); 
        std::cout << "Double Roman Domination Number computed by Genetic Algorithm: " << drd->getGamma2rGeneticAlgorithm() << std::endl;
        std::cout << "Double Roman Domination Number computed by ACO: " << drd->getGamma2rACO() << std::endl;

        std::cout << "\nGenetic Algorithm solution: " << std::endl;
        for (const auto& it: drd->getSolutionGeneticAlgorithm())
           std::cout << it << " ";
        std::cout << std::endl;

        std::cout << "\nDouble Roman Domination Function: \n" << std::endl;
        std::cout << "ACO solution: " << std::endl;
        for (const auto& it: drd->getSolutionACO())
           std::cout << it << " ";
        std::cout << std::endl;

        delete drd;
    }

	return 0;
}
