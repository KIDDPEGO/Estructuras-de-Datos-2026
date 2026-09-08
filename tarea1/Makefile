CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = tarea1
SRCS = main.cpp tListaCaracteres.cpp tParrafo.cpp tDocumento.cpp
OBJS = $(SRCS:.cpp=.o)

BIN ?= documento.bin
CMD ?= comandos.txt
OUT ?= salida.txt

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) $(BIN) $(CMD) $(OUT)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean
