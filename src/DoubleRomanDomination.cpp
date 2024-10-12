#include "DoubleRomanDomination.hpp"


/**
 * @brief Destructor for the DoubleRomanDomination class.
 * 
 * Frees the memory allocated for the genetic algorithm and graph objects.
 */
DoubleRomanDomination::~DoubleRomanDomination() {
    delete this->geneticAlgorithm;
    delete this->graph;
}

/**
 * @brief Gets the genetic algorithm object used for double Roman domination.
 * 
 * @return GeneticAlgorithm* Pointer to the genetic algorithm object.
 */
GeneticAlgorithm* DoubleRomanDomination::getGeneticAlgorithm() {
    return this->geneticAlgorithm;
}

/**
 * @brief Gets the graph used in the double Roman domination algorithm.
 * 
 * @return Graph* Pointer to the graph object.
 */
Graph* DoubleRomanDomination::getGraph() {
    return this->graph;
}

/**
 * @brief Runs the genetic algorithm and calculates the double Roman domination number (gamma2R).
 * 
 * Executes the genetic algorithm with predefined heuristics and computes the total sum of genes
 * in the resulting chromosome to calculate gamma2R.
 * 
 * @return size_t The calculated double Roman domination number.
 */
 
size_t DoubleRomanDomination::getGamma2R() {
    Cromossome* temp = this->geneticAlgorithm->run(geneticAlgorithm->getGenerations(),  
            DoubleRomanDomination::heuristic1,
            DoubleRomanDomination::fitness,
            DoubleRomanDomination::tournamentSelection,
            DoubleRomanDomination::rouletteWheelSelection,
            this->graph);

    std::for_each(temp->genes.begin(), temp->genes.end(), [&](int element) {
        this->gamma2r += element;
    });

    return this->gamma2r;                                                                                                                             
}

/**
 * @brief A heuristic function that generates an initial chromosome solution for double Roman domination.
 * 
 * This heuristic randomly selects vertices and assigns them a value of 3, while updating their neighbors 
 * with a value of 0. The adjacency list of the chosen vertex is then deleted.
 * 
 * @param graph Pointer to the graph used to create the chromosome.
 * @return Cromossome* The generated chromosome solution.
 */
Cromossome* DoubleRomanDomination::heuristic1(Graph* graph) {
    Cromossome* solution = new Cromossome(graph->getOrder(), graph);
    std::random_device randomNumber;
    std::mt19937 seed(randomNumber());
    std::uniform_int_distribution<int> gap(0, graph->getOrder() - 1);
	
    size_t choosenVertex = 0;

    while (graph->getOrder() > 0) {
        choosenVertex = gap(seed);
        while (!graph->vertexExists(choosenVertex))
            choosenVertex = gap(seed);
	    
        solution->genes[choosenVertex] = 3;
        for (const auto& it: graph->getAdjacencyList(choosenVertex)) {
            if (solution->genes[it] == -1)
                solution->genes[it] = 0;
        }

        graph->deleteAdjacencyList(choosenVertex);

        if (graph->getOrder() == 1) {
            choosenVertex = graph->getAdjacencyList().begin()->first;
            solution->genes[choosenVertex] = 3;
            graph->deleteVertex(choosenVertex);
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
 * @return Cromossome* The generated chromosome solution.
 */
Cromossome* DoubleRomanDomination::heuristic2(Graph* graph) {
    Cromossome* solution = new Cromossome(graph->getOrder(), graph);
    std::random_device randomNumber;
    std::mt19937 seed(randomNumber());
    std::uniform_int_distribution<int> gap(0, graph->getOrder() - 1);
    
    size_t choosenVertex = 0;
    size_t graphOrder = graph->getOrder();

    while (graph->getOrder() > 0) {
        choosenVertex = gap(seed);
        while (!graph->vertexExists(choosenVertex))
            choosenVertex = gap(seed);

        solution->genes[choosenVertex] = 3;
        for (const auto& it: graph->getAdjacencyList(choosenVertex)) {
            if (solution->genes[it] == -1)
                solution->genes[it] = 0;
        }

        graph->deleteAdjacencyList(choosenVertex);

        for (size_t i = 0; i < graphOrder; ++i) {
            if (graph->vertexExists(i)) {
                if (graph->getVertexDegree(i) == 0) {
                    solution->genes[i] = 2;
                    graph->deleteVertex(i);
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
 * @return Cromossome* The generated chromosome solution.
 */
Cromossome* DoubleRomanDomination::heuristic3(Graph* graph) {
    Cromossome* solution = new Cromossome(graph->getOrder(), graph);
    std::vector<size_t> sortedVertices(graph->getOrder());
    size_t graphOrder = graph->getOrder();

    for (size_t i = 0; i < graph->getOrder(); ++i)
        sortedVertices[i] = i;

    std::sort(sortedVertices.begin(), sortedVertices.end(),
        [&](size_t a, size_t b) {
            return graph->getVertexDegree(a) > graph->getVertexDegree(b);
    });

    size_t choosenVertex = 0;

    while ((graph->getOrder() > 0) && (choosenVertex < sortedVertices.size())) {
        if (choosenVertex >= sortedVertices.size()) break;

        while (choosenVertex < sortedVertices.size() && 
                (!graph->vertexExists(sortedVertices[choosenVertex]))) {
            ++choosenVertex;
        }

        if (choosenVertex >= sortedVertices.size()) break;

        solution->genes[sortedVertices[choosenVertex]] = 3;

        for (const auto& it : graph->getAdjacencyList(sortedVertices[choosenVertex])) {
            if (solution->genes[it] == -1)
                solution->genes[it] = 0;
        }

        graph->deleteAdjacencyList(sortedVertices[choosenVertex++]);

        for (size_t i = 0; i < graphOrder; ++i) {
            if (graph->vertexExists(i)) {
                if (graph->getVertexDegree(i) == 0) {
                    solution->genes[i] = 2;
                    graph->deleteVertex(i);
                }
            }
        }
    }

    return solution;
}

/**
 * @brief Calculates the fitness value of a chromosome.
 * 
 * This function sums up the gene values in the chromosome to compute the fitness score.
 * 
 * @param cromossome Pointer to the chromosome whose fitness value is to be calculated.
 * @return Cromossome* The chromosome with its fitness value calculated.
 */
Cromossome* DoubleRomanDomination::fitness(Cromossome* cromossome) {
    for (size_t i = 0; i < cromossome->genesSize; ++i)
        cromossome->fitnessValue += cromossome->genes[i];
    return cromossome;
}

/**
 * @brief Selects the best chromosome from the population using tournament selection.
 * 
 * This method randomly selects chromosomes from the population, evaluates their fitness, 
 * and returns the one with the highest fitness value.
 * 
 * @param population The vector of chromosomes in the current population.
 * @return Cromossome* The chromosome with the highest fitness value.
 */
Cromossome* DoubleRomanDomination::tournamentSelection(std::vector<Cromossome*> population) {
    std::random_device randomNumber;
    std::mt19937 seed(randomNumber());
    std::uniform_int_distribution<int> gap(0, population.size() - 1);
    Cromossome* bestSolution = fitness(population[gap(seed)]);
    Cromossome* temp = nullptr;
    
    for (size_t i = 0; i < population.size(); ++i) {
        temp = fitness(population[i]);
        if (temp->fitnessValue > bestSolution->fitnessValue)
            bestSolution = temp;
    }
    
    return bestSolution;
}

/**
 * @brief Selects a chromosome from the population using roulette wheel selection.
 * 
 * This method randomly selects and returns a chromosome from the population.
 * 
 * @param population The vector of chromosomes in the current population.
 * @return Cromossome* The randomly selected chromosome.
 */
Cromossome* DoubleRomanDomination::rouletteWheelSelection(std::vector<Cromossome*> population) {
    std::random_device randomNumber;
    std::mt19937 seed(randomNumber()); 
    std::uniform_int_distribution<> gap(0, population.size() - 1);
    
    return population[gap(seed)];
}

