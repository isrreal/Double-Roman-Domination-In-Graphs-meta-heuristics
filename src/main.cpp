#include "GeneticAlgorithm.hpp"  
#include "DoubleRomanDomination.hpp"
#include "Graph.hpp"             
#include "AntColonyOptimization.hpp"


int main(int argc, char** argv) {
    if (argc == 4) {
    	if (std::string(argv[1]) == "r") {
		    // order, isDirected, edgeProbability   
		    Graph graph(std::stoi(argv[2]), false, std::stof(argv[3]));
		    // graph, populationSize, genesSize, generations, numberOfAnts, iterations
		    DoubleRomanDomination* drd = new DoubleRomanDomination(graph, 1000, graph.getOrder(), 100, 20, 10); 
		    std::cout << "Double Roman Domination Number computed by Genetic Algorithm: " << drd->getGamma2rGeneticAlgorithm() << std::endl;
		    std::cout << "Double Roman Domination Number computed by ACO: " << drd->getGamma2rACO() << std::endl;
		    delete drd;
       }
       
       else if (std::string(argv[1]) == "f") {
       		// order, isDirected   
		    Graph graph(std::stoi(argv[2]), false, "graph.txt");
		    // graph, populationSize, genesSize, generations, numberOfAnts, iterations
		    DoubleRomanDomination* drd = new DoubleRomanDomination(graph, 1000, graph.getOrder(), 100, 20, 10); 
		    std::cout << "Double Roman Domination Number computed by Genetic Algorithm: " << drd->getGamma2rGeneticAlgorithm() << std::endl;
		    std::cout << "Double Roman Domination Number computed by ACO: " << drd->getGamma2rACO() << std::endl;
		    delete drd;
       }
       
       return 0;
    }
    
    else
        return -1;
}
