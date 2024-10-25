#include "DoubleRomanDomination.hpp"


/**
 * @brief Destructor for the DoubleRomanDomination class.
 * 
 * Frees the memory allocated for the genetic algorithm and graph objects.
 */
DoubleRomanDomination::~DoubleRomanDomination() {
    delete this->geneticAlgorithm;
    //delete this->ACO;
}

/**
 * @brief Gets the graph used in the double Roman domination algorithm.
 * 
 * @return Graph* Pointer to the graph object.
 */
Graph& DoubleRomanDomination::getGraph() {
    return this->graph;
}

std::vector<int> DoubleRomanDomination::getSolution() {
	return this->solution;
}

size_t DoubleRomanDomination::getGamma2rGeneticAlgorithm() {
    return this->gamma2rGeneticAlgorithm;
}

size_t DoubleRomanDomination::getGamma2rACO() {
    return this->gamma2rACO;
}

/**
 * @brief Runs the genetic algorithm and calculates the double Roman domination number (gamma2R).
 * 
 * Executes the genetic algorithm with predefined heuristics and computes the total sum of genes
 * in the resulting chromosome to calculate gamma2R.
 * 
 * @return size_t The calculated double Roman domination number.
 */
 
void DoubleRomanDomination::runGeneticAlgorithm() {
    this->geneticAlgorithm->run(geneticAlgorithm->getGenerations(), heuristic1);

    solution = this->geneticAlgorithm->getBestSolution();
    std::for_each(solution.begin(), solution.end(), [&](int element) {
        this->gamma2rGeneticAlgorithm += element;
    });
}

void DoubleRomanDomination::runACO() {
   this->ACO->run();
   
   solution = this->ACO->getBestSolution();

   std::for_each(solution.begin(), solution.end(), [&](int element) {
      this->gamma2rACO += element;
   });
}

/**
 * @brief A heuristic function that generates an initial chromosome solution for double Roman domination.
 * 
 * This heuristic randomly selects vertices and assigns them a value of 3, while updating their neighbors 
 * with a value of 0. The adjacency list of the chosen vertex is then deleted.
 * 
 * @param graph Pointer to the graph used to create the chromosome.
 * @return Chromosome* The generated chromosome solution.
 */
Chromosome* DoubleRomanDomination::heuristic1(Graph graph) {
    Chromosome* solution = new Chromosome(graph.getOrder());
    std::random_device randomNumber;
    std::mt19937 seed(randomNumber());
    std::uniform_int_distribution<int> gap(0, graph.getOrder() - 1);
	
    size_t choosenVertex = 0;

    while (graph.getOrder() > 0) {
        choosenVertex = gap(seed);
        while (!graph.vertexExists(choosenVertex))
            choosenVertex = gap(seed);
	    
        solution->genes[choosenVertex] = 3;
        for (const auto& it: graph.getAdjacencyList(choosenVertex)) {
            if (solution->genes[it] == -1)
                solution->genes[it] = 0;
        }

        graph.deleteAdjacencyList(choosenVertex);

        if (graph.getOrder() == 1) {
            choosenVertex = graph.getAdjacencyList().begin()->first;
            solution->genes[choosenVertex] = 3;
            graph.deleteVertex(choosenVertex);
        }
    }

    return solution;    
}

/**
 * @brief A second heuristic function that generates an initial chromosome solution for double Roman domination.
 * 
 * This heuristic selects vertices randomly and assigns them values, updating neighbors accordingly and
 * handling vertices with no neighbors by assigning a value of 2.
 * 
 * @param graph Pointer to the graph used to create the chromosome.
 * @return Chromosome* The generated chromosome solution.
 */
Chromosome* DoubleRomanDomination::heuristic2(Graph graph) {
    Chromosome* solution = new Chromosome(graph.getOrder());
    std::random_device randomNumber;
    std::mt19937 seed(randomNumber());
    std::uniform_int_distribution<int> gap(0, graph.getOrder() - 1);
    
    size_t choosenVertex = 0;
    size_t graphOrder = graph.getOrder();

    while (graph.getOrder() > 0) {
        choosenVertex = gap(seed);
        while (!graph.vertexExists(choosenVertex))
            choosenVertex = gap(seed);

        solution->genes[choosenVertex] = 3;
        for (const auto& it: graph.getAdjacencyList(choosenVertex)) {
            if (solution->genes[it] == -1)
                solution->genes[it] = 0;
        }

        graph.deleteAdjacencyList(choosenVertex);

        for (size_t i = 0; i < graphOrder; ++i) {
            if (graph.vertexExists(i)) {
                if (graph.getVertexDegree(i) == 0) {
                    solution->genes[i] = 2;
                    graph.deleteVertex(i);
                }
            }
        }
    }

    return solution;
}

/**
 * @brief A third heuristic function that generates an initial chromosome solution for double Roman domination.
 * 
 * This heuristic sorts vertices by degree in descending order, then selects vertices with the highest degree
 * for assignment while updating their neighbors.
 * 
 * @param graph Pointer to the graph used to create the chromosome.
 * @return Chromosome* The generated chromosome solution.
 */
Chromosome* DoubleRomanDomination::heuristic3(Graph graph) {
    Chromosome* solution = new Chromosome(graph.getOrder());
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

        solution->genes[sortedVertices[choosenVertex]] = 3;

        for (const auto& it : graph.getAdjacencyList(sortedVertices[choosenVertex])) {
            if (solution->genes[it] == -1)
                solution->genes[it] = 0;
        }

        graph.deleteAdjacencyList(sortedVertices[choosenVertex++]);

        for (size_t i = 0; i < graphOrder; ++i) {
            if (graph.vertexExists(i)) {
                if (graph.getVertexDegree(i) == 0) {
                    solution->genes[i] = 2;
                    graph.deleteVertex(i);
                }
            }
        }
    }

    return solution;
}

