#include "Graph.hpp"

Graph::Graph(size_t order, bool isDirected, float probabilityOfEdge) {
    this->isDirected = isDirected;
    this->order = order;
    this->size = 0;
    
    this->adjList = std::vector<std::list<int>>(order);
    
    size_t connectedVertex = 0;
    float probability = 0.0;
    
    std::random_device randomNumber;
    std::mt19937 seed(randomNumber());
    std::uniform_int_distribution<int> gap(0, order - 1); 
    std::uniform_real_distribution<float> probabilityGap(0.0, 1.0);

    for (size_t i = 0; i < order; ++i) {
        connectedVertex = gap(seed); 
        
        while (i == connectedVertex) 
            connectedVertex = gap(seed);
        
        if (!edgeExists(i, connectedVertex)) 
            addEdge(i, connectedVertex); 

        for (size_t j = i + 1; j < order; ++j) {
            if (!edgeExists(i, j)) {
                probability = probabilityGap(seed);
                if (probabilityOfEdge >= probability)
                    addEdge(i, j); 
            }
        }
    }
}

Graph::Graph(const Graph& graph) {
    this->adjList = graph.adjList;
    this->order = graph.order; 
    this->size = graph.size;
    this->isDirected = graph.isDirected;
}

Graph::Graph() {}

void Graph::addEdge(int source, int destination) {
    if (this->isDirected == false) {
        this->adjList[source].push_back(destination);
        this->adjList[destination].push_back(source);
        this->size += 2;  
    } else {
        this->adjList[source].push_back(destination);
        this->size += 1;
    }
}

bool Graph::edgeExists(size_t u, size_t v) {
    return std::find(adjList[u].begin(), adjList[u].end(), v) != adjList[u].end();
}

size_t Graph::getVertexDegree(size_t vertex) { return this->adjList[vertex].size(); }

size_t Graph::getSize() { return this->size; }

size_t Graph::getOrder() { return this->order; }

std::list<int> Graph::getAdjacencyList(size_t vertex) { return this->adjList[vertex]; }
	
/*
void Graph::breadthFirstSearch() {
    std::vector<bool> visited(this->order, false);
    std::queue<int> fila;
    visited[vertices[0]->identificator] = true;  
    fila.push(vertices[0]->identificator);
    
    while (!fila.empty()) {
        int temp = fila.front();
        fila.pop();
        std::cout << temp << std::endl;  

        for (const auto& it : edges[temp]) {
            if (!visited[it]) {
                visited[it] = true; 
                fila.push(it);
            }
        }
    }
}

void Graph::depthFirstSearch() {
    std::vector<bool> visited(this->order, false);
    std::stack<int> stack;
    stack.push(vertices[0]->identificator); 

    while (!stack.empty()) {
        int temp = stack.top();
        stack.pop();

        if (!visited[temp]) {
            visited[temp] = true;  
            std::cout << temp << std::endl; 

            for (const auto& neighbor : edges[temp]) {
                if (!visited[neighbor])  
                    stack.push(neighbor);          
            }
        }
    }
} 
*/

void Graph::deleteAdjacencyList(size_t vertex) {
    if ((vertex >= this->adjList.size()) || (this->adjList[vertex] == std::list<int>{-1})) 
        return;
        
    std::queue<int> toDelete;
    toDelete.push(vertex);
    int currentVertex = -1;
    
    for (const auto& it: this->adjList[vertex])
    	toDelete.push(it);

    while (!toDelete.empty()) {
        currentVertex = toDelete.front();
        toDelete.pop();

        for (const auto& it: this->adjList[currentVertex])
        	this->adjList[it].remove(currentVertex);
       	deleteVertex(currentVertex);
    }
}

void Graph::deleteVertex(size_t vertex) {
    this->adjList[vertex].clear();
    this->adjList[vertex] = {-1}; 
    --this->order;
    this->size -= this->adjList[vertex].size();
}




std::ostream& operator<< (std::ostream& os, const Graph& graph) {
    for (size_t i = 0; i < graph.adjList.size(); ++i) {
 	    std::cout << i << " ----> ";
 	    for (const auto& it: graph.adjList[i])
 		    std::cout << it << " ";
 	    std::cout << std::endl;
    }
     return os;
 }
