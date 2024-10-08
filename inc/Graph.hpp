#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <queue>
#include <stack>
#include <random>
#include <algorithm>
#include <vector>
#include <list>

class Graph {
private:
    size_t order;
    size_t size;
    bool isDirected;
    
    std::vector<std::list<int>> adjList;

    void addEdge(int source, int destination);
   // void configureEdges(std::vector<std::pair<int, int>> edges);

public:	

    Graph(size_t order, bool isDirected, float probabilityOfEdge);	
    Graph(const Graph& graph);
    Graph();
    ~Graph();
 
    size_t getSize();
    size_t getOrder();
    size_t getVertexDegree(size_t vertex);
    
    std::list<int> getAdjacencyList(size_t vertex);
    
    bool edgeExists(size_t u, size_t v);	

    void breadthFirstSearch();  
    
    void setVertexLabel(size_t vertex, int label);
    
    void setAdjacenciesLabel(size_t vertex, int label);
    
    void depthFirstSearch();
    
    void deleteAdjacencyList(size_t vertex);
    
    void deleteVertex(size_t vertex);
    
    friend std::ostream& operator<< (std::ostream& os, const Graph& graph) {
        for (size_t i = 0; i < graph.adjList.size(); ++i) {
		std::cout << i << " ----> ";
		for (const auto& it: graph.adjList[i])
			std::cout << it << " ";
			// std::cout << it << " (" << graph.adjList[it]->label << ") ";
		std::cout << std::endl;
	}
        return os;
    }
};

#endif
