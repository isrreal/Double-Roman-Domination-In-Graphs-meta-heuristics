CPPFLAGS=-std=c++17 
IPATH=-Iinc/
SRC=src/
OBJ=obj/

all: app

app: main.gch GeneticAlgorithm.gch Cromossome.gch Graph.gch DoubleRomanDomination.gch
	g++ $(OBJ)main.gch $(OBJ)GeneticAlgorithm.gch $(OBJ)Cromossome.gch $(OBJ)Graph.gch $(OBJ)DoubleRomanDomination.gch -o app

main.gch: $(SRC)main.cpp
	$(CHAIN)-gcc $(CPPFLAGS) $(IPATH) -c $(SRC)main.cpp -o $(OBJ)main.gch
                                        
GeneticAlgorithm.gch: $(SRC)GeneticAlgorithm.cpp                         
	g++ $(CPPFLAGS) $(IPATH) -c $(SRC)GeneticAlgorithm.cpp -o $(OBJ)GeneticAlgorithm.gch

DoubleRomanDomination.gch: $(SRC)Graph.cpp 
	g++ $(CPPFLAGS) $(IPATH) -c $(SRC)DoubleRomanDomination.cpp -o $(OBJ)DoubleRomanDomination.gch
	
Cromossome.gch: $(SRC)Cromossome.cpp 
	g++ $(CPPFLAGS) $(IPATH) -c $(SRC)Cromossome.cpp -o $(OBJ)Cromossome.gch
	
Graph.gch: $(SRC)Graph.cpp 
	g++ $(CPPFLAGS) $(IPATH) -c $(SRC)Graph.cpp -o $(OBJ)Graph.gch
	
clean:
	rm -rf $(OBJ)*.gch

