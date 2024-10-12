#include "GeneticAlgorithm.hpp"

/**
 * @brief Destructor of the GeneticAlgorithm class.
 * 
 * Frees the memory allocated for the population of chromosomes and clears the population vector.
 */
 
GeneticAlgorithm::~GeneticAlgorithm() {
    for (size_t i = populationSize; i > 0; --i)
        delete population[i];
    population.clear();
}
 
std::vector<Cromossome*> GeneticAlgorithm::getPopulation() { return this->population; }

size_t GeneticAlgorithm::getPopulationSize() { return this->populationSize; }

size_t GeneticAlgorithm::getGenesSize() { return this->genesSize; }

size_t GeneticAlgorithm::getGenerations() { return this->generations; }

/**
 * @brief Creates a population of chromosomes with a specific number of genes.
 * 
 * If a heuristic function is provided, the chromosomes are initialized using this heuristic.
 * Otherwise, chromosomes are initialized with random genes.
 * 
 * @param heuristic A pointer to a function that generates chromosomes based on a graph.
 * @param graph A pointer to the graph used to initialize the chromosomes.
 */

void GeneticAlgorithm::createPopulation(Cromossome*(*heuristic)(Graph*), Graph* graph) {
    if (heuristic) {  
       Cromossome* func = (*heuristic)(graph);  
       for (size_t i = 0; i < populationSize; ++i) {
            this->population[i] = new Cromossome(func);
            this->population[i]->indexRemove = i;
       }
   } 
        
   else {
       for (size_t i = 0; i < populationSize; ++i) {
           this->population[i] = new Cromossome(genesSize, nullptr); 
           this->population[i]->indexRemove = i;
       }
   }
}

/**
 * @brief Calculates the fitness score for a given chromosome.
 * 
 * If a fitness heuristic is provided, it is used to calculate the fitness score.
 * Otherwise, returns nullptr.
 * 
 * @param cromossome A pointer to the chromosome to evaluate.
 * @param fitnessHeuristic A pointer to a function that evaluates the fitness of the chromosome.
 * @return Cromossome* The chromosome with its fitness score calculated, or nullptr if no heuristic is provided.
 */

Cromossome* GeneticAlgorithm::fitness(Cromossome* cromossome, 
	Cromossome*(*fitnessHeuristic)(Cromossome*) = nullptr) {
    if (fitnessHeuristic)
        return (*fitnessHeuristic)(cromossome);

    else
	return nullptr;
}


/**
 * @brief Selects a chromosome from the population using a specific selection heuristic and removes it.
 * 
 * Uses the provided selection heuristic to select the best chromosome from the population and removes it
 * to prevent duplications in future selections.
 * 
 * @param selectionHeuristic A pointer to a function that implements the selection heuristic.
 * @return Cromossome* The selected chromosome, or nullptr if no valid selection is made.
 */

Cromossome* GeneticAlgorithm::selectionMethod(Cromossome*(*fitnessHeuristic)(Cromossome*), 
	Cromossome*(*selectionHeuristic)(std::vector<Cromossome*>)) {
    if (!selectionHeuristic) 
        return nullptr; 
  
    Cromossome* selected = (*selectionHeuristic)(this->population);
    
    if (!selected) 
        return nullptr; 
    
    if (selected->indexRemove >= 0 && selected->indexRemove < this->population.size()) 
    	this->population.erase(this->population.begin() + selected->indexRemove);

    return selected; 
}


/**
 * @brief Chooses the best Cromossome between two options based on their fitness values.
 * 
 * @param cromossome1 Pointer to the first Cromossome.
 * @param cromossome2 Pointer to the second Cromossome.
 * @return Cromossome* The Cromossome with the higher fitness value.
 */

Cromossome* GeneticAlgorithm::chooseBestSolution(Cromossome* cromossome1, Cromossome* cromossome2) {
	    return (cromossome1->fitnessValue > cromossome2->fitnessValue ? cromossome1 : cromossome2);
}


/**
 * @brief Performs a crossover between two chromosomes to create an offspring.
 * 
 * Combines genes from two parent chromosomes to create a new chromosome with genes 
 * inherited from both parents.
 * 
 * @param cromossome1 Pointer to the first parent chromosome.
 * @param cromossome2 Pointer to the second parent chromosome.
 * @param crossOverHeuristic Optional pointer to a function that performs the crossover.
 * @return Cromossome* A new chromosome offspring.
 */


Cromossome* GeneticAlgorithm::crossOver(Cromossome* cromossome1, Cromossome* cromossome2,
 	Cromossome*(*crossOverHeuristic)(Cromossome*, Cromossome*)) {
 	
   if (crossOverHeuristic)
        return (*crossOverHeuristic)(cromossome1, cromossome2);
     
   std::random_device randomNumber;
   std::mt19937 seed(randomNumber()); 
   std::uniform_int_distribution<> gap(0, genesSize - 1);
   size_t range1 = gap(seed);
   size_t range2 = gap(seed);
   
   std::vector<int> x, y;

   while ((range1 == range2) || ((range2 - range1) == 1)) {
        range1 = gap(seed);
        range2 = gap(seed);
   }

   if (range1 > range2) 
        std::swap(range1, range2);
    
   for (size_t i = range1; i <= range2; ++i) { 
        x.push_back(cromossome1->genes[i]);
        y.push_back(cromossome2->genes[i]);
   }

   for (size_t i = range1, j = 0; i <= range2; ++i, ++j) {  
       cromossome1->genes[i] = y[j];
       cromossome2->genes[i] = x[j]; 
  }
 
   Cromossome* solution1 = new Cromossome(cromossome1);
   Cromossome* solution2 = new Cromossome(cromossome2);

   feasibilityCheck(solution1);
   feasibilityCheck(solution2);
    
   return chooseBestSolution(solution1, solution2);
}


/**
 * @brief Checks the feasibility of a chromosome.
 * 
 * Adjusts genes based on the adjacency list of the graph, ensuring that constraints of Double Roman Domination are met.
 * 
 * @param cromossome A pointer to the chromosome to be checked.
 * @return Cromossome* The adjusted chromosome.
 */
 
 
Cromossome* GeneticAlgorithm::feasibilityCheck(Cromossome* cromossome) {	
	for (auto& gene: cromossome->genes) {
		for (auto& adjacency: cromossome->graph->getAdjacencyList(gene)) {
			if ((gene == 0) &&  (cromossome->genes[adjacency] == 3)) 
				gene = 2;	
		}
	}
	return cromossome;
}

/**
 * @brief Generates a new population by crossing over Cromossomes from the current population.
 * 
 *  Produces a new genetically superior population.
 * 
 * @param selectionMethod1 Pointer to the first selection heuristic.
 * @param selectionMethod2 Pointer to the second selection heuristic.
 * @return std::vector<Cromossome*> A new population of Cromossomes.
 */

std::vector<Cromossome*> GeneticAlgorithm::createNewPopulation(Cromossome*(*fitnessHeuristic)(Cromossome*), 
	Cromossome*(*selectionMethod1)(std::vector<Cromossome*>),
        Cromossome*(*selectionMethod2)(std::vector<Cromossome*>)) {
        
    std::vector<Cromossome*> newPopulation = this->population;

    Cromossome* selected1 = nullptr;
    Cromossome* selected2 = nullptr;
    Cromossome* offspring = nullptr;

    while (newPopulation.size() < this->population.size()) {
        selected1 = this->selectionMethod(fitnessHeuristic, selectionMethod1);
        selected2 = this->selectionMethod(fitnessHeuristic, selectionMethod2);
       
        offspring = this->crossOver(selected1, selected2, nullptr);

        newPopulation.push_back(offspring);
    }

    return newPopulation;
}

/**
 * @brief Runs the genetic algorithm for a specified number of generations.
 * 
 * @param generations Number of generations to evolve.
 * @param heuristic Pointer to a function that generates initial Cromossomes from a graph.
 * @param selectionHeuristic1 Pointer to the first selection heuristic.
 * @param selectionHeuristic2 Pointer to the second selection heuristic.
 * @param graph Pointer to the graph used to generate initial solutions.
 * @return Cromossome* The best solution found after all generations.
 */

Cromossome* GeneticAlgorithm::run(size_t generations,
        Cromossome*(*heuristic)(Graph*),
        Cromossome*(*fitnessHeuristic)(Cromossome*), 
        Cromossome*(*selectionHeuristic1)(std::vector<Cromossome*>),
        Cromossome*(*selectionHeuristic2)(std::vector<Cromossome*>),
        Graph* graph) {
        
   this->createPopulation(heuristic, graph);

   Cromossome* bestSolution = nullptr;
   
   for (size_t i = 0; i < generations; ++i) {                                                 
       bestSolution = this->selectionMethod(fitnessHeuristic, selectionHeuristic1);
       this->population = this->createNewPopulation(fitnessHeuristic, selectionHeuristic1, selectionHeuristic2);	
   }

   return bestSolution;
}
