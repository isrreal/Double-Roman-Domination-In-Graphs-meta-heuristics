#include "DoubleRomanDomination.hpp"


/**
 * @brief Destructor for the DoubleRomanDomination class.
 * 
 * Frees the memory allocated for the genetic algorithm and graph objects.
 */
 
DoubleRomanDomination::~DoubleRomanDomination() {
    delete this->geneticAlgorithm;
    delete this->ACO;
}

/**
 * @brief Gets the graph used in the double Roman domination algorithm.
 * 
 * @return Graph& Reference to the graph object.
 */
 
Graph& DoubleRomanDomination::getGraph() {
    return this->graph;
}

/**
 * @brief Retrieves the solution obtained from the ACO algorithm.
 * 
 * @return std::vector<int> The solution vector from ACO.
 */
 
std::vector<int> DoubleRomanDomination::getSolutionACO() {
	return this->solutionACO;
}

/**
 * @brief Retrieves the solution obtained from the genetic algorithm.
 * 
 * @return std::vector<int> The solution vector from the genetic algorithm.
 */
 
std::vector<int> DoubleRomanDomination::getSolutionGeneticAlgorithm() {
	return this->solutionGeneticAlgorithm;
}

/**
 * @brief Retrieves the double Roman domination number calculated by the genetic algorithm.
 * 
 * @return size_t The calculated gamma2R value.
 */
 
size_t DoubleRomanDomination::getGamma2rGeneticAlgorithm() {
    return this->gamma2rGeneticAlgorithm;
}

/**
 * @brief Retrieves the double Roman domination number calculated by the ACO algorithm.
 * 
 * @return size_t The calculated gamma2R value.
 */
 
size_t DoubleRomanDomination::getGamma2rACO() {
    return this->gamma2rACO;
}

/**
 * @brief Runs the genetic algorithm to compute the double Roman domination number (gamma2R).
 * 
 * Executes the genetic algorithm using a specified heuristic function and computes the sum of genes 
 * in the best chromosome solution, storing it as gamma2R.
 * 
 * @param heuristic The heuristic identifier (1, 2, or 3) to select the appropriate heuristic function.
 */
 
void DoubleRomanDomination::runGeneticAlgorithm(uint8_t heuristic) {                                                                                                                                           
    auto selectedHeuristic = (heuristic == 2) ? heuristic2 : (heuristic == 3) ? heuristic3 : heuristic1;
    this->geneticAlgorithm->run(geneticAlgorithm->getGenerations(), selectedHeuristic);

    solutionGeneticAlgorithm = this->geneticAlgorithm->getBestSolution();
    std::for_each(solutionGeneticAlgorithm.begin(), solutionGeneticAlgorithm.end(), [&](int element) {
        this->gamma2rGeneticAlgorithm += element;
    });
}


/**
 * @brief Runs the ACO algorithm to compute the double Roman domination number (gamma2R).
 * 
 * Executes the ACO algorithm and computes the sum of genes in the best solution, storing it as gamma2R.
 */
 
void DoubleRomanDomination::runACO() {
   this->ACO->run();
   
   solutionACO = this->ACO->getBestSolution();

   std::for_each(solutionACO.begin(), solutionACO.end(), [&](int element) {
      this->gamma2rACO += element;
   });
}

/**
 * @brief Generates an initial chromosome solution for double Roman domination using heuristic 1.
 * 
 * This heuristic randomly selects vertices, assigning each selected vertex a value of 3, and sets 
 * neighbors' values to 0. The adjacency list of each selected vertex is then deleted.
 * 
 * @param graph Graph object used to create the chromosome.
 * @return Chromosome The generated chromosome solution.
 */
 
Chromosome DoubleRomanDomination::heuristic1(Graph graph) {
    Chromosome solution(Chromosome(graph.getOrder()));
    std::random_device randomNumber;
    std::mt19937 seed(randomNumber());
    std::uniform_int_distribution<int> gap(0, graph.getOrder() - 1);
	
    size_t choosenVertex = 0;

    while (graph.getOrder() > 0) {
        choosenVertex = gap(seed);
        while (!graph.vertexExists(choosenVertex))
            choosenVertex = gap(seed);
	    
        solution.genes[choosenVertex] = 3;
        for (const auto& it: graph.getAdjacencyList(choosenVertex)) {
            if (solution.genes[it] == -1)
                solution.genes[it] = 0;
        }

        graph.deleteAdjacencyList(choosenVertex);

        if (graph.getOrder() == 1) {
            choosenVertex = graph.getAdjacencyList().begin()->first;
            solution.genes[choosenVertex] = 3;
            graph.deleteVertex(choosenVertex);
        }
    }

    return solution;    
}

/**
 * @brief Generates an initial chromosome solution for double Roman domination using heuristic 2.
 * 
 * This heuristic randomly selects vertices, assigns values based on vertex connectivity, and handles 
 * isolated vertices by assigning a value of 2.
 * 
 * @param graph Graph object used to create the chromosome.
 * @return Chromosome The generated chromosome solution.
 */
 
Chromosome DoubleRomanDomination::heuristic2(Graph graph) {
    Chromosome solution(Chromosome(graph.getOrder()));
    std::random_device randomNumber;
    std::mt19937 seed(randomNumber());
    std::uniform_int_distribution<int> gap(0, graph.getOrder() - 1);
    
    size_t choosenVertex = 0;
    size_t graphOrder = graph.getOrder();

    while (graph.getOrder() > 0) {
        choosenVertex = gap(seed);
        while (!graph.vertexExists(choosenVertex))
            choosenVertex = gap(seed);

        solution.genes[choosenVertex] = 3;
        for (const auto& it: graph.getAdjacencyList(choosenVertex)) {
            if (solution.genes[it] == -1)
                solution.genes[it] = 0;
        }

        graph.deleteAdjacencyList(choosenVertex);

        for (size_t i = 0; i < graphOrder; ++i) {
            if (graph.vertexExists(i)) {
                if (graph.getVertexDegree(i) == 0) {
                    solution.genes[i] = 2;
                    graph.deleteVertex(i);
                }
            }
        }
    }

    return solution;
}

/**
 * @brief Generates an initial chromosome solution for double Roman domination using heuristic 3.
 * 
 * This heuristic sorts vertices by degree in descending order, selects the highest degree vertices, 
 * and assigns values while updating their neighbors.
 * 
 * @param graph Graph object used to create the chromosome.
 * @return Chromosome The generated chromosome solution.
 */
 
Chromosome DoubleRomanDomination::heuristic3(Graph graph) {
    Chromosome solution(Chromosome(graph.getOrder()));
    std::vector<size_t> sortedVertices(graph.getOrder());
    size_t graphOrder = graph.getOrder();

    for (size_t i = 0; i < graph.getOrder(); ++i)
        sortedVertices[i] = i;

    std::sort(sortedVertices.begin(), sortedVertices.end(),
        [&](size_t a, size_t b) {
            return graph.getVertexDegree(a) > graph.getVertexDegree(b);
    });

    size_t choosenVertex = 0;

    while ((graph.getOrder() > 0) && (choosenVertex < sortedVertices.size())) {
        if (choosenVertex >= sortedVertices.size()) break;

        while (choosenVertex < sortedVertices.size() && 
                (!graph.vertexExists(sortedVertices[choosenVertex]))) {
            ++choosenVertex;
        }

        if (choosenVertex >= sortedVertices.size()) break;

        solution.genes[sortedVertices[choosenVertex]] = 3;

        for (const auto& it : graph.getAdjacencyList(sortedVertices[choosenVertex])) {
            if (solution.genes[it] == -1)
                solution.genes[it] = 0;
        }

        graph.deleteAdjacencyList(sortedVertices[choosenVertex++]);

        for (size_t i = 0; i < graphOrder; ++i) {
            if (graph.vertexExists(i)) {
                if (graph.getVertexDegree(i) == 0) {
                    solution.genes[i] = 2;
                    graph.deleteVertex(i);
                }
            }
        }
    }

    return solution;
}

