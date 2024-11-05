CPPFLAGS=-std=c++17 
IPATH=-Iinc/
SRC=src/
OBJ=obj/

all: create_obj_dir app

app: main.gch GeneticAlgorithm.gch Chromosome.gch Graph.gch DoubleRomanDomination.gch AntColonyOptimization.gch
	g++ $(OBJ)main.gch $(OBJ)GeneticAlgorithm.gch $(OBJ)Chromosome.gch $(OBJ)Graph.gch $(OBJ)DoubleRomanDomination.gch $(OBJ)AntColonyOptimization.gch	-o app

main.gch: $(SRC)main.cpp
	$(CHAIN)-gcc $(CPPFLAGS) $(IPATH) -c $(SRC)main.cpp -o $(OBJ)main.gch
                                        
GeneticAlgorithm.gch: $(SRC)GeneticAlgorithm.cpp                         
	g++ $(CPPFLAGS) $(IPATH) -c $(SRC)GeneticAlgorithm.cpp -o $(OBJ)GeneticAlgorithm.gch

AntColonyOptimization.gch: $(SRC)AntColonyOptimization.cpp                         
	g++ $(CPPFLAGS) $(IPATH) -c $(SRC)AntColonyOptimization.cpp -o $(OBJ)AntColonyOptimization.gch

DoubleRomanDomination.gch: $(SRC)Graph.cpp 
	g++ $(CPPFLAGS) $(IPATH) -c $(SRC)DoubleRomanDomination.cpp -o $(OBJ)DoubleRomanDomination.gch

Chromosome.gch: $(SRC)Chromosome.cpp 
	g++ $(CPPFLAGS) $(IPATH) -c $(SRC)Chromosome.cpp -o $(OBJ)Chromosome.gch
	
Graph.gch: $(SRC)Graph.cpp 
	g++ $(CPPFLAGS) $(IPATH) -c $(SRC)Graph.cpp -o $(OBJ)Graph.gch
	
create_obj_dir: 
	mkdir -p $(OBJ)
clean:
	rm -rf $(OBJ)*.gch

