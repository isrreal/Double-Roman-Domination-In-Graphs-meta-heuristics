CPPFLAGS=-std=c++17 
IPATH=-Iinc/
SRC=src/
OBJ=obj/

all: app

app: main.gch AlgoritmoGenetico.gch Cromossomo.gch Graph.gch DoubleRomanDomination.gch
	g++ $(OBJ)main.gch $(OBJ)AlgoritmoGenetico.gch $(OBJ)Cromossomo.gch $(OBJ)Graph.gch $(OBJ)DoubleRomanDomination.gch -o app

main.gch: $(SRC)main.cpp
	$(CHAIN)-gcc $(CPPFLAGS) $(IPATH) -c $(SRC)main.cpp -o $(OBJ)main.gch
                                        
AlgoritmoGenetico.gch: $(SRC)AlgoritmoGenetico.cpp                         
	g++ $(CPPFLAGS) $(IPATH) -c $(SRC)AlgoritmoGenetico.cpp -o $(OBJ)AlgoritmoGenetico.gch

DoubleRomanDomination.gch: $(SRC)Graph.cpp 
	g++ $(CPPFLAGS) $(IPATH) -c $(SRC)DoubleRomanDomination.cpp -o $(OBJ)DoubleRomanDomination.gch
	
Cromossomo.gch: $(SRC)Cromossomo.cpp 
	g++ $(CPPFLAGS) $(IPATH) -c $(SRC)Cromossomo.cpp -o $(OBJ)Cromossomo.gch
	
Graph.gch: $(SRC)Graph.cpp 
	g++ $(CPPFLAGS) $(IPATH) -c $(SRC)Graph.cpp -o $(OBJ)Graph.gch
	
clean:
	rm -rf $(OBJ)*.gch

