# What is a meta-heuritic?
A meta-heuristic is a general exploration method, often stochastic, that applies similarly to various different combinatorial optimization problems. It typically begins with any feasible solution and iteratively improves it over several iterations until a stopping criterion is met. Examples of meta-heuristics include Genetic Algorithms and Ant Colony Optimization.


# Meta-heuristic Algorithms for Double Roman Domination Problem

In this project, we implement two algorithms based on meta-heuristics for solving the Double Roman Domination Problem, inspired by the paper **Meta-heuristic Algorithms for Double Roman Domination Problem**. These algorithms are based on Genetic Algorithms and Ant Colony Optimization.

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

4. **ApplyRVNS**: This sub-routine randomly selects a vertex labeled 2 or 0 and unlabels it, updating the value to -1. The **ConstructSolution**, **ExtendSolution**, and **ReduceSolution** sub-routines are then reapplied, and the new solution's weight is compared to the previous one. If the new solution has a lower weight, it replaces the current solution.



## How to Use

1. Clone the repository
   ```bash
   git clone https://github.com/isrreal/Double-Roman-Domination-In-Graphs-meta-heuristics.git

2. Compile the code
   ```bash
   make
3. Run the code
```bash
  ./app graph_order edge_probability
