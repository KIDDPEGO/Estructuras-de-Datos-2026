CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

TARGET = tarea3
SRCS = main.cpp Grafo.cpp Digrafo.cpp EstructurasAuxiliares.cpp Logistica.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) salida.txt

.PHONY: all run clean