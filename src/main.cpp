#include "GeneticAlgorithm.hpp"  
#include "DoubleRomanDomination.hpp"
#include "Graph.hpp"             
#include "AntColonyOptimization.hpp"

int main(int argc, char** argv) {
    if (argc == 3) {
       // order, isDirected, edgeProbability   
        Graph graph(std::stoi(argv[1]), false, std::stof(argv[2]));
        // graph, populationSize, genesSize, generations, numberOfAnts, iterations
        DoubleRomanDomination* drd = new DoubleRomanDomination(graph, 100, graph.getOrder(), 100, 20, 10); 
        std::cout << "Double Roman Domination Number computed by Genetic Algorithm: " << drd->getGamma2rGeneticAlgorithm() << std::endl;
        std::cout << "Double Roman Domination Number computed by ACO: " << drd->getGamma2rACO() << std::endl;
        delete drd;
        return 0;
    }
    else
        return -1;
}
