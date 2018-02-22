# Algemene flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
# Lijst met objecten
OBJECTS = Tetris.o

all: tetris

# De volgende 2 targets worden gebruikt voor het compileren van de app
obj/%.o: src/%.cpp
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

tetris: $(addprefix obj/, $(OBJECTS)) obj/main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Target om alles schoon te maken
clean:
	rm -f ./tetris
	rm -Rf ./obj
