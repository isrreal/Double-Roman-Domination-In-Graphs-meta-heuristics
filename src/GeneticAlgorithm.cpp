#include "GeneticAlgorithm.hpp"
 
 /**
 * @brief Retrieves the current population of chromosomes.
 * @return A vector of Chromosomes representing the current population.
 */
 
std::vector<Chromosome> GeneticAlgorithm::getPopulation() { return this->population; }

/**
 * @brief Retrieves the size of the population.
 * @return The size of the population as a size_t.
 */
 
size_t GeneticAlgorithm::getPopulationSize() { return this->populationSize; }

/**
 * @brief Retrieves the number of genes in each chromosome.
 * @return The number of genes as a size_t.
 */
 
size_t GeneticAlgorithm::getGenesSize() { return this->genesSize; }

/**
 * @brief Retrieves the number of generations to run the algorithm.
 * @return The number of generations as a size_t.
 */
 
size_t GeneticAlgorithm::getGenerations() { return this->generations; }

/**
 * @brief Retrieves the graph associated with the genetic algorithm.
 * @return The Graph object used by the algorithm.
 */
 
Graph GeneticAlgorithm::getGraph() { return this->graph; }

/**
 * @brief Retrieves the best solution found by the algorithm.
 * @return A vector of integers representing the best solution.
 */
 
std::vector<int> GeneticAlgorithm::getBestSolution() { return this->bestSolution; } 

/**
 * @brief Creates an initial population of chromosomes.
 * 
 * Initializes chromosomes using a heuristic function, if provided, or with random genes otherwise.
 * 
 * @param generateChromosomeHeuristic A pointer to a function generating chromosomes based on a graph.
 * @param graph The graph used to initialize the chromosomes.
 */

void GeneticAlgorithm::createPopulation(Chromosome(*generateChromosomeHeuristic)(Graph), Graph graph) {
    if (generateChromosomeHeuristic) {  
       Chromosome func = (*generateChromosomeHeuristic)(graph);  
       for (size_t i = 0; i < populationSize; ++i) {
            this->population[i] = Chromosome(func);
            this->population[i].indexRemove = i;
       }
   } 
        
   else {
       for (size_t i = 0; i < populationSize; ++i) {
           this->population[i] = Chromosome(genesSize); 
           this->population[i].indexRemove = i;
       }
   }
}

/**
 * @brief Calculates the fitness score for a chromosome.
 * 
 * Uses a fitness heuristic if provided; otherwise, computes fitness based on gene values.
 * 
 * @param chromosome Reference to the chromosome to evaluate.
 * @param fitnessHeuristic A pointer to a function that calculates fitness.
 * @return The evaluated chromosome with a fitness score.
 */

Chromosome GeneticAlgorithm::fitness(Chromosome& chromosome, Chromosome(*fitnessHeuristic)(Chromosome&) = nullptr) { 
    if (fitnessHeuristic)
        return (*fitnessHeuristic)(chromosome);

    for (size_t i = 0; i < chromosome.genesSize; ++i)
        chromosome.fitnessValue += chromosome.genes[i];
    return chromosome;
}

/**
 * @brief Selects the chromosome from the population using tournament selection.
 * 
 * This method randomly selects two chromosomes from the population, evaluates their fitness, 
 * and choses a random number r between 0 and 1. If r < k (where k is a parameters, for example 0.75),
 * fitter of the two parameters is selected to be a parent; otherwise, the one with the higher fitness value is selected.
 * 
 * @param population The vector of chromosomes in the current population.
 * @return Chromosome The chromosome with the highest or lowest fitness value.
 */

Chromosome GeneticAlgorithm::tournamentSelection(std::vector<Chromosome> population) { 
    constexpr float parameter = 0.75f; 
    std::random_device randomNumber;
    std::mt19937 seed(randomNumber());
    std::uniform_int_distribution<int> gap(0, population.size() - 1);
    std::uniform_real_distribution<float> probability(0, 1); 
    
    
    Chromosome c1 = GeneticAlgorithm::fitness(population[gap(seed)], nullptr);
    Chromosome c2 = GeneticAlgorithm::fitness(population[gap(seed)], nullptr);
   
    if (probability(seed) < parameter) 
       return GeneticAlgorithm::chooseBestSolution(c1, c2);
    else 
       return GeneticAlgorithm::chooseWorstSolution(c1, c2); 
}

/**
 * @brief Selects a chromosome using roulette wheel selection.
 * 
 * Returns a chromosome based on fitness-weighted random selection.
 * 
 * @param population The vector of chromosomes in the population.
 * @return A randomly selected chromosome.
 */

Chromosome GeneticAlgorithm::rouletteWheelSelection(std::vector<Chromosome> population) {
    size_t totalFitness = 0;

    for (size_t i = 0; i < population.size(); ++i) {
        fitness(population[i], nullptr);
        totalFitness += population[i].fitnessValue;
    }

    std::random_device randomNumber;
    std::mt19937 seed(randomNumber());
    std::uniform_int_distribution<> distribution(0, totalFitness - 1);
    size_t randomValue = distribution(seed);

    size_t cumulativeFitness = 0;
    for (auto& chromosome: population) {
        cumulativeFitness += chromosome.fitnessValue;
        if (cumulativeFitness >= randomValue) 
            return chromosome;
    }
    
    return population.back();
}

/**
 * @brief Selects and removes a chromosome based on a heuristic.
 * 
 * Uses the provided heuristic to select and remove a chromosome to prevent duplicates.
 * 
 * @param selectionHeuristic A pointer to a selection function.
 * @return The selected chromosome.
 */

Chromosome GeneticAlgorithm::selectionMethod(Chromosome(*selectionHeuristic)(std::vector<Chromosome>)) {
    if (!selectionHeuristic) 
        return Chromosome(); 
  
    Chromosome selected = (*selectionHeuristic)(this->population);
    
    if (selected.indexRemove >= 0 && selected.indexRemove < this->population.size()) 
    	this->population.erase(this->population.begin() + selected.indexRemove);

    return selected; 
}


/**
 * @brief Chooses the best Chromosome between two options based on their fitness values.
 * 
 * @param chromosome1 constant reference to the first Chromosome.
 * @param chromosome2 constant reference  to the second Chromosome.
 * @return Chromosome The Chromosome with the higher fitness value.
 */

Chromosome GeneticAlgorithm::chooseBestSolution(const Chromosome& chromosome1, const Chromosome& chromosome2) {
	    return (chromosome1.fitnessValue > chromosome2.fitnessValue ? chromosome1 : chromosome2);
}

/**
 * @brief Chooses the worst Chromosome between two options based on their fitness values.
 * 
 * @param chromosome1 constant reference to the first Chromosome.
 * @param chromosome2 constant reference to the second Chromosome.
 * @return Chromosome The Chromosome with the lower fitness value.
 */

Chromosome GeneticAlgorithm::chooseWorstSolution(const Chromosome& chromosome1, const Chromosome& chromosome2) {
	    return (chromosome1.fitnessValue < chromosome2.fitnessValue ? chromosome1 : chromosome2);
}

/**
 * @brief Performs crossover between two chromosomes.
 * 
 * Combines genes from two parents to produce an offspring. Uses a heuristic if provided.
 * 
 * @param chromosome1 The first parent chromosome.
 * @param chromosome2 The second parent chromosome.
 * @param crossOverHeuristic Optional pointer to a crossover function.
 * @return A new chromosome offspring.
 */

Chromosome GeneticAlgorithm::crossOver(Chromosome& chromosome1, Chromosome& chromosome2,
 	Chromosome(*crossOverHeuristic)(Chromosome&, Chromosome&)) {
 	
   if (crossOverHeuristic)
        return (*crossOverHeuristic)(chromosome1, chromosome2);
     
   std::random_device randomNumber;
   std::mt19937 seed(randomNumber()); 
   std::uniform_int_distribution<> gap(0, genesSize - 1);
   size_t range1 = gap(seed);
   size_t range2 = gap(seed);
   
   std::vector<int> x, y;

   if (range1 > range2) 
        std::swap(range1, range2);
    
   for (size_t i = range1; i <= range2; ++i) { 
        x.push_back(chromosome1.genes[i]);
        y.push_back(chromosome2.genes[i]);
   }

   for (size_t i = range1, j = 0; i <= range2; ++i, ++j) {  
       chromosome1.genes[i] = y[j];
       chromosome2.genes[i] = x[j]; 
  }
 
   Chromosome solution1 = chromosome1;
   Chromosome solution2 = chromosome2;

   feasibilityCheck(solution1);
   feasibilityCheck(solution2);
    
   return chooseBestSolution(solution1, solution2);
}


/**
 * @brief Checks and adjusts chromosome feasibility.
 * 
 * Ensures that the chromosome meets Double Roman Domination constraints based on the graph.
 * 
 * @param chromosome The chromosome to check.
 * @return The adjusted chromosome.
 */
 
Chromosome GeneticAlgorithm::feasibilityCheck(Chromosome& chromosome) {	
    bool hasNeighborWith3 = false;                     
                                                                                                                                                            
    for (size_t i = 0; i < genesSize; ++i) {
        if (chromosome.genes[i] == 0) {
            hasNeighborWith3 = false;
            for (auto& neighbor : this->graph.getAdjacencyList(i)) {
                if (chromosome.genes[neighbor] == 3) {
                    hasNeighborWith3 = true;
                    break; 
                }
            }

            if (!hasNeighborWith3) 
                chromosome.genes[i] = 2;
        }
    }

    return chromosome;	
}

/**
 * @brief Creates a new generation of chromosomes by performing crossover operations.
 *
 * This function generates a new population by selecting chromosomes from the current population using 
 * different selection heuristics (tournament and roulette wheel selection), performing crossover 
 * on selected pairs to create offspring, and adding them to the new population. The new population 
 * is intended to be genetically improved over previous generations.
 * 
 * @details This method begins by clearing the existing population. It then repeatedly selects two parent 
 * chromosomes from the current population—one chosen through tournament selection and the other through 
 * roulette wheel selection. A crossover operation is applied to the selected pair to produce a single 
 * offspring, which is then added to the new population vector. The process continues until the new population 
 * reaches the specified population size.
 *
 * @return std::vector<Chromosome>& A reference to the newly created population vector, which now contains 
 * genetically modified offspring chromosomes.
 */

std::vector<Chromosome>& GeneticAlgorithm::createNewPopulation() {
	std::vector<Chromosome> temp;

    while (temp.size() < populationSize) {
        Chromosome selected1 = this->selectionMethod(tournamentSelection);
        Chromosome selected2 = this->selectionMethod(rouletteWheelSelection);
        Chromosome offspring = this->crossOver(selected1, selected2, nullptr);

        temp.push_back(offspring);
    }
    
	this->population.swap(temp);
	
    return population;
}

/**
 * @brief Runs the genetic algorithm for a specified number of generations.
 * 
 * Evolves the population over multiple generations and stores the best solution found.
 * 
 * @param generations Number of generations to evolve.
 * @param heuristic Function pointer for initializing chromosomes from a graph.
 */

void GeneticAlgorithm::run(size_t generations, Chromosome(*heuristic)(Graph)) { 

   this->createPopulation(heuristic, graph);

   Chromosome currentBestSolution = this->tournamentSelection(this->population);                                         
   Chromosome bestSolution = currentBestSolution;

   for (size_t i = 0; i < generations; ++i) {        
       	this->population.swap(this->createNewPopulation());
        currentBestSolution = this->tournamentSelection(this->population);                                       

        if (bestSolution.fitnessValue > currentBestSolution.fitnessValue)
            bestSolution = currentBestSolution; 
   }

    this->bestSolution = bestSolution.genes;
}
