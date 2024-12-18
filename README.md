# Meta-heuristic Algorithms for Double Roman Domination Problem

In this project, we implement two algorithms based on meta-heuristics for solving the Double Roman Domination Problem, an NP-Complete Combinatorial Optimization Problem, inspired by the paper [**Meta-heuristic Algorithms for Double Roman Domination Problem**](https://doi.org/10.1016/j.asoc.2024.111306). These meta-heuristics are based on Genetic Algorithms and Ant Colony Optimization.

# What is Double Roman Domination Problem?

A *Double Roman Domination Function* (DRDF) of a graph $G$ is a function $h: V(G) \rightarrow \{0, 1, 2, 3\}$ that satisfies the following conditions:

1. If $h(v) = 0$, then $v$ has at least two neighbors $u$ and $u_1$ such that $h(u) = h(u_1) = 2$; or $v$ has one neighbor $u_2$ such that $h(u_2) = 3$.

2. If $h(v) = 1$, then $v$ has at least one neighbor $u$ such that $h(u) \geq 2$.

The weight of the double Roman domination function is denoted by $h(V(G)) = \sum_{v \in V(G)} h(v)$. A DRDF is *optimal* if it has the smallest possible weight. The *double Roman domination number* of a graph $G$ is the smallest weight of a DRDF of $G$ and is denoted by $\gamma_{2R}(G)$. The *Double Roman Domination Problem* (DRDP) consists of determining $\gamma_{2R}(G)$ for an arbitrary graph $G$.

The decision version of the DRDP consists of, given a graph $G$ and an integer $\ell$, deciding if $G$ has a DRDF with weight less than or equal to $\ell$. This decision problem is NP-Complete.

# What is a Optimization Problem?

According to *Papadimitriou e Steiglitz (1982)*, an *optimization problem (OP)* consists of three core components: a set of *instances* (inputs), a set of *feasible solutions* $Sol(I)$ for each instance $I$, and an *objective function* $val(S)$, which assigns a numerical cost to each feasible solution $S \in Sol(I)$. If the feasible solution set $Sol(I)$ for an instance $I$ is empty, $I$ is deemed *infeasible*; otherwise, it is *feasible*. The goal of an OP is to find the best solution among all feasible solutions. These problems are generally classified as *minimization* or *maximization* problems, focusing on the solutions with the minimum or maximum cost, respectively. A feasible solution with optimal cost is called an *optimal solution*, and its value for any instance $I$ is denoted as $OPT(I)$, where $OPT(I) = val(S^\*)$ for an optimal solution $S^*$. Note that $OPT(I)$ is defined only if $I$ is feasible.

Optimization problems are often computationally challenging. Complexity theory classifies these problems as follows:

- **P**: Problems solvable in polynomial time.
- **NP**: Decision problems (YES/NO answers) whose solutions are verifiable in polynomial time.
- **NP-hard**: Problems to which every problem in NP can be reduced in polynomial time, indicating high computational difficulty.
- **NP-complete**: Problems that are both in NP and NP-hard, representing many real-world problems without known polynomial-time solutions.

# What is a Meta-Heuristic?
A meta-heuristic is a general exploration method, often stochastic, that applies similarly to various different combinatorial optimization problems. It typically begins with any feasible solution and iteratively improves it over several iterations until a stopping criterion is met. Examples of meta-heuristics include Genetic Algorithms and Ant Colony Optimization.


## Genetic Algorithm

The genetic algorithm proposed by the authors represents solutions, or chromosomes, as vectors of size $|V|$, where each position represents a specific vertex and its label, according to the Double Roman Domination Function (DRDF) constraints. The initial population is generated using three heuristics, producing 1000 chromosomes. Each heuristic uses an auxiliary graph $G$, which is a copy of the original graph. During each iteration, vertices are removed from $G$, with the stopping condition being $V(G) = \emptyset$.

1. **First Heuristic**: A greedy approach is applied. In each iteration, a vertex $v$ is randomly selected from the auxiliary graph and assigned the label 3. The corresponding position in the solution vector is labeled 3, while vertices in $N(v)$ are labeled 0.
   
2. **Second Heuristic**: Similar to the first, but after removing labeled vertices, the auxiliary graph is checked for isolated vertices (degree 0). These vertices are labeled 2, and the corresponding positions in the solution vector are updated. The vertices are then removed from the auxiliary graph.

3. **Third Heuristic**: Vertices are sorted in descending order by degree. The highest-degree vertex is selected and labeled 3, while its neighbors in $N(v)$ are labeled 0. If the remaining vertices in the auxiliary graph have degree 0, they are labeled 2.

### Crossover Operator

Two solutions $S_1$ and $S_2$ are selected from the current population of 1000 chromosomes. Random indices $R_1$ and $R_2$ are chosen, and the labels between these indices in $S_1$ and $S_2$ are swapped. The resulting solutions are checked to ensure they satisfy the DRDF constraints. Elitism and mutation rate are not considered in the proposed algorithm.

## Ant Colony Optimization (ACO)

The Ant Colony Optimization algorithm simulates the behavior of ants searching for food, where ants deposit pheromones along their paths. The best path is the one with the highest pheromone concentration, guiding future ants. In this algorithm, each vertex in the graph is associated with an initial pheromone value of 0.5, and each solution is represented as a vector of size $|V|$. The weight of the solution is the sum of the labels in the solution vector, with the goal of finding a solution with the smallest possible weight. The algorithm runs until a maximum number of iterations is reached or there are no improvements in the solution for a set number of iterations.

The type of Ant Colony Optimization proposed is based on two variants: **MAX-MIN Ant System** (MMAS) and **Hyper-Cube Framework** (HCF).

### ACO Sub-routines

1. **ConstructSolution**: A random vertex is selected and labeled 3, while its neighbors are labeled 0 and removed from the auxiliary graph. This process repeats until the graph is empty.

2. **ExtendSolution**: A vertex labeled 0 or 2 is selected from the current solution and updated to 3.

3. **ReduceSolution**: Redundant vertices are removed from the current solution. A vertex $v$ is redundant if all vertices in its closed neighborhood $N[v]$ are dominated by other vertices in the solution.

4. **RVNS (Random Variable Neighborhood Search)**: This function enhances the best result obtained from the ACO algorithm by exploring nearby solution spaces. RVNS increases the likelihood of finding a solution closer to the optimal one by modifying the solution in the following steps:
    - The **DestroySolution** sub-routine randomly selects a vertex labeled 0 or 2 and also unlabeled it, setting its value to -1.
    - **ConstructSolution**, **ExtendSolution**, and **ReduceSolution** are then reapplied to form a new solution, which is compared with the previous one. If the new solution has a lower weight, it replaces the current solution.


## How to Use

1. Clone the repository
   ```bash
   git clone https://github.com/isrreal/Double-Roman-Domination-In-Graphs-meta-heuristics.git
### 2. Edit the File "graph.txt":

The `graph.txt` file is essential for defining the structure of the graph, specifying both the **order** (the number of vertices) and the **size** (the number of edges). It should be formatted in a way that clearly outlines the relationships between the vertices.

1. **File Structure**:
   - The first line should contain two integers:
     - `order_of_graph`: This represents the total number of vertices in the graph.
     - `size_of_graph`: This indicates the total number of edges connecting the vertices.
   
2. **Edge List**:
   - Subsequent lines must list pairs of integers, each representing an edge between two vertices. Each pair indicates a direct connection between the specified vertices.

**Example of `graph.txt`**:

By default, the Roman Empire graph is represented as follows:

![Graph Representation](https://github.com/user-attachments/assets/d7ec6492-6090-4e5a-8173-01f1ace57b5a)

#### Vertex Mapping:
- **Britannia** - 0
- **Gaul** - 1
- **Iberia** - 2
- **Rome** - 3
- **North Africa** - 4
- **Constantinople** - 5
- **Asia Minor** - 6
- **Egypt** - 7

The content below illustrates the Roman Empire represented as a graph with **8 vertices** and **11 edges**:

```plaintext
8 13
0 1 0 2
1 2 1 3
2 3 2 4 
3 4 3 5 3 7
4 7 5 6
5 7 6 7
```
   
5. Run the code
   ```bash
   # Syntax:
   # ./app <population_size> <generations> <chromosome_creation_heuristic> <number_of_ants> <iterations>
   #
   # Parameters:
   #   population_size                - Size of the population for the Genetic Algorithm
   #   generations                    - Number of generations to run in the Genetic Algorithm
   #   chromosome_creation_heuristic  - Heuristic for creating chromosomes [1, 2, or 3]. Default is 1.
   #   number_of_ants                 - Number of ants for the Ant Colony Optimization (ACO)
   #   iterations                     - Number of iterations for the ACO

   ./app <population_size> <generations> <chromosome_creation_heuristic> <number_of_ants> <iterations>

