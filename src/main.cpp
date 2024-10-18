#include "GeneticAlgorithm.hpp"  
#include "DoubleRomanDomination.hpp"
#include "Graph.hpp"             
#include "AntColonyOptimization.hpp"

int main() {
    Graph graph(10, false, 0.1); 
    AntColonyOptimization aco(graph, 10);
    aco.run(10);

    for (const auto& it: aco.getBestSolution())
        std::cout << it << " ";
    std::cout << std::endl;
    return 0;
}
