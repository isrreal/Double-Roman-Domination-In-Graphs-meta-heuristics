#include "AlgoritmoGenetico.hpp"


// Destrutor
AlgoritmoGenetico::~AlgoritmoGenetico() {
    for (size_t i = tamanhoDaPopulacao; i > 0; --i)
        delete populacao[i];
    populacao.clear();
}


//
// retorna um novo cromossomo com a quantidade de genes especificada
//

Cromossomo* AlgoritmoGenetico::criarCromossomo(size_t quantidadeDeGenes) {
	return new Cromossomo(quantidadeDeGenes, nullptr);
}

//
// A função cria uma população com cromossomos com uma quantidade específica de genes
//

void AlgoritmoGenetico::criarPopulacao(Cromossomo*(*heuristic)(Graph*), Graph* graph) {
    if (heuristic) {  
       Cromossomo* func = (*heuristic)(graph);  
       for (size_t i = 0; i < tamanhoDaPopulacao; ++i)
            this->populacao[i] = new Cromossomo(func);
   } 
        
   else {
       for (size_t i = 0; i < tamanhoDaPopulacao; ++i)
           this->populacao[i] = criarCromossomo(quantidadeDeGenes);  
   }
}

// 
// A função separa os genes do cromossomo em subgrupos de cadeias com o tamanho especificado
// retorna um vetor de strings contendo os valores dos subgrupos  
//

std::vector<std::string> AlgoritmoGenetico::leituraDeValores(Cromossomo* cromossomo, size_t tamanhoDaCadeia) {
	std::string valor = "";
	std::vector<std::string> subgrupos;

	for (size_t i = 1; i < cromossomo->quantidadeDeGenes + 1; ++i) {
		valor += cromossomo->genes[i - 1];
		if (i % tamanhoDaCadeia == 0) {
			subgrupos.push_back(valor);
			valor = "";
		}
	}

	return subgrupos;
}

//
// A função converte os valores binarios dos genes em decimais
// retorna um vetor contendo os valores em decimal dos binarios de entrada
//

std::vector<std::string> AlgoritmoGenetico::binarioParaDecimal(std::vector<std::string> binarios) {
	std::vector<std::string> decimais;

	for (auto it: binarios) 
		decimais.push_back(binarioParaDecimal(it));

	return decimais;
}

//
// retorna a conversão em decimal do binário de entrada  
//

std::string AlgoritmoGenetico::binarioParaDecimal(std::string binario) {
	std::string decimais = "";
	int valor = 0;
	for (size_t i = 0, j = binario.size() - 1; i < binario.size(); ++i, --j) 
		valor += (binario.data()[i] == '1' ? 1 : 0) * std::pow(2, j);
	return std::to_string(valor);
}

// a função recebe um cromossomo e atribui sua nota de aptidão
// retorna um par contendo o cromossomo e sua nota de aptidão

std::pair<Cromossomo*, int> AlgoritmoGenetico::fitness(Cromossomo* cromossomo) {
	size_t fitnessValue = 0;
	for (size_t i = 0; i < cromossomo->quantidadeDeGenes; ++i)
		fitnessValue += cromossomo->genes[i];
	return {cromossomo, fitnessValue};
}

// a função recebe dois cromossomos e seleciona, dentro os dois, o que possui melhor genética
// retorna o cromossomo com mais aptidão dentre os comparados

Cromossomo* AlgoritmoGenetico::selecionarMelhorIndividuo(Cromossomo* cromossomo1, Cromossomo* cromossomo2) {
	return (this->fitness(cromossomo1).second > this->fitness(cromossomo2).second ? cromossomo1 : cromossomo2);
}

//
// a função realiza o cross over completo de dois cromossomos, e cria um cromossomo filho, contendo genes dos cromossomos pais 
// retorna um cromossomo filho, contendo o material genético dos cromossomos pai e mãe
//


Cromossomo* AlgoritmoGenetico::crossOver(Cromossomo* pai, Cromossomo* mae, Cromossomo*(*crossOverHeuristic)(Cromossomo*, Cromossomo*)) {
    if (crossOverHeuristic)
        return (*crossOverHeuristic)(pai, mae);
     
   std::random_device randomNumber;
   std::mt19937 seed(randomNumber()); 
   std::uniform_int_distribution<> gap(0, quantidadeDeGenes - 1);
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
        x.push_back(pai->genes[i]);
        y.push_back(mae->genes[i]);
   }

   for (size_t i = range1, j = 0; i <= range2; ++i, ++j) {  
       pai->genes[i] = y[j];
       mae->genes[i] = x[j]; 
  }
 
   Cromossomo* s1 = new Cromossomo(pai);
   Cromossomo* s2 = new Cromossomo(mae);

   feasibilityCheck(s1);
   feasibilityCheck(s2);
    
   return selecionarMelhorIndividuo(s1, s2);
}

Cromossomo* AlgoritmoGenetico::feasibilityCheck(Cromossomo* cromossomo) {	
	for (auto& gene: cromossomo->genes) {
		for (auto& adjacency: cromossomo->graph->getAdjacencyList(gene)) {
			if ((gene == 0) &&  (cromossomo->genes[adjacency] == 3)) 
				gene = 2;	
		}
	}
	return cromossomo;
}


//
// essa função simula a mutação de genética do cromossomo, alterando seus genes baseados na taxa de mutação
// retorna um novo cromossomo sujeito a mutação genética
//

Cromossomo* AlgoritmoGenetico::mutacao(Cromossomo* cromossomo) {
    std::vector<int> cromossomoMutado = cromossomo->genes;                                                 
    
    std::random_device randomNumber;
    std::mt19937 seed(randomNumber()); 
    std::uniform_real_distribution<> gap(0, 3);
    
    uint8_t sorteio = 0;
    
    for (size_t i = 0; i < cromossomoMutado.size(); ++i) {
        sorteio = gap(seed); 
        
        if (sorteio <= this->taxaDeMutacao) { 
            cromossomoMutado[i] = (cromossomoMutado[i] == 0) ? 1 : 0;
            cromossomoMutado[i] = (cromossomoMutado[i] == 1) ? 2 : 1;
            cromossomoMutado[i] = (cromossomoMutado[i] == 2) ? 3 : 2;
            cromossomoMutado[i] = (cromossomoMutado[i] == 3) ? 2 : 1;
        }
    }

    return new Cromossomo(cromossomoMutado, cromossomo->graph);
}

//
// A função simula a identificação de um cromossomo geneticamente superior aos demais da população, baseado na taxa de elitismo
// retorna uma nova população contendo os genes do cromossomo geneticamente superior 
//
 
std::vector<Cromossomo*> AlgoritmoGenetico::elitismo() {
	std::vector<Cromossomo*> novaPopulacao;
	Cromossomo* melhorIndividuo = this->obterMelhorIndividuo();
	size_t numeroDeRepeticoes = this->populacao.size() * this->taxaDeElitismo;

	for (size_t i = 0; i < numeroDeRepeticoes; ++i)
		novaPopulacao.push_back(melhorIndividuo);
	
	return novaPopulacao;
}

//
// A função escolhe aleatoriamente os cromossomos da população inicial e testa a aptidão de cada um 
// retorna o cromossomo geneticamente superior 
//

Cromossomo* AlgoritmoGenetico::obterMelhorIndividuo() {
	std::random_device randomNumber;
	std::mt19937 seed(randomNumber());
	std::uniform_int_distribution<int> gap(0, this->populacao.size() - 1);
	std::pair<Cromossomo*, int> melhorIndividuo = this->fitness(this->populacao[gap(seed)]);
	std::pair<Cromossomo*, int> individuo;
	
	for (size_t i = 0; i < this->populacao.size(); ++i) {
		individuo = this->fitness(this->populacao[i]);
		if (individuo.second > melhorIndividuo.second)
			melhorIndividuo = individuo;
	}
	
	return melhorIndividuo.first;
}

//
// A função simula a reprodução de uma nova população geneticamente superior, sujeitas a mutações e elitismo, usando a população inicial
// retorna uma nova população geneticamente superior
//

std::vector<Cromossomo*> AlgoritmoGenetico::gerarNovaPopulacao() {
    std::vector<Cromossomo*> novaPopulacao = this->elitismo();

    std::random_device randomNumber;
    std::mt19937 seed(randomNumber());
    std::uniform_int_distribution<int> gap(0, this->populacao.size() - 1);
    size_t randomPosition1, randomPosition2 = 0;

    auto gerarDoisIndicesDistintos = [&](size_t& numero1, size_t& numero2) {
        numero1 = gap(seed);
        while (numero1 == numero2)
        	numero2 = gap(seed);
    };

    Cromossomo* selecionado1 = nullptr;
    Cromossomo* selecionado2 = nullptr;
    Cromossomo* individuoMaisApto1 = nullptr;
    Cromossomo* individuoMaisApto2 = nullptr;
    Cromossomo* novoIndividuo = nullptr;

    while (novaPopulacao.size() < this->populacao.size()) {
        gerarDoisIndicesDistintos(randomPosition1, randomPosition2);
        selecionado1 = this->populacao[randomPosition1];
        selecionado2 = this->populacao[randomPosition2];
        individuoMaisApto1 = this->selecionarMelhorIndividuo(selecionado1, selecionado2);

        gerarDoisIndicesDistintos(randomPosition1, randomPosition2);
        selecionado1 = this->populacao[randomPosition1];
        selecionado2 = this->populacao[randomPosition2];
        individuoMaisApto2 = this->selecionarMelhorIndividuo(selecionado1, selecionado2);

        novoIndividuo = this->crossOver(individuoMaisApto1, individuoMaisApto2, nullptr);

        novaPopulacao.push_back(novoIndividuo);
    }

    return novaPopulacao;
}

// 
// A função aplica o algoritmo genético, simulando mutações e elitismo, utilizando uma quantidade específica de gerações
// retorna o melhor indivíduo dentre as gerações
//

Cromossomo* AlgoritmoGenetico::rodarAG(size_t quantidadeDeGeracoes, Cromossomo*(*heuristic)(Graph*), Graph* graph) {
   this->criarPopulacao(heuristic, graph);

   Cromossomo* melhorIndividuo = nullptr;

   for (size_t i = 0; i < quantidadeDeGeracoes; ++i) {                                                 
       melhorIndividuo = this->obterMelhorIndividuo();
       this->populacao = this->gerarNovaPopulacao();	
   }

    return melhorIndividuo;
}


