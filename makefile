CXX = g++
CXXFLAGS = -Wall $(shell wx-config --cxxflags | sed 's/-pthread//g')
LIBS = $(shell wx-config --libs | sed 's/-pthread//g')

TARGET = sistema_evento

SRC = main.cpp programacaoBasica.cpp

OBJS = main.o programacaoBasica.o

main.o: main.cpp 
programacaoBasica.o: programacaoBasica.cpp programacaoBasica.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: all
	./$(TARGET)