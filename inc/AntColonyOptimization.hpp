#ifndef ANT_COLONY_OPTIMIZATION_HPP
#define ANT_COLONY_OPTIMIZATION_HPP

#include "Graph.hpp"
#include <vector>

class AntColonyOptimization {
    private:
        Graph graph;
        std::vector<float> graphPheromone;
        std::vector<int> solution;
        size_t numberOfAnts;
        std::vector<int> currentBestSolution;
        std::vector<int> bestSolution;
         
        float convergenceFactor;
        float evaporationRate;

        float minDestructionRate;
        float maxDestructionRate;
        size_t currentRVNSnumber;
        size_t maxRVNSfunctions;
        size_t maxRVNSiterations;
        size_t maxRVNSnoImprovementIterations;


        void initializePheromones(std::vector<float>& graphPheromone);
        std::vector<int> constructSolution(std::vector<int> solution);
        std::vector<int> extendSolution(std::vector<int> solution);
        std::vector<int> reduceSolution(std::vector<int> solution);
        std::vector<int> RVNS(std::vector<int> solution);
                                                                       
        std::vector<int> destroySolution(std::vector<int> solution);

        size_t chooseVertex(Graph& temp);
        size_t chooseVertex(std::vector<int> solution);

        bool feasible(std::vector<int> solution);

        size_t summation(std::vector<int> solution);
        
        float getMaxPheromoneValue(std::vector<float> graphPheromone);
        
        float getMinPheromoneValue(std::vector<float> graphPheromone);
        
        bool delta(std::vector<int> solution, size_t vertex);

        void updatePheromones(std::vector<int>& currentBestSolution,
                std::vector<int>& bestSolution,
                std::vector<float>& graphPheromone);

        float computeConvergence(std::vector<float> graphPheromone);
    public:

        AntColonyOptimization(Graph& graph, size_t numberOfAnts);
        
        std::vector<int> getBestSolution();

        void run(size_t iterations);
};

#endif
