#include "GeneticAlgorithm.hpp"


// Destrutor
GeneticAlgorithm::~GeneticAlgorithm() {
    for (size_t i = populationSize; i > 0; --i)
        delete population[i];
    population.clear();
}

std::vector<Cromossome*> GeneticAlgorithm::getPopulation() { return this->population; }

size_t GeneticAlgorithm::getPopulationSize() { return this->populationSize; }

size_t GeneticAlgorithm::getGenesSize() { return this->genesSize; }

size_t GeneticAlgorithm::getGenerations() { return this->generations; }

//
// A função cria uma população com cromossomes com uma quantidade específica de genes
//

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

// a função recebe um cromossome e atribui sua nota de aptidão
// retorna um par contendo o cromossome e sua nota de aptidão

std::pair<Cromossome*, size_t> GeneticAlgorithm::fitness(Cromossome* cromossome, std::pair<Cromossome*, size_t>(*fitnessHeuristic)(Cromossome*)) {
    if (fitnessHeuristic)
        return (*fitnessHeuristic)(cromossome);

    size_t fitnessValue = 0;
	for (size_t i = 0; i < cromossome->genesSize; ++i)
		fitnessValue += cromossome->genes[i];
	return {cromossome, fitnessValue};
}


/**
 * @brief Seleciona um cromossome da população utilizando uma heurística de seleção específica e o remove da população.
 * 
 * Esta função utiliza uma heurística de seleção passada como argumento para escolher o melhor cromossome da população.
 * Após a seleção, o cromossome é removido da população original para evitar duplicações em futuras seleções.
 * 
 * @param selectionHeuristic Ponteiro para uma função que implementa a heurística de seleção, 
 *                           a qual deve receber um vetor de cromossomes e retornar o cromossome selecionado.
 * @return Cromossome* O cromossome selecionado e removido da população, ou nullptr se não houver seleção válida.
 */

Cromossome* GeneticAlgorithm::selectionMethod(Cromossome*(*selectionHeuristic)(std::vector<Cromossome*>)) {
    if (!selectionHeuristic) 
        return nullptr; 
  
    Cromossome* selected = (*selectionHeuristic)(this->population);
    
    if (!selected) 
        return nullptr; 
    
    if (selected->indexRemove >= 0 && selected->indexRemove < this->population.size()) 
    	this->population.erase(this->population.begin() + selected->indexRemove);

    return selected; 
}


// a função recebe dois cromossomes e seleciona, dentro os dois, o que possui melhor genética
// retorna o cromossome com mais aptidão dentre os comparados

Cromossome* GeneticAlgorithm::chooseBestSolution(Cromossome* cromossome1, Cromossome* cromossome2) {
	    return (this->fitness(cromossome1, nullptr).second > this->fitness(cromossome2, nullptr).second ? cromossome1 : cromossome2);
}


//
// a função realiza o cross over completo de dois cromossomes, e cria um cromossome filho, contendo genes dos cromossomes pais 
// retorna um cromossome filho, contendo o material genético dos cromossomes pai e mãe
//


Cromossome* GeneticAlgorithm::crossOver(Cromossome* cromossome1, Cromossome* cromossome2, Cromossome*(*crossOverHeuristic)(Cromossome*, Cromossome*)) {
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

Cromossome* GeneticAlgorithm::feasibilityCheck(Cromossome* cromossome) {	
	for (auto& gene: cromossome->genes) {
		for (auto& adjacency: cromossome->graph->getAdjacencyList(gene)) {
			if ((gene == 0) &&  (cromossome->genes[adjacency] == 3)) 
				gene = 2;	
		}
	}
	return cromossome;
}

//
// A função simula a reprodução de uma nova população geneticamente superior, sujeitas a mutações e elitismo, usando a população inicial
// retorna uma nova população geneticamente superior
//

std::vector<Cromossome*> GeneticAlgorithm::createNewPopulation(Cromossome*(*selectionMethod1)(std::vector<Cromossome*>),
        Cromossome*(*selectionMethod2)(std::vector<Cromossome*>)) {
    std::vector<Cromossome*> newPopulation = this->population;

    Cromossome* selected1 = nullptr;
    Cromossome* selected2 = nullptr;
    Cromossome* offspring = nullptr;

    while (newPopulation.size() < this->population.size()) {
        selected1 = this->selectionMethod(selectionMethod1);
        selected2 = this->selectionMethod(selectionMethod2);
       
        offspring = this->crossOver(selected1, selected2, nullptr);

        newPopulation.push_back(offspring);
    }

    return newPopulation;
}

// @brief
// A função aplica o algoritmo genético, simulando mutações e elitismo, utilizando uma quantidade específica de gerações
// retorna o melhor indivíduo dentre as gerações
//

Cromossome* GeneticAlgorithm::run(size_t generations,
        Cromossome*(*heuristic)(Graph*), 
        Cromossome*(*selectionHeuristic1)(std::vector<Cromossome*>),
        Cromossome*(*selectionHeuristic2)(std::vector<Cromossome*>),
        Graph* graph) {
        
   this->createPopulation(heuristic, graph);

   Cromossome* bestSolution = nullptr;
   
   for (size_t i = 0; i < generations; ++i) {                                                 
       bestSolution = this->selectionMethod(selectionHeuristic1);
       this->population = this->createNewPopulation(selectionHeuristic1, selectionHeuristic2);	
   }

   return bestSolution;
}
