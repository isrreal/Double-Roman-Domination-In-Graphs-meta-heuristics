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
 
std::vector<Chromosome*> GeneticAlgorithm::getPopulation() { return this->population; }

size_t GeneticAlgorithm::getPopulationSize() { return this->populationSize; }

size_t GeneticAlgorithm::getGenesSize() { return this->genesSize; }

size_t GeneticAlgorithm::getGenerations() { return this->generations; }

Graph GeneticAlgorithm::getGraph() { return this->graph; }

std::vector<int> GeneticAlgorithm::getBestSolution() { return this->bestSolution; } 
/**
 * @brief Creates a population of chromosomes with a specific number of genes.
 * 
 * If a heuristic function is provided, the chromosomes are initialized using this heuristic.
 * Otherwise, chromosomes are initialized with random genes.
 * 
 * @param heuristic A pointer to a function that generates chromosomes based on a graph.
 * @param graph A pointer to the graph used to initialize the chromosomes.
 */

void GeneticAlgorithm::createPopulation(Chromosome*(*generateChromosomeHeuristic)(Graph), Graph graph) {
    if (generateChromosomeHeuristic) {  
       Chromosome* func = (*generateChromosomeHeuristic)(graph);  
       for (size_t i = 0; i < populationSize; ++i) {
            this->population[i] = new Chromosome(func);
            this->population[i]->indexRemove = i;
       }
   } 
        
   else {
       for (size_t i = 0; i < populationSize; ++i) {
           this->population[i] = new Chromosome(genesSize); 
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
 * @param chromosome A pointer to the chromosome to evaluate.
 * @param fitnessHeuristic A pointer to a function that evaluates the fitness of the chromosome.
 * @return Chromosome* The chromosome with its fitness score calculated, or nullptr if no heuristic is provided.
 */

Chromosome* GeneticAlgorithm::fitness(Chromosome* chromosome, Chromosome*(*fitnessHeuristic)(Chromosome*) = nullptr) { 
    if (fitnessHeuristic)
        return (*fitnessHeuristic)(chromosome);

    for (size_t i = 0; i < chromosome->genesSize; ++i)
        chromosome->fitnessValue += chromosome->genes[i];
    return chromosome;
}

/**
 * @brief Selects the best chromosome from the population using tournament selection.
 * 
 * This method randomly selects chromosomes from the population, evaluates their fitness, 
 * and returns the one with the highest fitness value.
 * 
 * @param population The vector of chromosomes in the current population.
 * @return Chromosome* The chromosome with the highest fitness value.
 */

Chromosome* GeneticAlgorithm::tournamentSelection(std::vector<Chromosome*> population) { 
    std::random_device randomNumber;
    std::mt19937 seed(randomNumber());
    std::uniform_int_distribution<int> gap(0, population.size() - 1);
    Chromosome* bestSolution = GeneticAlgorithm::fitness(population[gap(seed)], nullptr);
    Chromosome* temp = nullptr;
    
    for (size_t i = 0; i < population.size(); ++i) {
        temp = GeneticAlgorithm::fitness(population[i], nullptr);
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
 * @return Chromosome* The randomly selected chromosome.
 */

Chromosome* GeneticAlgorithm::rouletteWheelSelection(std::vector<Chromosome*> population) {
    size_t totalFitness = 0;

    for (size_t i = 0; i < population.size(); ++i) {
        fitness(population[i], nullptr);
        totalFitness += population[i]->fitnessValue;
    }

    std::random_device randomNumber;
    std::mt19937 seed(randomNumber());
    std::uniform_int_distribution<> distribution(0, totalFitness - 1);
    size_t randomValue = distribution(seed);

    size_t cumulativeFitness = 0;
    for (auto& chromosome: population) {
        cumulativeFitness += chromosome->fitnessValue;
        if (cumulativeFitness >= randomValue) 
            return chromosome;
    }
    
    return population.back();
}



/**
 * @brief Selects a chromosome from the population using a specific selection heuristic and removes it.
 * 
 * Uses the provided selection heuristic to select the best chromosome from the population and removes it
 * to prevent duplications in future selections.
 * 
 * @param selectionHeuristic A pointer to a function that implements the selection heuristic.
 * @return Chromosome* The selected chromosome, or nullptr if no valid selection is made.
 */

Chromosome* GeneticAlgorithm::selectionMethod(Chromosome*(*selectionHeuristic)(std::vector<Chromosome*>)) {
    if (!selectionHeuristic) 
        return nullptr; 
  
    Chromosome* selected = (*selectionHeuristic)(this->population);
    
    if (!selected) 
        return nullptr; 
    
    if (selected->indexRemove >= 0 && selected->indexRemove < this->population.size()) 
    	this->population.erase(this->population.begin() + selected->indexRemove);

    return selected; 
}


/**
 * @brief Chooses the best Chromosome between two options based on their fitness values.
 * 
 * @param chromosome1 Pointer to the first Chromosome.
 * @param chromosome2 Pointer to the second Chromosome.
 * @return Chromosome* The Chromosome with the higher fitness value.
 */

Chromosome* GeneticAlgorithm::chooseBestSolution(Chromosome* chromosome1, Chromosome* chromosome2) {
	    return (chromosome1->fitnessValue > chromosome2->fitnessValue ? chromosome1 : chromosome2);
}


/**
 * @brief Performs a crossover between two chromosomes to create an offspring.
 * 
 * Combines genes from two parent chromosomes to create a new chromosome with genes 
 * inherited from both parents.
 * 
 * @param chromosome1 Pointer to the first parent chromosome.
 * @param chromosome2 Pointer to the second parent chromosome.
 * @param crossOverHeuristic Optional pointer to a function that performs the crossover.
 * @return Chromosome* A new chromosome offspring.
 */


Chromosome* GeneticAlgorithm::crossOver(Chromosome* chromosome1, Chromosome* chromosome2,
 	Chromosome*(*crossOverHeuristic)(Chromosome*, Chromosome*)) {
 	
   if (crossOverHeuristic)
        return (*crossOverHeuristic)(chromosome1, chromosome2);
     
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
        x.push_back(chromosome1->genes[i]);
        y.push_back(chromosome2->genes[i]);
   }

   for (size_t i = range1, j = 0; i <= range2; ++i, ++j) {  
       chromosome1->genes[i] = y[j];
       chromosome2->genes[i] = x[j]; 
  }
 
   Chromosome* solution1 = new Chromosome(chromosome1);
   Chromosome* solution2 = new Chromosome(chromosome2);

   feasibilityCheck(solution1);
   feasibilityCheck(solution2);
    
   return chooseBestSolution(solution1, solution2);
}


/**
 * @brief Checks the feasibility of a chromosome.
 * 
 * Adjusts genes based on the adjacency list of the graph, ensuring that constraints of Double Roman Domination are met.
 * 
 * @param chromosome A pointer to the chromosome to be checked.
 * @return Chromosome* The adjusted chromosome.
 */
 
 
Chromosome* GeneticAlgorithm::feasibilityCheck(Chromosome* chromosome) {	
	for (auto& gene: chromosome->genes) {
		for (auto& adjacency: graph.getAdjacencyList(gene)) {
			if ((gene == 0) &&  (chromosome->genes[adjacency] == 3)) 
				gene = 2;	
		}
	}
	return chromosome;
}

/**
 * @brief Generates a new population by crossing over Chromosomes from the current population.
 * 
 *  Produces a new genetically superior population.
 * 
 * @return std::vector<Chromosome*> A new population of Chromosomes.
 */

std::vector<Chromosome*> GeneticAlgorithm::createNewPopulation() {
    std::vector<Chromosome*> newPopulation;
    Chromosome* selected1 = nullptr;
    Chromosome* selected2 = nullptr;
    Chromosome* offspring = nullptr;

    while (newPopulation.size() < this->populationSize) {
        selected1 = this->selectionMethod(tournamentSelection);
        selected2 = this->selectionMethod(rouletteWheelSelection);
       
        offspring = this->crossOver(selected1, selected2, nullptr);

        newPopulation.push_back(offspring);
    }

    return newPopulation;
}

/**
 * @brief Runs the genetic algorithm for a specified number of generations.
 * 
 * @param generations Number of generations to evolve.
 * @param heuristic Pointer to a function that generates initial Chromosomes from a graph.
 * @param graph Pointer to the graph used to generate initial solutions.
 * @return Chromosome* The best solution found after all generations.
 */

void GeneticAlgorithm::run(size_t generations, Chromosome*(*heuristic)(Graph)) { 

   this->createPopulation(heuristic, graph);
   Chromosome* currentBestSolution = this->tournamentSelection(this->population);                                         
   Chromosome* bestSolution = currentBestSolution;

   for (size_t i = 0; i < generations; ++i) {        
       	this->population = this->createNewPopulation();
        currentBestSolution = this->tournamentSelection(this->population);                                       

        if (bestSolution->fitnessValue > currentBestSolution->fitnessValue)
            bestSolution = currentBestSolution; 
   }
    this->bestSolution = bestSolution->genes;
}
