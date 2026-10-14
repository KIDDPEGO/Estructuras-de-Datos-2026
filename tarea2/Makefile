CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = tarea2
SRCS = main.cpp Pila.cpp Cola.cpp ABB.cpp AVL.cpp Juego.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	./$(TARGET) inicio.txt partida.txt arbol.txt 

clean:
	rm -f  $(TARGET)
