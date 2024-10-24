#include "GeneticAlgorithm.hpp"  
#include "DoubleRomanDomination.hpp"
#include "Graph.hpp"             
#include "AntColonyOptimization.hpp"
#include <sstream>
#include <fstream>

Graph readGraph(const std::string& filename) {
    std::ifstream file(filename, std::fstream::in);
    
    if (!file) {
        std::cerr << "Error opening the file!" << std::endl;
        throw std::runtime_error("File not found");
    }

    std::string line;
    size_t order = 0, size = 0;
    int source = 0, destination = 0;

    // Lê a primeira linha contendo a ordem e o tamanho do grafo
    std::getline(file, line);
    std::stringstream ss(line);
    ss >> order >> size;

    // Inicializa o grafo com a ordem e define como não-direcionado (ou true se for direcionado)
    Graph graph(order, false, 0.0f); 

    // Lê as arestas do grafo e atualiza a lista de adjacências
    while (std::getline(file, line)) {
        std::stringstream ssEdges(line);
        while (ssEdges >> source >> destination) {
            graph.addEdge(source, destination);
        }
    }

    return graph; 
}

int main(int argc, char** argv) {
    if (argc == 3) {
       // order, isDirected, edgeProbability   
        Graph graph(std::stoi(argv[1]), false, std::stof(argv[2]));
        // graph, populationSize, genesSize, generations, numberOfAnts, iterations
        DoubleRomanDomination* drd = new DoubleRomanDomination(graph, 1000, graph.getOrder(), 100, 20, 10); 
        std::cout << "Double Roman Domination Number computed by Genetic Algorithm: " << drd->getGamma2rGeneticAlgorithm() << std::endl;
        std::cout << "Double Roman Domination Number computed by ACO: " << drd->getGamma2rACO() << std::endl;
        delete drd;
        return 0;
    }
    else
        return -1;
}
