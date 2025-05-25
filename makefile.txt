CXX = g++
MAIN_TARGET = main
TEST_TARGET = vector_test
SRC = master/vector.cpp master/main.cpp
TEST_SRC = master/vector.cpp
FLAGS = -L. -lVectorTest

all: $(MAIN_TARGET) $(TEST_TARGET)

$(MAIN_TARGET): $(SRC)
	$(CXX) -o $(MAIN_TARGET) $(SRC)

$(TEST_TARGET): $(TEST_SRC)
	$(CXX) -o $(TEST_TARGET) $(TEST_SRC) $(FLAGS)

run: $(MAIN_TARGET)
	./$(MAIN_TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(MAIN_TARGET) $(TEST_TARGET) 