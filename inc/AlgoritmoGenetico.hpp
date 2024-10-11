#ifndef ALGORITMO_GENETICO_HPP
#define ALGORITMO_GENETICO_HPP

#include <iostream>
#include <random>
#include <vector>
#include "Cromossomo.hpp"

class AlgoritmoGenetico {
	private:
		size_t tamanhoDaPopulacao;
		size_t quantidadeDeGenes;
		float taxaDeMutacao;
		float taxaDeElitismo;
		std::vector<Cromossomo*> populacao;
		std::vector<std::string> subgrupos;
		
		Cromossomo* criarCromossomo(size_t quantidadeDeGenes, Graph* graph);
		void criarPopulacao(Cromossomo*(*heuristic)(Graph*), Graph* graph);
		std::vector<std::string> binarioParaDecimal(std::vector<std::string>);
		Cromossomo* selectionMethod(Cromossomo*(*selectionHeuristic)(std::vector<Cromossomo*>));
		Cromossomo* selecionarMelhorIndividuo(Cromossomo* cromossomo1, Cromossomo* cromossomo2);

		Cromossomo* crossOver(Cromossomo* pai, Cromossomo* mae, Cromossomo*(*crossOverHeuristic)(Cromossomo*, Cromossomo*)); 
		Cromossomo* feasibilityCheck(Cromossomo* cromossomo);
		Cromossomo* mutacao(Cromossomo*);
		std::vector<Cromossomo*> elitismo();
		std::vector<Cromossomo*> gerarNovaPopulacao();
	public:
		AlgoritmoGenetico(size_t tamanhoDaPopulacao, size_t quantidadeDeGenes,
			       	float taxaDeMutacao, float taxaDeElitismo):
        				tamanhoDaPopulacao(tamanhoDaPopulacao), quantidadeDeGenes(quantidadeDeGenes),
				       	taxaDeMutacao(taxaDeMutacao), taxaDeElitismo(taxaDeElitismo),
                        populacao(tamanhoDaPopulacao, nullptr) {}
        ~AlgoritmoGenetico();
        std::vector<Cromossomo*> getPopulacao();      
		Cromossomo* rodarAG(size_t quantidadeDeGeracoes, 
                Cromossomo*(*selectionMethod)(std::vector<Cromossomo*>),
                Cromossomo*(*heuristic)(Graph*), Graph* graph);
       
        static std::pair<Cromossomo*, int> fitness(Cromossomo*);
        static Cromossomo* tournamentSelection(std::vector<Cromossomo*> populacao);
        static Cromossomo* rouletteWheelSelection(std::vector<Cromossomo*>           populacao);                                                                                                     
        std::string binarioParaDecimal(std::string);
        std::vector<std::string> leituraDeValores(Cromossomo*, size_t);
};	

#endif
